# Hướng dẫn Cấu hình VS Code để Auto-complete/Gợi ý Code tốt nhất cho Android Kernel

Khi lập trình Kernel Space (Linux/Android Kernel), hệ thống không sử dụng các thư viện C chuẩn (`libc`) mà sử dụng hệ thống tiêu đề (headers) riêng của nhân. Để VS Code gợi ý code thông minh, chính xác và không bị báo lỗi đỏ nhầm, bạn hãy làm theo các bước sau.

---

## 1. Sử dụng Clangd (Khuyên dùng thay cho C/C++ IntelliSense)

Đối với các dự án lớn như Kernel, extension **Clangd** của LLVM hoạt động hiệu quả hơn, nhanh hơn và chính xác hơn nhiều so với extension C/C++ mặc định của Microsoft.

### Bước 1.1: Cài đặt Extension
1. Cài đặt extension **clangd** trên VS Code Marketplace.
2. Vô hiệu hóa tính năng IntelliSense của extension Microsoft C/C++ để tránh xung đột:
   * Mở `.vscode/settings.json` (hoặc cấu hình settings của VS Code) và thêm dòng sau:
     ```json
     "C_Cpp.intelliSenseEngine": "disabled"
     ```

### Bước 1.2: Sử dụng `compile_commands.json`
Clangd hoạt động dựa trên tệp `compile_commands.json` để biết chính xác các file mã nguồn đang sử dụng cờ biên dịch và include path nào:
* **Đối với dự án hiện tại của bạn**: Tệp này **đã có sẵn** ở thư mục gốc, Clangd sẽ tự động nhận diện và phân tích cấu hình.
* **Đối với dự án mới**: Tệp này ban đầu sẽ **chưa có**. Bạn cần làm theo hướng dẫn ở [Mục 5](#5-quy-trình-thiết-lập-từ-đầu-cho-một-dự-án-kernel-mới-new-project) bên dưới để tự sinh ra tệp này trước khi Clangd có thể hoạt động.

---

## 2. Cấu hình tệp `.clangd` để tối ưu hóa gợi ý

Tệp cấu hình `.clangd` ở thư mục gốc giúp bạn tinh chỉnh Clangd cho các tệp hoặc thư mục cụ thể (như các driver hoặc module bạn tự viết thêm mà chưa được liệt kê trong `compile_commands.json`).

Mở file [.clangd](file:///home/trungcao/training/android-kernel/.clangd) và cập nhật nội dung như sau:

```yaml
CompileFlags:
  # Vô hiệu hóa một số cảnh báo phiền phức
  Add: [
    -Wno-unknown-warning-option,
    -Wno-everything
  ]
  # Chỉ định compiler thích hợp nếu Clangd không tự tìm thấy sysroot hệ thống hoặc prebuilts
  Compiler: clang

# Cấu hình fallback cho các module tự viết nằm ngoài sơ đồ build chính
# (Ví dụ: modulemoi/ hoặc mydriver/ nếu chưa được tích hợp vào Kbuild/Bazel)
If:
  PathMatch: (modulemoi|mydriver|myapp)/.*
CompileFlags:
  Add: [
    -D__KERNEL__,
    -DKBUILD_MODNAME="mymodule",
    -nostdinc,
    # Trỏ đến thư mục include của Kernel tương ứng với kiến trúc phần cứng (x86 hoặc arm64)
    -I/home/trungcao/training/android-kernel/common/include,
    -I/home/trungcao/training/android-kernel/common/arch/x86/include,
    -I/home/trungcao/training/android-kernel/bazel-bin/common
  ]
```

---

## 3. Tạo/Cập nhật cơ sở dữ liệu biên dịch khi thêm file mới

Nếu bạn thêm một file C mới hoặc một thư mục Driver mới và muốn nó được gợi ý code chuẩn xác nhất:
1. **Cách 1 (Chuẩn nhất)**: Khai báo Module của bạn vào cấu hình Build của nhân (Kconfig, Makefile / BUILD.bazel) và chạy lệnh build kernel. Hệ thống build sẽ tự động cập nhật tệp `compile_commands.json`.
2. **Cách 2 (Thủ công nhanh)**: Thêm đường dẫn thư mục chứa code mới của bạn vào phần `PathMatch` trong cấu hình `.clangd` ở trên để Clangd áp dụng các cờ của Kernel khi phân tích cú pháp.

---

## 4. Reset Clangd Index khi cấu hình xong

Sau khi thay đổi file cấu hình `.clangd` hoặc `compile_commands.json`:
1. Nhấn `Ctrl + Shift + P` (hoặc `F1`) trên VS Code.
2. Gõ và chọn lệnh: `clangd: Restart language server`.
3. Clangd sẽ tải lại cấu hình và phân tích lại mã nguồn, các cảnh báo lỗi đỏ không đúng sẽ biến mất và tính năng gợi ý (Go to Definition, Autocomplete) sẽ hoạt động mượt mà.

---

## 5. Quy trình thiết lập từ đầu cho một Dự án Kernel Mới (New Project)

Nếu bạn bắt đầu một dự án Kernel hoặc Android Kernel hoàn toàn mới, hãy làm theo các bước dưới đây để thiết lập gợi ý mã nguồn từ con số 0:

### Bước 5.1: Biên dịch dự án ít nhất một lần
Để sinh ra các tệp thông tin trung gian (các tệp `.cmd`), bạn cần cấu hình và biên dịch Kernel:
* **Với Linux Kernel chuẩn (Kbuild)**:
  ```bash
  make ARCH=arm64 defconfig     # Thiết lập cấu hình mặc định (ví dụ arm64)
  make ARCH=arm64 -j$(nproc)    # Biên dịch nhân và các module
  ```
* **Với Android GKI Kernel (sử dụng Bazel)**:
  ```bash
  tools/bazel build //common:kernel_aarch64   # Biên dịch thông qua Bazel
  ```

### Bước 5.2: Sinh tệp `compile_commands.json`
Trình biên dịch của VS Code cần tệp này để hiểu cấu trúc include của toàn bộ dự án.
* **Với Linux Kernel chuẩn**: Sử dụng tập lệnh Python đi kèm sẵn trong mã nguồn Kernel:
  ```bash
  ./scripts/clang-tools/gen_compile_commands.py
  ```
  Lệnh này sẽ tìm các tệp tin `.cmd` đã sinh ra ở Bước 5.1 và tạo ra tệp `compile_commands.json` ở thư mục gốc.

* **Với Android Kernel (Bazel)**: Chạy target sinh compile commands:
  ```bash
  tools/bazel run //common:compile_commands
  ```
  *(Tên target có thể thay đổi tùy thuộc vào cấu hình cụ thể trong `BUILD.bazel` của dự án bạn).*

### Bước 5.3: Tạo tệp cấu hình `.clangd` ở thư mục gốc
Tạo một tệp tên là `.clangd` ở gốc dự án mới của bạn với nội dung cấu hình tương tự như sau:
```yaml
CompileFlags:
  Add: [
    -Wno-unknown-warning-option,
    -Wno-everything
  ]
  Compiler: clang
```

### Bước 5.4: Kích hoạt trong VS Code
1. Mở thư mục gốc của dự án bằng VS Code.
2. Cài đặt extension **clangd** và tắt IntelliSense mặc định (như đã hướng dẫn ở [Mục 1](file:///home/trungcao/training/android-kernel/vscode_kernel_setup.md#1-sử-dụng-clangd-khuyên-dùng-thay-cho-cc-intellisense)).
3. Chạy lệnh `clangd: Restart language server` để Clangd bắt đầu lập chỉ mục (index) cho dự án mới của bạn.

