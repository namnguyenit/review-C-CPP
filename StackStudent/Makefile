
CXX = g++
CC = gcc
CXXFLAGS = -std=c++11 -Iinclude -I../linklist/include
CFLAGS = -I../linklist/include



# File chạy 'app' phụ thuộc vào các file .o nằm trong thư mục obj/
app:obj/main.o obj/StackStudent.o obj/linklist.o obj/student.o
	$(CXX) obj/main.o obj/StackStudent.o obj/linklist.o obj/student.o -o app


# Biên dịch main.cpp thành obj/main.o
obj/main.o: main.cpp include/StackStudent.hpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o obj/main.o

# Biên dịch StackStudent.cpp thành obj/StackStudent.o
obj/StackStudent.o: src/StackStudent.cpp include/StackStudent.hpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c src/StackStudent.cpp -o obj/StackStudent.o

# Biên dịch linklist.c thành obj/linklist.o
obj/linklist.o: ../linklist/src/linklist.c ../linklist/include/linklist.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c ../linklist/src/linklist.c -o obj/linklist.o

# Biên dịch student.c thành obj/student.o
obj/student.o: ../linklist/src/student.c ../linklist/include/student.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c ../linklist/src/student.c -o obj/student.o



# Xóa thư mục obj/ và file chạy app
clean:
	rm -rf obj app