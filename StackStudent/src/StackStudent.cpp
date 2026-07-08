#include "../include/StackStudent.hpp"
#include <stdexcept>

// Triển khai Constructor
StackStudent::StackStudent() {
    khoi_tao(&list);
}

// Triển khai Destructor
StackStudent::~StackStudent() {
    xoa_list(&list);
}

// Triển khai Copy Constructor (Deep Copy)
StackStudent::StackStudent(const StackStudent& other) {
    khoi_tao(&list);
    Node* temp = other.list.head;
    while (temp != NULL) {
        themcuoi(&list, temp->data);
        temp = temp->next;
    }
}

// Triển khai Copy Assignment Operator (Deep Copy)
StackStudent& StackStudent::operator=(const StackStudent& other) {
    if (this != &other) {
        xoa_list(&list);
        Node* temp = other.list.head;
        while (temp != NULL) {
            themcuoi(&list, temp->data);
            temp = temp->next;
        }
    }
    return *this;
}

// Triển khai hàm push
void StackStudent::push(student s) {
    if (themcuoi(&list, s) == FAILURE) {
        throw std::runtime_error("Loi: Khong the cap phat bo nho cho Stack!");
    }
}

// Triển khai hàm pop
void StackStudent::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Loi: Stack dang rong, khong the pop!");
    }
    xoacuoi(&list);
}

// Triển khai hàm top
student StackStudent::top() const {
    if (isEmpty()) {
        throw std::out_of_range("Loi: Stack dang rong, khong the xem top!");
    }
    return list.tail->data;
}

// Triển khai hàm isEmpty
bool StackStudent::isEmpty() const {
    return list.head == NULL;
}

// Triển khai hàm size
int StackStudent::size() const {
    return list.size;
}
