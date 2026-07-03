#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"
 // danh sách liên kết đơn 
Node *newnode(student data){
    Node *temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        return NULL;
    }
    temp->data=data;
    temp->next=NULL;
    return temp;
}

void themdau(Node **head, student data){
    Node *temp = newnode(data);
    if (temp == NULL) {
        fprintf(stderr, "Cap phat bo nho that bai\n");
        return;
    }
    if(*head == NULL){
        *head = temp; 
    }else{
        temp->next=*head;
        *head = temp;
    }
}
int demnode(Node *head){
    int count = 0;
    Node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}
void themcuoi(Node **head, student data){
    Node *temp = newnode(data);
    if (temp == NULL) {
        fprintf(stderr, "Cap phat bo nho that bai\n");
        return;
    }
    
    if(*head == NULL){
        *head = temp; 
    }else{
        Node *t = *head;
        while(t->next != NULL){
            t=t->next;
        }
        t->next=temp;
    }
}
void themgiua(Node **head, student data, int vt){
    if (vt < 0 || vt > demnode(*head)) {
        printf("Vi tri chen khong hop le.\n");
        return;
    }

    if (vt == 0) {
        themdau(head, data);
        return;
    }
    Node *temp = newnode(data);
    if (temp == NULL) {
        fprintf(stderr, "Cap phat bo nho that bai\n");
        return;
    }

    Node *t = *head;
    int count = 0;
    while(count < vt-1 ){
        t=t->next;
        count++;
    }
    temp->next=t->next;
    t->next=temp;
}

void xoadau (Node **head){
    if(head == NULL || *head == NULL)  return ;
    Node *temp = *head;
    *head = temp->next;
    free(temp);
}
void xoacuoi(Node **head){
    if(head == NULL || *head == NULL)  return ;
    Node *temp = *head;
    Node *prev = NULL;
    if (temp->next == NULL) {
        free(temp);
        *head = NULL;
        return;
    }
    while(temp->next != NULL){
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    free(temp);
}

void xoagiua(Node **head, int vt){
    if(head == NULL || *head == NULL)  return ;
    if (vt < 0 || vt >= demnode(*head)) {
        printf("Vi tri xoa khong hop le.\n");
        return;
    }
    if(*head == NULL) return ;
    Node *temp = *head;
    Node *prev = NULL;
    int count = 0;
    if (vt == 0) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (count < vt){
        prev = temp;
        temp = temp->next;
        count++;
    }
    prev->next = temp->next;
    free(temp);
}

void capnhat(Node *head, student data, int vt){
    if (vt < 0 || vt >= demnode(head)) {
        printf("Vi tri cap nhat khong hop le.\n");
        return;
    }

    if(head == NULL) return ;
    Node *temp = head;
    int count = 0;
    while(count < vt ){
        temp = temp->next;
        count++;
    }
    temp->data = data;
}
void xemnode (Node * head, int vt){
    if (vt < 0 || vt >= demnode(head)) {
        printf("Vi tri xem khong hop le.\n");
        return;
    }
    if(head == NULL) return ;
    Node *temp = head;
    int count = 0;
    while(count < vt ){
        temp = temp->next;
        count++;
    }
    printf("ID: %d\n", temp->data.id);
    printf("Name: %s\n", temp->data.name);
    printf("Age: %d\n", temp->data.age);
    printf("Class: %d\n", temp->data.clas);
    printf("GPA: %.2f\n", temp->data.gpa);
}
void xemtoanbo(Node *head){
    if(head == NULL) return ;
    Node *temp = head;
    while (temp!=NULL)
    {
        printf("ID: %d\n", temp->data.id);
        printf("Name: %s\n", temp->data.name);
        printf("Age: %d\n", temp->data.age);
        printf("Class: %d\n", temp->data.clas);
        printf("GPA: %.2f\n", temp->data.gpa);
        temp = temp->next;
    }
}
void freeall(Node **head) {
    if (head == NULL || *head == NULL) return;
    Node *temp = *head;
    Node *next_node;    
    *head = NULL;
    while (temp != NULL) {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    }
}
