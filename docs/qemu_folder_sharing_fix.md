# Tài Liệu Khắc Phục Lỗi Chia Sẻ Thư Mục QEMU (9P VirtIO) trên Android Kernel

Tài liệu này lưu trữ chi tiết nguyên nhân lỗi, các file cấu hình và mã nguồn đã chỉnh sửa để kích hoạt thành công tính năng chia sẻ thư mục giữa máy thật (Host) và máy ảo QEMU (Guest) sử dụng giao thức **9P VirtIO**.

---

## 1. Tổng Quan Vấn Đề (Root Causes)

Trước khi chỉnh sửa, tính năng chia sẻ thư mục không hoạt động do 4 nguyên nhân gốc sau:
1.  **Thiếu cấu hình driver trong nhân Kernel**: Kernel mặc định của Android GKI không bật driver truyền tải VirtIO cho 9P (`CONFIG_NET_9P_VIRTIO`) và hệ thống file 9P (`CONFIG_9P_FS`).
2.  **Ràng buộc GKI của Android (Kleaf)**:
    *   Các module 9P cơ bản (`9pnet.ko`, `9pnet_fd.ko`) nằm trong danh sách module bắt buộc của GKI nên **bắt buộc phải biên dịch dưới dạng Module (`=m`)**, không được để dạng Built-in (`=y`). Nếu để `=y`, tiến trình đóng gói sẽ báo lỗi thiếu file `.ko`.
    *   Khi bật các module 9P mới dưới dạng module (`=m`), Kleaf yêu cầu phải khai báo tường minh chúng là file đầu ra (`module_implicit_outs`) của target build, nếu không hệ thống sẽ chặn build để tránh module "lạ".
3.  **Thiếu cơ chế phân phối của Bazel**: Target đóng gói cho thiết bị ảo (`virtual_device_x86_64_dist`) mặc định chỉ copy các module của thiết bị ảo ra thư mục `out/` mà bỏ qua các module nhân GKI (trong đó có 9P).
4.  **Lỗi logic nạp module trong script `/init`**: Lệnh `mount -t 9p` bị chạy trước khi các module driver (`9p.ko`, `9pnet.ko`...) được nạp vào nhân. Đồng thời, việc nạp module theo thứ tự bảng chữ cái bị lỗi do vấn đề phụ thuộc (dependency) giữa các module (ví dụ: `9p.ko` cần `9pnet.ko` và `netfs.ko` phải chạy trước).

---

## 2. Chi Tiết Các File Đã Chỉnh Sửa

Dưới đây là chi tiết các thay đổi bằng biểu đồ Git Diff:

### 2.1 Cấu hình Kernel
#### File: `common/arch/x86/configs/gki_defconfig`
Bật driver 9P và hệ thống file 9P dưới dạng module (`=m`). Cần xếp chúng đúng vị trí quy định của Kconfig để tránh lỗi `savedefconfig`.

```diff
@@ -292,8 +292,8 @@
 CONFIG_BT_HCIUART_BCM=y
 CONFIG_BT_HCIUART_QCA=y
 CONFIG_RFKILL=m
-CONFIG_NET_9P=y          # (Chuyển từ y sang m để tránh lỗi đóng gói GKI)
-CONFIG_NET_9P_VIRTIO=y   # (Chuyển sang m)
+CONFIG_NET_9P=m
+CONFIG_NET_9P_VIRTIO=m
 CONFIG_NFC=m
 CONFIG_NETDEV_ADDR_LIST_TEST=m
 CONFIG_PCI=y
@@ -601,7 +601,7 @@
 CONFIG_PSTORE_RAM=y
 CONFIG_EROFS_FS=y
 CONFIG_EROFS_FS_PCPU_KTHREAD=y
-CONFIG_9P_FS=y           # (Phải nằm ở cuối phần Filesystems và để dạng =m)
+CONFIG_9P_FS=m
 CONFIG_9P_FS_POSIX_ACL=y
 CONFIG_9P_FS_SECURITY=y
 CONFIG_NLS_CODEPAGE_437=y
```

---

### 2.2 Khai báo Module đầu ra cho GKI Kernel
#### File: `common/BUILD.bazel`
Khai báo thêm 3 module mới sinh ra vào thuộc tính `module_implicit_outs` của target `kernel_x86_64` để Kleaf cho phép đóng gói chúng.

```diff
@@ -201,7 +201,11 @@
     },
     "kernel_x86_64": {
         "kmi_symbol_list_strict_mode": False,
-        "module_implicit_outs": get_gki_modules_list("x86_64") + get_kunit_modules_list("x86_64"),
+        "module_implicit_outs": get_gki_modules_list("x86_64") + get_kunit_modules_list("x86_64") + [
+            "net/9p/9pnet_virtio.ko",
+            "fs/netfs/netfs.ko",
+            "fs/9p/9p.ko",
+        ],
         "make_goals": _GKI_X86_64_MAKE_GOALS,
         "extra_dist": [
             ":test_mappings_zip",
```

---

### 2.3 Cấu hình Phân Phối của Bazel ra thư mục `out/`
#### File: `common-modules/virtual-device/BUILD.bazel`
Thêm `//common:kernel_x86_64_modules` vào target phân phối để sao chép các file `.ko` của GKI sang thư mục `out/` khi chạy lệnh build.

```diff
@@ -303,6 +303,7 @@
         ":virtual_device_x86_64_merged_kernel_uapi_headers",
         ":virtual_device_x86_64_modules_install",
         "//common:kernel_x86_64",
+        "//common:kernel_x86_64_modules", # Thêm dòng này
         "//common:kernel_x86_64_additional_artifacts",
         "//common:test_mappings_zip",
         "//common:tests_zip_x86_64",
```

---

### 2.4 Cấu hình Khởi Chạy QEMU
#### File: `out/run_qemu.sh`
Chỉ định thư mục chia sẻ riêng biệt là `out/share` trên máy host (tự động tạo nếu chưa có) và truyền tham số map thiết bị `virtio-9p-pci` vào QEMU với tag mount là `shared_mount`.

```diff
@@ -7,7 +7,8 @@
 SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
 BZIMAGE="$SCRIPT_DIR/bzImage"
 INITRAMFS="$SCRIPT_DIR/initramfs.cpio.gz"
-SHARED_DIR="$SCRIPT_DIR"
+SHARED_DIR="$SCRIPT_DIR/share"
+mkdir -p "$SHARED_DIR"          # Tự động tạo thư mục share
 
 # ... (kiểm tra file)
 
@@ -41,5 +41,7 @@
     -m 1024 \
     -enable-kvm \
     -cpu host \
-    -smp 2
+    -smp 2 \
+    -fsdev local,id=shared_dev,path="$SHARED_DIR",security_model=none \
+    -device virtio-9p-pci,fsdev=shared_dev,mount_tag=shared_mount
```

---

### 2.5 Cấu hình Nạp Module và Mount Hệ Thống File trong Guest OS
#### File: `out/build_rootfs.sh`
Chỉnh sửa logic bên trong file `/init` của RootFS:
1.  Chuyển lệnh `mount -t 9p` xuống chạy cuối cùng, sau khi toàn bộ module đã được nạp.
2.  Lặp lệnh nạp module `insmod` **3 lần** để tự động giải quyết các phụ thuộc lẫn nhau.
3.  Tắt cảnh báo lỗi ghi vào `/proc/sys/kernel/hotplug` (do kernel bản mới đã tắt tính năng này).

```diff
@@ -40,11 +40,8 @@
 mount -t sysfs    none /sys
 mount -t devtmpfs none /dev 2>/dev/null || true
 
-# (Xóa lệnh mount 9p ở đầu script cũ)
-
 # Thiết lập hotplug để tự tạo device nodes
-echo /bin/mdev > /proc/sys/kernel/hotplug
+echo /bin/mdev > /proc/sys/kernel/hotplug 2>/dev/null || true # Ẩn lỗi
 mdev -s
 
-# Nạp các module nếu có trong /modules/ (Chạy lặp 3 lần để giải quyết dependency)
-for mod in /modules/*.ko; do
-    [ -f "$mod" ] && insmod "$mod" 2>/dev/null
-done
+for i in 1 2 3; do
+    for mod in /modules/*.ko; do
+        [ -f "$mod" ] && insmod "$mod" 2>/dev/null
+    done
+done
 
+# (Đưa lệnh mount 9p xuống cuối sau khi load driver xong)
+mount -t 9p -o trans=virtio,version=9p2000.L shared_mount /mnt/host 2>/dev/null || echo "⚠ Không thể mount thư mục chia sẻ!"
```

---

## 3. Quy Trình Vận Hành & Kiểm Tra

Khi bạn muốn biên dịch hoặc chạy lại từ đầu, hãy thực hiện theo các bước sau:

### Bước 1: Biên dịch trên máy Host
Tại thư mục gốc `/home/trungcao/training/android-kernel`:
```bash
tools/bazel run //common-modules/virtual-device:virtual_device_x86_64_dist -- --destdir=out
```

### Bước 2: Build lại Rootfs & khởi chạy QEMU
```bash
cd out
./build_rootfs.sh
./run_qemu.sh
```

### Bước 3: Kiểm tra trong máy ảo
Sau khi máy ảo boot lên thành công:
```bash
ls /mnt/host
```
Nếu nhìn thấy các file trong thư mục `out/share/` trên máy thật (ví dụ `test.txt`) hiển thị tại đây là thành công.
