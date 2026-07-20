# Hướng dẫn toàn tập: Tự build Android Kernel và chạy trên QEMU

Tài liệu này tổng hợp lại toàn bộ quy trình từ con số 0: Kéo mã nguồn Android Kernel (GKI), cấu hình Kernel, tự viết module, đóng gói hệ thống file (RootFS) siêu nhẹ bằng BusyBox, và khởi chạy nó trên trình giả lập QEMU với tính năng chia sẻ thư mục máy thật - máy ảo.

---

## 1. Kéo mã nguồn Android Kernel (Kleaf/GKI)

Mã nguồn Kernel của Android hiện đại được quản lý bằng `repo` và sử dụng hệ thống build **Kleaf** (dựa trên Bazel).

**Các bước thực hiện:**
```bash
mkdir android-kernel && cd android-kernel
repo init -u https://android.googlesource.com/kernel/manifest -b common-android15-6.6
repo sync -j$(nproc)
```
Sau khi kéo về, toàn bộ mã nguồn sẽ nằm trong cây thư mục `common/`, còn công cụ build nằm ở `build/` và `tools/`.

---

## 2. Cấu hình chia sẻ thư mục Host - Guest (9P VirtIO)

Để máy ảo QEMU có thể đọc/ghi trực tiếp vào một thư mục trên máy thật (Host), chúng ta sử dụng giao thức **9P qua VirtIO**. GKI Kernel mặc định không nạp sẵn tính năng này, nên ta phải bật nó lên.

### 2.1. Sửa file `gki_defconfig`
File cấu hình mặc định: `common/arch/x86/configs/gki_defconfig`.
Bạn đã thêm các dòng sau vào phần cấu hình Networking và File System:
```ini
CONFIG_NET_9P=m
CONFIG_NET_9P_VIRTIO=m
CONFIG_9P_FS=m
CONFIG_9P_FS_POSIX_ACL=y
CONFIG_9P_FS_SECURITY=y
```
*(Lưu ý: Android GKI yêu cầu các cấu hình mới phải được đặt là `m` (Module) thay vì `y` (Built-in) để tuân thủ tính module hóa).*

### 2.2. Khai báo đầu ra trong `BUILD.bazel`
Vì chúng ta đã chuyển các cấu hình 9P thành `m`, quá trình biên dịch sẽ sinh ra 3 file: `9pnet.ko`, `9pnet_virtio.ko`, `9p.ko`. Cần phải khai báo chúng vào file `common/BUILD.bazel` tại thẻ `kernel_x86_64` (mục `module_implicit_outs`) để Bazel chịu xuất file ra ngoài.

---

## 3. Viết và Biên dịch Kernel Module tự chế (`hello_module`)

Bạn đã tạo một module tự viết nằm ở thư mục `mymodule/`.
*   **Mã nguồn C (`mymodule/hello_module.c`)**: Khai báo 2 tham số `my_number` và `my_name` bằng macro `module_param()`. Hàm `hello_init` in ra lời chào và hàm `hello_exit` in ra lời tạm biệt.
*   **Cấu hình Build (`mymodule/BUILD.bazel`)**:
    ```python
    load("//build/kernel/kleaf:kernel.bzl", "ddk_module")
    ddk_module(
        name = "hello_module",
        srcs = ["hello_module.c"],
        out = "hello_module.ko",
        kernel_build = "//common:kernel_x86_64",
        deps = ["//common:all_headers_x86_64"],
    )
    ```

**Cách biên dịch module này:**
Lệnh build thiết bị ảo (`virtual_device_x86_64_dist`) không tự động build module ngoài, do đó bạn phải build riêng nó:
```bash
tools/bazel build //mymodule:hello_module
```
File đầu ra sẽ nằm tại: `bazel-bin/mymodule/hello_module/hello_module.ko`.

---

## 4. Giải phẫu chi tiết file `build_rootfs.sh`

Mục đích của file này là gom tất cả các công cụ lệnh (BusyBox) và các Module (`.ko`) lại, bọc nó thành một cục file nén gọi là **Initramfs** (`initramfs.cpio.gz`). Khi Kernel boot xong, nó sẽ bung cục này ra RAM để làm ổ đĩa hệ điều hành C: đầu tiên.

### Chi tiết các khối lệnh quan trọng:

1.  **Tạo thư mục**: `mkdir -p "$OUTDIR/initramfs"/{bin,sbin,etc,proc...}`
    Tạo bộ khung cấu trúc thư mục chuẩn của Linux.
2.  **Chép BusyBox**: `cp /usr/bin/busybox "$OUTDIR/initramfs/bin/"`
    Lấy file nhị phân tĩnh BusyBox từ máy thật. Lát nữa vào máy ảo, tất cả các lệnh `ls`, `cat`, `grep` thực chất đều gọi về cái lõi BusyBox này.
3.  **Tạo script /init**: Đây là "trái tim" của file rootfs. File `/init` là thứ đầu tiên Kernel chạy sau khi boot xong.
    *   `/bin/busybox --install -s /bin`: Tạo các đường dẫn ảo (symlink) cho lệnh ls, cat, sh trỏ về lõi busybox.
    *   `mount -t proc/sys/devtmpfs`: Kích hoạt các thư mục ảo của Kernel.
    *   `mdev -s`: Trình quản lý thiết bị mini, giúp tự sinh ra các file như `/dev/sda`, `/dev/tty`.
    *   **Vòng lặp nạp Module**:
        ```bash
        for i in 1 2 3; do
            for mod in /modules/*.ko; do
                insmod "$mod"
        ```
        *Tại sao phải lặp 3 lần?* Vì các module phụ thuộc nhau (VD: `9p.ko` phải nạp sau `9pnet.ko`). Lặp 3 lần theo thứ tự ABC mặc kệ lỗi sẽ đảm bảo mọi dependency đều được giải quyết tự động mà không cần file cấu hình `modules.dep` phức tạp.
    *   **Mount thư mục chia sẻ (9P)**:
        `mount -t 9p -o trans=virtio... shared_mount /mnt/host`
        Kết nối ổ đĩa `shared_mount` (đã được cấu hình ở bên QEMU) vào thư mục `/mnt/host` của máy ảo.
    *   `exec /bin/sh -i`: Mở giao diện gõ lệnh (Terminal) cho người dùng.
4.  **Sao chép `hello_module.ko`**:
    Script sẽ đi tìm file `.ko` ở thư mục `bazel-bin/` vừa được build ở bước 3, chép nó vào `/modules/` để tí nữa vòng lặp `insmod` tự động nạp nó.
5.  **Nén thành file cpio.gz**:
    Dùng lệnh `cpio` và `gzip` để nén tàn bộ thư mục `initramfs` thành 1 file duy nhất.

---

## 5. Giải phẫu chi tiết file `run_qemu.sh`

Mục đích của file này là gọi trình giả lập phần cứng **QEMU**, nạp Kernel (`bzImage`) và hệ thống đĩa (`initramfs.cpio.gz`) vào để chạy.

### Giải thích các tham số truyền cho lệnh `qemu-system-x86_64`:

*   `-kernel "$BZIMAGE"`: Trỏ đến file Kernel đã được biên dịch.
*   `-initrd "$INITRAMFS"`: Trỏ đến hệ thống file nén chứa BusyBox.
*   `-display gtk -vga std`: Mở cửa sổ QEMU đồ họa mặc định.
*   `-append "console=ttyS0 console=tty0 loglevel=4"`:
    Đây là tham số truyền thẳng vào ruột Kernel.
    *   `console=ttyS0`: Xuất log ra cổng Serial ảo.
    *   `console=tty0`: Xuất log ra màn hình chính của QEMU.
    *   `loglevel=4`: Chỉ hiển thị log lỗi hoặc cảnh báo lúc boot (giảm bớt rác).
*   `-m 1024`: Cấp 1024MB RAM cho máy ảo.
*   `-enable-kvm -cpu host`: Chạy máy ảo bằng công nghệ ảo hóa phần cứng (KVM) để đạt tốc độ gần tương đương máy thật.
*   `-smp 2`: Cấp 2 lõi CPU ảo.
*   **Chia sẻ thư mục**:
    *   `-fsdev local,id=shared_dev,path="$SHARED_DIR",security_model=none`: Khởi tạo thiết bị hệ thống file trên máy ảo, gán ID là `shared_dev` và trỏ vào thư mục máy thật là `$SHARED_DIR` (tức thư mục `out/share/`).
    *   `-device virtio-9p-pci,fsdev=shared_dev,mount_tag=shared_mount`: Cắm thiết bị đó vào khe PCI ảo bằng chuẩn `virtio-9p`, đặt tên cho nó là `shared_mount`. (Đây chính là tên mà lệnh `mount -t 9p` trong script `/init` sẽ tìm để kết nối tới).

---

## 6. Tổng kết Quy trình sử dụng hàng ngày

1.  Mỗi khi sửa code Kernel module `hello_module.c`:
    ```bash
    tools/bazel build //mymodule:hello_module
    ```
2.  Sau đó nếu muốn test nóng (không cần khởi động lại máy ảo):
    ```bash
    # Trên máy thật
    cp bazel-bin/mymodule/hello_module/hello_module.ko out/share/
    ```
    ```bash
    # Trong máy ảo
    rmmod hello_module
    insmod /mnt/host/hello_module.ko my_number=99 my_name="NewName"
    dmesg | tail
    ```
3.  Nếu muốn nhúng luôn vào RootFS tự động chạy lúc khởi động:
    ```bash
    cd out && ./build_rootfs.sh && ./run_qemu.sh
    ```
