#ifndef STUDENT_H
#define STUDENT_H

typedef struct student
{
    int id;
    char name[50];
    int age;
    int clas;
    float gpa;
} student;

// void printall(student *s);
// void printstudent(student s, int id);   
// void createstudent(student *s, int id, const char *name, int age, int clas, float gpa);
// void deletestudent(student *s);
// void editstudent(student *s, int id, const char *name, int age, int clas, float gpa);
// void comparestudents(student *s1, student *s2);

#endif
