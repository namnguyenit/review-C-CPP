#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LENGTH 50

typedef struct student
{
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    int clas;
    float gpa;
} student;

/// @brief Nhap thong tin cho mot sinh vien tu ban phim
/// @param s Con tro den cau truc sinh vien can nhap thong tin
void nhap_student(student *s);

/// @brief In thong tin cua mot sinh vien ra man hinh
/// @param s Cau truc sinh vien can in thong tin
void in_student(student s);

/// @brief Cap nhat thong tin sinh vien bang du lieu moi
/// @param s Con tro den sinh vien can cap nhat
/// @param new_data Con tro den du lieu moi dung de cap nhat
void cn_student(student *s, const student *new_data);

/// @brief Khoi tao va tra ve mot cau truc sinh vien voi cac thong so cho truoc
/// @param id Ma so sinh vien
/// @param name Ten sinh vien
/// @param age Tuoi sinh vien
/// @param clas Lop hoc cua sinh vien
/// @param gpa Diem trung binh tich luy
/// @return Cau truc sinh vien duoc khoi tao
student tao_student(int id, const char *name, int age, int clas, float gpa);

/// @brief So sanh hai sinh vien theo diem GPA
/// @param s1 Sinh vien thu nhat
/// @param s2 Sinh vien thu hai
/// @return Tra ve >0 neu s1.gpa < s2.gpa, <0 neu s1.gpa > s2.gpa, va 0 neu bang nhau
int ss_by_gpa(student s1, student s2);

/// @brief So sanh hai sinh vien theo ten
/// @param s1 Sinh vien thu nhat
/// @param s2 Sinh vien thu hai
/// @return Tra ve ket qua so sanh ten theo thu tu tu dien
int ss_by_name(student s1, student s2);

/// @brief So sanh hai sinh vien theo ID
/// @param s1 Sinh vien thu nhat
/// @param s2 Sinh vien thu hai
/// @return Tra ve hieu cua id s1 va id s2
int ss_by_id(student s1, student s2);

#endif
