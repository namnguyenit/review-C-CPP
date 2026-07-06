#ifndef LINKLIST_H
#define LINKLIST_H

#include "student.h"


typedef struct Node {
  student data;
  struct Node *next;
} Node;

typedef struct LinkList{
  Node *head;
  Node *tail;
  int size;
} LinkList;


Node *newnode(student data);

void khoi_tao(LinkList *list);
void xoa_list(LinkList *list);

int themdau(LinkList *list, student data);
int themcuoi(LinkList *list, student data);
int themgiua(LinkList *list, student data, int vt);

int xoadau (LinkList *list);
int xoacuoi(LinkList *list);
int xoagiua(LinkList *list, int vt);


typedef void (*studentCB)(student s);
void all(LinkList *list, studentCB cb);
typedef int (*searchCB)(student s);
Node* search (LinkList *list, searchCB cb);
typedef int (*arrangeCB) (student s1, student s2);
void arrange (LinkList *list, arrangeCB cb);


// void capnhat(Node *head, student data, int vt);
// void xemnode (Node * head, int vt);
// void xemtoanbo(Node *head);
void freeall(Node **head);
int demnode(Node *head);
#endif