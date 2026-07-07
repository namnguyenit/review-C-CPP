#include <stdio.h>
#include <stdlib.h>
#include "../include/linklist.h"

Node *newnode(student data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (temp == NULL)
    {
        return NULL;
    }
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void khoi_tao(LinkList *list)
{
    if (list == NULL)
    {
        return;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int themdau(LinkList *list, student data)
{
    if (list == NULL)
    {
        return FAILURE;
    }
    Node *temp = newnode(data);
    if (temp == NULL)
    {
        fprintf(stderr, "Cap phat bo nho that bai\n");
        return FAILURE;
    }
    if (list->head == NULL)
    {
        list->head = temp;
        list->tail = temp;
    }
    else
    {
        temp->next = list->head;
        list->head = temp;
    }
    list->size++;
    return SUCCESS;
}

int demnode(Node *head)
{
    int count = 0;
    Node *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

int themcuoi(LinkList *list, student data)
{
    if (list == NULL)
    {
        return FAILURE;
    }
    Node *temp = newnode(data);
    if (temp == NULL)
    {
        fprintf(stderr, "Cap phat bo nho that bai\n");
        return FAILURE;
    }

    if (list->head == NULL)
    {
        list->head = temp;
        list->tail = temp;
    }
    else
    {
        list->tail->next = temp;
        list->tail = temp;
    }
    list->size++;
    return SUCCESS;
}

int themgiua(LinkList *list, student data, int vt)
{
    if (list == NULL || vt < 0 || vt > list->size)
    {
        return FAILURE;
    }
    if (vt == 0)
    {
        themdau(list, data);
        return SUCCESS;
    }
    if (vt == list->size)
    {
        themcuoi(list, data);
        return SUCCESS;
    }

    Node *temp = newnode(data);
    if (temp == NULL)
    {
        fprintf(stderr, "Cap phat bo nho that bai\n");
        return FAILURE;
    }

    Node *t = list->head;

    for (int i = 0; i < vt - 1; i++)
    {
        t = t->next;
    }
    temp->next = t->next;
    t->next = temp;
    list->size++;
    return SUCCESS;
}

int xoadau(LinkList *list)
{
    if (list == NULL || list->head == NULL)
        return FAILURE;
    Node *temp = list->head;
    list->head = list->head->next;
    if (list->head == NULL)
    {
        list->tail = NULL;
    }
    list->size--;
    free(temp);
    return SUCCESS;
}

int xoacuoi(LinkList *list)
{
    if (list == NULL || list->head == NULL)
        return FAILURE;
    Node *temp = list->head;
    if (temp->next == NULL)
    {
        free(temp);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return SUCCESS;
    }
    Node *prev = NULL;
    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    free(temp);
    list->tail = prev;
    list->size--;
    return SUCCESS;
}

int xoagiua(LinkList *list, int vt)
{
    if (list == NULL || vt < 0 || vt > list->size)
        return FAILURE;

    if (vt == 0)
    {
        return xoadau(list);
    }
    if (vt == list->size - 1)
    {
        return xoacuoi(list);
    }
    Node *temp = list->head;
    Node *prev = NULL;
    for (int i = 0; i < vt; i++)
    {
        prev = temp;
        temp = temp->next;
    }
    prev->next = temp->next;
    free(temp);
    list->size--;
    return SUCCESS;
}

void xoa_list(LinkList *list)
{
    if (list == NULL)
    {
        return;
    }
    Node *temp = list->head;
    while (temp != NULL)
    {
        Node *next_node = temp->next;
        free(temp);
        temp = next_node;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void freeall(Node **head)
{
    if (head == NULL || *head == NULL)
        return;
    Node *temp = *head;
    Node *next_node;
    *head = NULL;
    while (temp != NULL)
    {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    }
}

Node *search(LinkList *list, searchCB cb)
{
    if (list == NULL || cb == NULL)
    {
        return NULL;
    }
    Node *temp = list->head;
    while (temp != NULL)
    {
        if (cb(temp->data))
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void all(LinkList *list, studentCB cb)
{
    if (list == NULL || cb == NULL)
    {
        return;
    }
    Node *temp = list->head;
    while (temp != NULL)
    {
        cb(temp->data);
        temp = temp->next;
    }
}

void arrange(LinkList *list, arrangeCB cb)
{
    if (list == NULL || list->size < 2 || cb == NULL)
    {
        return;
    }
    for (Node *i = list->head; i != NULL; i = i->next)
    {
        for (Node *j = i->next; j != NULL; j = j->next)
        {
            if (cb(i->data, j->data) > 0)
            {
                student temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}
