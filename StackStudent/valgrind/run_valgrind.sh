#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

EXECUTABLE="../app"
if [ ! -f "$EXECUTABLE" ]; then
    EXECUTABLE="../bin/x86/app"
fi

if [ ! -f "$EXECUTABLE" ]; then
    echo "Lỗi: Không tìm thấy file thực thi 'app' tại ../app hoặc ../bin/x86/app"
    exit 1
fi

REPORT_FILE="valgrind_report.txt"

echo "Đang chạy valgrind để kiểm tra bộ nhớ cho: $EXECUTABLE"
echo "Báo cáo sẽ được lưu tại: $SCRIPT_DIR/$REPORT_FILE"
echo "----------------------------------------------------"

valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --verbose \
    --log-file="$REPORT_FILE" \
    "$EXECUTABLE"

echo "Hoàn thành. Bạn có thể xem kết quả bằng lệnh: cat $REPORT_FILE"
