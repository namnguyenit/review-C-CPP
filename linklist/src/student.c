#include <stdio.h>
#include <string.h>
#include "../include/student.h"

void nhap_student(student *s)
{
    if (s == NULL)
        return;

    printf("Nhap ID: ");
    scanf("%d", &s->id);
    getchar();

    printf("Nhap ten: ");
    fgets(s->name, sizeof(s->name), stdin);
    s->name[strcspn(s->name, "\n")] = '\0';

    printf("Nhap tuoi: ");
    scanf("%d", &s->age);

    printf("Nhap lop: ");
    scanf("%d", &s->clas);

    printf("Nhap GPA: ");
    scanf("%f", &s->gpa);
    getchar();
}
student tao_student(int id, const char *name, int age, int clas, float gpa)
{
    student s;
    s.id = id;
    strncpy(s.name, name, sizeof(s.name) - 1);
    s.name[sizeof(s.name) - 1] = '\0';
    s.age = age;
    s.clas = clas;
    s.gpa = gpa;
    return s;
}

void in_student(student s)
{
    printf("ID: %d | Ten: %-15s | Tuoi: %d | Lop: %d | GPA: %.2f\n",
           s.id, s.name, s.age, s.clas, s.gpa);
}

void cn_student(student *s, const student *new_data)
{
    if (s == NULL || new_data == NULL)
        return;
    s->id = new_data->id;
    strcpy(s->name, new_data->name);
    s->age = new_data->age;
    s->clas = new_data->clas;
    s->gpa = new_data->gpa;
}

int ss_by_gpa(student s1, student s2)
{
    if (s1.gpa < s2.gpa)
        return 1;
    if (s1.gpa > s2.gpa)
        return -1;
    return 0;
}

int ss_by_name(student s1, student s2)
{
    return strcmp(s1.name, s2.name);
}

int ss_by_id(student s1, student s2)
{
    return s1.id - s2.id;
}
