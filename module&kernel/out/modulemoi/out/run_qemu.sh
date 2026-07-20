#!/bin/bash

#=============================================================
# run_qemu.sh - Khởi chạy Android Kernel trên QEMU
#=============================================================

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BZIMAGE="$SCRIPT_DIR/bzImage"
INITRAMFS="$SCRIPT_DIR/initramfs.cpio.gz"
SHARED_DIR="$SCRIPT_DIR/share"
mkdir -p "$SHARED_DIR"

# Kiểm tra file cần thiết
if [ ! -f "$BZIMAGE" ]; then
    echo "LỖI: Không tìm thấy $BZIMAGE"
    echo "Hãy chạy: tools/bazel run //common-modules/virtual-device:virtual_device_x86_64_dist -- --destdir=out"
    exit 1
fi

if [ ! -f "$INITRAMFS" ]; then
    echo "LỖI: Không tìm thấy $INITRAMFS"
    echo "Hãy chạy: ./build_rootfs.sh"
    exit 1
fi

echo "============================================="
echo "  Khởi động Android Kernel trên QEMU"
echo "============================================="
echo "  Kernel:    $BZIMAGE"
echo "  Initramfs: $INITRAMFS"
echo ""
echo "  Cửa sổ QEMU sẽ hiện terminal."
echo "  Đóng cửa sổ QEMU để thoát."
echo "============================================="

qemu-system-x86_64 \
    -kernel "$BZIMAGE" \
    -initrd "$INITRAMFS" \
    -display gtk \
    -vga std \
    -append "console=ttyS0 console=tty0 loglevel=4" \
    -m 1024 \
    -enable-kvm \
    -cpu host \
    -smp 2 \
    -fsdev local,id=shared_dev,path="$SHARED_DIR",security_model=none \
    -device virtio-9p-pci,fsdev=shared_dev,mount_tag=shared_mount
