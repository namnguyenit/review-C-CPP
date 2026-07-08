#include <iostream>
#include "include/StackStudent.hpp"

int main() {
    StackStudent stack;

    try {
        std::cout << "--- THEM HOC SINH VAO STACK ---\n";
        stack.push(tao_student(1, "Nguyen Van An", 20, 12, 8.5));
        stack.push(tao_student(2, "Tran Thi Binh", 21, 12, 9.2));
        stack.push(tao_student(3, "Le Van Cuong", 19, 11, 7.8));

        std::cout << "Kich thuoc Stack hien tai: " << stack.size() << std::endl;

        std::cout << "\n--- TEST DEEP COPY ---\n";
        {
            StackStudent stack2 = stack; // Copy Constructor
            std::cout << "Kich thuoc stack2 (copy): " << stack2.size() << " | Top: " << stack2.top().name << std::endl;
            
            StackStudent stack3;
            stack3 = stack; // Copy Assignment Operator
            std::cout << "Kich thuoc stack3 (gan): " << stack3.size() << " | Top: " << stack3.top().name << std::endl;
        } // Hết scope này stack2 và stack3 tự giải phóng bộ nhớ mà không ảnh hưởng đến stack gốc
        std::cout << "Giai phong stack2 va stack3 thanh cong (khong bi double free)!\n";

        std::cout << "\n--- LAY DU LIEU TU STACK (LIFO) ---\n";
        while (!stack.isEmpty()) {
            student topStudent = stack.top();
            std::cout << "Top Student: " << topStudent.name << " - GPA: " << topStudent.gpa << std::endl;
            stack.pop();
        }

        std::cout << "\nKich thuoc Stack sau khi pop het: " << stack.size() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Bat duoc ngoai le: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
