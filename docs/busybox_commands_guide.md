# Hướng Dẫn Các Lệnh Trong BusyBox (Tác Dụng & Tham Số)

Tài liệu này tổng hợp toàn bộ các lệnh được tích hợp sẵn trong phiên bản **BusyBox v1.30.1** (bản phân phối tĩnh mặc định trên máy của bạn), được phân loại theo từng nhóm chức năng kèm theo các tham số quan trọng và ví dụ thực tế.

---

## 1. Các Lệnh Thao Tác File & Thư Mục (File Operations)

Đây là nhóm lệnh cơ bản nhất để quản lý cấu trúc thư mục và file trong hệ thống máy ảo.

### 1.1 `ls` - Liệt kê nội dung thư mục
*   **Tác dụng**: Hiển thị danh sách các file và thư mục con.
*   **Tham số thường dùng**:
    *   `-l`: Hiển thị chi tiết (quyền truy cập, kích thước, chủ sở hữu, thời gian).
    *   `-a`: Hiển thị tất cả file, bao gồm cả file ẩn (bắt đầu bằng dấu `.`).
    *   `-h`: Hiển thị kích thước file ở định dạng dễ đọc (KB, MB, GB).
    *   `-R`: Liệt kê đệ quy các thư mục con.
*   **Ví dụ**: `ls -lah /mnt/host`

### 1.2 `cp` - Sao chép file/thư mục
*   **Tác dụng**: Copy dữ liệu từ nguồn tới đích.
*   **Tham số thường dùng**:
    *   `-r` hoặc `-R`: Sao chép đệ quy (dùng cho thư mục).
    *   `-f`: Ghi đè file đích mà không hỏi ý kiến.
    *   `-p`: Giữ nguyên thuộc tính file (thời gian, quyền hạn).
*   **Ví dụ**: `cp -rf /modules/hello_module.ko /tmp/`

### 1.3 `mv` - Di chuyển hoặc đổi tên file/thư mục
*   **Tác dụng**: Di chuyển file từ thư mục này sang thư mục khác, hoặc đổi tên file.
*   **Tham số thường dùng**:
    *   `-f`: Ghi đè file đích mà không hỏi.
    *   `-i`: Hỏi trước khi ghi đè.
*   **Ví dụ**: `mv old_name.txt new_name.txt`

### 1.4 `rm` - Xóa file/thư mục
*   **Tác dụng**: Xóa vĩnh viễn file hoặc thư mục khỏi hệ thống.
*   **Tham số thường dùng**:
    *   `-r` hoặc `-R`: Xóa đệ quy toàn bộ thư mục con và file bên trong.
    *   `-f`: Xóa cưỡng chế (force), không hỏi và bỏ qua file không tồn tại.
*   **Ví dụ**: `rm -rf /tmp/test_dir`

### 1.5 `mkdir` - Tạo thư mục mới
*   **Tác dụng**: Tạo thư mục mới tại đường dẫn chỉ định.
*   **Tham số thường dùng**:
    *   `-p`: Tạo đệ quy tất cả thư mục cha nếu chúng chưa tồn tại.
*   **Ví dụ**: `mkdir -p /mnt/host/share/subfolder`

---

## 2. Các Lệnh Xem & Xử Lý Văn Bản (Text Processing & Viewing)

### 2.1 `cat` - In nội dung file ra màn hình
*   **Tác dụng**: Nối và hiển thị nội dung của file ra terminal.
*   **Tham số thường dùng**:
    *   `-n`: Hiển thị số dòng ở đầu mỗi dòng.
*   **Ví dụ**: `cat -n /etc/passwd`

### 2.2 `grep` - Tìm kiếm nội dung theo mẫu
*   **Tác dụng**: Tìm kiếm chuỗi ký tự bên trong file hoặc luồng dữ liệu đầu vào.
*   **Tham số thường dùng**:
    *   `-i`: Tìm kiếm không phân biệt chữ hoa, chữ thường.
    *   `-r` hoặc `-R`: Tìm kiếm đệ quy trong tất cả các file của thư mục.
    *   `-n`: Hiển thị số thứ tự dòng tìm thấy.
    *   `-v`: Tìm các dòng **không** chứa từ khóa.
*   **Ví dụ**: `dmesg | grep -i "error"`

### 2.3 `vi` - Trình soạn thảo văn bản
*   **Tác dụng**: Trình soạn thảo màn hình trực quan để chỉnh sửa nội dung file.
*   **Các phím chức năng cơ bản**:
    *   `i`: Chuyển sang chế độ gõ chữ (Insert mode).
    *   `Esc`: Thoát chế độ gõ chữ, quay lại chế độ lệnh (Command mode).
    *   `:wq` (ở chế độ lệnh): Lưu file và thoát.
    *   `:q!` (ở chế độ lệnh): Thoát mà không lưu thay đổi.
*   **Ví dụ**: `vi /mnt/host/test.txt`

### 2.4 `less` / `more` - Xem file dạng phân trang
*   **Tác dụng**: Xem file nội dung dài một cách từ từ.
*   **Điều khiển**: Dùng phím mũi tên hoặc `Space` để cuộn, `q` để thoát.
*   **Ví dụ**: `less /var/log/messages`

---

## 3. Các Lệnh Quản Lý Kernel Modules

Đặc biệt quan trọng đối với việc phát triển và thử nghiệm Driver/Kernel.

### 3.1 `insmod` - Nạp module vào Kernel
*   **Tác dụng**: Nạp file module `.ko` trực tiếp vào bộ nhớ kernel.
*   **Tham số**: Nhận tham số là đường dẫn tuyệt đối hoặc tương đối tới file `.ko` cùng với các tham số của module (nếu có).
*   **Ví dụ**: `insmod /modules/hello_module.ko myparam=1`

### 3.2 `rmmod` - Gỡ module ra khỏi Kernel
*   **Tác dụng**: Gỡ bỏ module đang chạy khỏi bộ nhớ kernel.
*   **Tham số**: Nhận tên của module (không phải tên file `.ko`).
*   **Ví dụ**: `rmmod hello_module`

### 3.3 `lsmod` - Hiển thị các module đang chạy
*   **Tác dụng**: Liệt kê tất cả các kernel modules đang được nạp, kích thước và các module phụ thuộc.
*   **Ví dụ**: `lsmod`

### 3.4 `modinfo` - Xem thông tin chi tiết module
*   **Tác dụng**: Hiển thị thông tin tác giả, mô tả, giấy phép, và các tham số truyền vào của file `.ko`.
*   **Ví dụ**: `modinfo /modules/hello_module.ko`

---

## 4. Các Lệnh Quản Lý Hệ Thống & Thiết Bị (System & Mount)

### 4.1 `mount` - Gắn hệ thống file vào thư mục
*   **Tác dụng**: Mount các thiết bị lưu trữ, thư mục chia sẻ, hoặc các hệ thống file ảo (`/proc`, `/sys`) vào cây thư mục của máy ảo.
*   **Tham số thường dùng**:
    *   `-t <loại_fs>`: Định dạng hệ thống file (ví dụ: `ext4`, `proc`, `sysfs`, `9p`, `devtmpfs`).
    *   `-o <tùy_chọn>`: Các tham số bổ sung cấu hình (ví dụ: `trans=virtio` cho 9p, `ro` cho readonly).
*   **Ví dụ**: `mount -t 9p -o trans=virtio,version=9p2000.L shared_mount /mnt/host`

### 4.2 `umount` - Gỡ gắn hệ thống file
*   **Tác dụng**: Unmount hệ thống file khỏi thư mục.
*   **Tham số thường dùng**:
    *   `-f`: Buộc phải unmount (ngay cả khi thiết bị đang bận).
*   **Ví dụ**: `umount /mnt/host`

### 4.3 `dmesg` - Xem log của Kernel
*   **Tác dụng**: In toàn bộ thông tin log đệm từ nhân kernel (rất hữu ích khi debug `printk` từ driver).
*   **Tham số thường dùng**:
    *   `-C`: Xóa sạch log đệm cũ.
    *   `-w`: Theo dõi log thời gian thực (real-time).
*   **Ví dụ**: `dmesg | tail -n 20`

### 4.4 `df` - Kiểm tra dung lượng đĩa cứng
*   **Tác dụng**: Hiển thị dung lượng đã dùng, còn trống của các phân vùng đã mount.
*   **Tham số thường dùng**:
    *   `-h`: Định dạng dễ đọc (Megabytes, Gigabytes).
*   **Ví dụ**: `df -h`

---

## 5. Các Lệnh Quản Lý Tiến Trình (Process Management)

### 5.1 `ps` - Hiển thị danh sách tiến trình đang chạy
*   **Tác dụng**: Liệt kê các tiến trình (processes) trong hệ thống cùng PID.
*   **Tham số thường dùng**:
    *   `-w`: Hiển thị rộng (không cắt ngắn dòng lệnh quá dài).
*   **Ví dụ**: `ps`

### 5.2 `top` - Giám sát hệ thống thời gian thực
*   **Tác dụng**: Hiển thị CPU, RAM tiêu thụ và danh sách các tiến trình tiêu tốn tài nguyên nhất liên tục theo thời gian thực.
*   **Thao tác**: Nhấn `q` để thoát.
*   **Ví dụ**: `top`

### 5.3 `kill` - Gửi tín hiệu dừng tiến trình
*   **Tác dụng**: Gửi tín hiệu (mặc định là SIGTERM) để tắt một tiến trình dựa trên PID của nó.
*   **Tham số thường dùng**:
    *   `-9`: Gửi tín hiệu SIGKILL để tắt cưỡng chế ngay lập tức.
*   **Ví dụ**: `kill -9 123`

---

## 6. Các Lệnh Nén & Lưu Trữ (Archiving & Compression)

### 6.1 `tar` - Đóng gói và giải nén file
*   **Tác dụng**: Đóng gói nhiều file/thư mục thành 1 file duy nhất và ngược lại.
*   **Tham số thường dùng**:
    *   `-c`: Tạo file lưu trữ mới (create).
    *   `-x`: Giải nén file lưu trữ (extract).
    *   `-z`: Nén/Giải nén thông qua công cụ `gzip` (đuôi `.tar.gz`).
    *   `-v`: Hiển thị tiến trình chi tiết ra màn hình (verbose).
    *   `-f <tên_file>`: Tên file lưu trữ đích.
*   **Ví dụ giải nén**: `tar -xzvf /mnt/host/source.tar.gz -C /tmp/`

### 6.2 `gzip` / `gunzip` - Nén và giải nén file đơn
*   **Tác dụng**: Nén file gốc thành đuôi `.gz` hoặc giải nén ngược lại.
*   **Ví dụ**: `gzip file.txt` (nén ra `file.txt.gz`)

---

## 7. Bảng Tra Cứu Các Lệnh Khác Trong BusyBox

Dưới đây là tóm tắt nhanh các lệnh phụ trợ khác có trong bản build BusyBox của bạn:

| Lệnh | Mô Tả Tác Dụng |
| :--- | :--- |
| `chmod` | Thay đổi quyền truy cập file/thư mục (ví dụ `chmod +x run.sh`) |
| `chown` | Thay đổi chủ sở hữu và nhóm sở hữu của file |
| `clear` | Xóa sạch màn hình Terminal |
| `date` | Xem hoặc thiết lập thời gian hệ thống |
| `dd` | Sao chép và chuyển đổi file cấp thấp (thường dùng tạo image) |
| `find` | Tìm kiếm file trong thư mục theo tên, dung lượng, quyền hạn |
| `free` | Hiển thị dung lượng RAM trống và đã sử dụng của hệ thống |
| `hostname`| Xem hoặc cấu hình tên máy (hostname) của hệ thống |
| `ifconfig`| Xem và cấu hình các giao diện mạng (IP, Subnet mask, Up/Down) |
| `ping` | Kiểm tra kết nối mạng tới một địa chỉ IP/Domain |
| `poweroff`| Tắt máy ảo QEMU an toàn |
| `reboot` | Khởi động lại máy ảo |
| `route` | Quản lý bảng định tuyến mạng IP |
| `sleep` | Tạm dừng chạy lệnh trong một số giây chỉ định |
| `sync` | Ghi toàn bộ dữ liệu đệm từ RAM xuống ổ đĩa cứng vật lý |
| `uname` | Hiển thị thông tin hệ điều hành và phiên bản nhân Kernel |
| `uptime` | Xem thời gian hệ thống đã hoạt động liên tục kể từ khi khởi động |
| `wc` | Đếm số dòng, số từ, và số ký tự trong file văn bản |
| `wget` | Tải các file từ internet về máy (hỗ trợ HTTP, HTTPS, FTP) |
| `which` | Tìm đường dẫn tuyệt đối của một lệnh thực thi |
| `whoami` | Hiển thị tên người dùng hiện tại đang đăng nhập hệ thống |
| `xargs` | Xây dựng và thực thi các dòng lệnh từ đầu vào tiêu chuẩn |
