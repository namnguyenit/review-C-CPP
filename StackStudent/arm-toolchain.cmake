# 1. Khai báo Hệ điều hành và Kiến trúc đích
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 2. Khai báo trình biên dịch C và C++ cho ARM (Cross-Compiler)
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

# 3. Hành vi tìm kiếm thư viện:
# - Chương trình host (ví dụ: make, cmake) lấy ở máy gốc (NEVER tìm ở ARM)
# - Thư viện (.so, .a) và Header (.h) BẮT BUỘC lấy ở thư mục gốc của ARM (ONLY), tránh nhầm với thư viện x86
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
