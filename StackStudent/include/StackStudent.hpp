#ifndef STACK_STUDENT_HPP
#define STACK_STUDENT_HPP

// Khai báo liên kết C
extern "C" {
    #include "linklist.h"
    #include "student.h"
}

class StackStudent {
private:
    LinkList list; // Cấu trúc dữ liệu lưu trữ của C

public:
    // Chỉ khai báo nguyên mẫu hàm (Prototype)
    StackStudent();
    ~StackStudent();

    // Copy Constructor & Assignment Operator (Deep Copy)
    StackStudent(const StackStudent& other);
    StackStudent& operator=(const StackStudent& other);

    void push(student s);
    void pop();
    student top() const;
    bool isEmpty() const;
    int size() const;
};

#endif // STACK_STUDENT_HPP
