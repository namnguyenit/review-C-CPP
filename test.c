#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
}

struct node *newnode(int data){
    struct node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->node = NULL;
    return *temp;
}

struct node *themnode(struct node **head, int data){
    struct node *temp = newnode(data);
    if (*head == NULL ){
        temp->next =  temp;
        *head = temp;
    }else{
        struct node *t = *head;
        while (t->next != temp)
    }

}

int main(){
    printf("Test\n");
}