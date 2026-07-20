#!/bin/bash
set -e

#=============================================================
# build_rootfs.sh - Tạo initramfs cho Android Kernel trên QEMU
#=============================================================

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
KERNEL_ROOT="$(dirname "$SCRIPT_DIR")"
OUTDIR="$SCRIPT_DIR"

echo "============================================="
echo "  Tạo Initramfs cho Android Kernel + QEMU"
echo "============================================="

# 1. Tạo cấu trúc thư mục
echo "[1/5] Tạo cấu trúc thư mục rootfs..."
rm -rf "$OUTDIR/initramfs" "$OUTDIR/initramfs.cpio.gz"
mkdir -p "$OUTDIR/initramfs"/{bin,sbin,etc,proc,sys,dev,tmp,lib,mnt/host,usr/bin,usr/sbin,modules}

# 2. Sao chép BusyBox (static)
echo "[2/5] Sao chép BusyBox..."
if [ -f /usr/bin/busybox ]; then
    cp /usr/bin/busybox "$OUTDIR/initramfs/bin/"
else
    echo "LỖI: Không tìm thấy /usr/bin/busybox. Cài đặt: sudo apt install busybox-static"
    exit 1
fi

# 3. Tạo script /init
echo "[3/5] Tạo script /init..."
cat << 'INIT_EOF' > "$OUTDIR/initramfs/init"
#!/bin/busybox sh

# Cài đặt symlinks cho BusyBox (ls, cat, mount, sh, ...)
/bin/busybox --install -s /bin

# Mount các filesystem cần thiết
mount -t proc     none /proc
mount -t sysfs    none /sys
mount -t devtmpfs none /dev 2>/dev/null || true

# Thiết lập hotplug để tự tạo device nodes
echo /bin/mdev > /proc/sys/kernel/hotplug 2>/dev/null || true
mdev -s

# Nạp các module nếu có trong /modules/ (chạy 3 lần để giải quyết phụ thuộc/dependency)
for i in 1 2 3; do
    for mod in /modules/*.ko; do
        [ -f "$mod" ] && insmod "$mod" 2>/dev/null
    done
done

# Mount thư mục chia sẻ từ máy host (sử dụng tag shared_mount đã cấu hình ở QEMU)
mount -t 9p -o trans=virtio,version=9p2000.L shared_mount /mnt/host 2>/dev/null || echo "⚠ Không thể mount thư mục chia sẻ!"

# Hiển thị banner
cat <<'BANNER'

=============================================
  Android Kernel VM - BusyBox Shell
=============================================
  Gõ lệnh để tương tác với VM:
    insmod /modules/hello_module.ko
    dmesg | tail
    lsmod
    ls /
  Thoát QEMU: đóng cửa sổ hoặc gõ 'poweroff'
=============================================

BANNER

# Chuyển stdin/stdout/stderr sang console chính
# /dev/console tự động trỏ tới console= trong kernel args
exec 0</dev/console
exec 1>/dev/console
exec 2>/dev/console

# Khởi chạy shell tương tác
exec /bin/sh -i
INIT_EOF
chmod +x "$OUTDIR/initramfs/init"

# 4. Sao chép kernel modules
echo "[4/5] Sao chép kernel modules..."

# hello_module.ko (module bạn tự viết)
HELLO_KO="$KERNEL_ROOT/bazel-bin/mymodule/hello_module/hello_module.ko"
if [ -f "$HELLO_KO" ]; then
    cp "$HELLO_KO" "$OUTDIR/initramfs/modules/"
    echo "  ✓ hello_module.ko"
else
    echo "  ⚠ Không tìm thấy hello_module.ko tại $HELLO_KO"
fi

# Sao chép thêm các module .ko trong thư mục out/ (nếu có)
for ko in "$OUTDIR"/*.ko; do
    [ -f "$ko" ] && cp "$ko" "$OUTDIR/initramfs/modules/" && echo "  ✓ $(basename "$ko")"
done

# 5. Đóng gói initramfs
echo "[5/5] Đóng gói initramfs.cpio.gz..."
cd "$OUTDIR/initramfs"
find . -print0 | cpio --null -ov --format=newc 2>/dev/null | gzip -9 > "$OUTDIR/initramfs.cpio.gz"
cd "$OUTDIR"

echo ""
echo "✅ Hoàn tất! Initramfs: $OUTDIR/initramfs.cpio.gz"
echo "   Chạy: ./run_qemu.sh"
echo ""
