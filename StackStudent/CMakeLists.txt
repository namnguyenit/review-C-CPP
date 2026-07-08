cmake_minimum_required(VERSION 3.10)

# Khai báo dự án sử dụng cả C và C++
project(StackStudentApp C CXX)

# Yêu cầu chuẩn C++11 (thay cho cờ -std=c++11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Liệt kê các file mã nguồn
set(SOURCES
    main.cpp
    src/StackStudent.cpp
    ../linklist/src/linklist.c
    ../linklist/src/student.c
)

# 2. Tạo ra tệp thực thi tên là "app" từ danh sách SOURCES
add_executable(app ${SOURCES})

# 3. Chỉ định các thư mục chứa file Header (.h / .hpp)
# Lệnh này thay thế cho cờ -Iinclude và -I../linklist/include
target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../linklist/include
)
