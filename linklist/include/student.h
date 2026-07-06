#ifndef STUDENT_H
#define STUDENT_H

typedef struct student {
    int id;
    char name[50];
    int age;
    int clas;
    float gpa;
} student;


void nhap_student(student *s);
void in_student(student s);
void cn_student(student *s, const student *new_data);

int ss_by_gpa(student s1, student s2);
int ss_by_name(student s1, student s2);
int ss_by_id(student s1, student s2);

#endif
