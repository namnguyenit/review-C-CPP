#ifndef LINKLIST_H
#define LINKLIST_H

#include "student.h"


typedef struct Node {
   student data;
  struct Node *next;
} Node;

Node *newnode(student data);

void themdau(Node ** head, student data);
void themcuoi(Node **head, student data);
void themgiua(Node ** head, student data, int vt);
void xoadau (Node **head);
void xoacuoi(Node **head);
void xoagiua(Node **head, int vt);
void capnhat(Node *head, student data, int vt);
void xemnode (Node * head, int vt);
void xemtoanbo(Node *head);
void freeall(Node **head);
int demnode(Node *head);
#endif