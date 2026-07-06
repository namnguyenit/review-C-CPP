#include<stdio.h>
#include<stdlib.h>
struct Node {
  int data;

  struct Node *next;
};

struct Node *newnode(int data){
  struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
  temp->data=data;

  temp->next=NULL;
  return temp;

}

void themnode(struct Node **head,int data){
  struct Node *temp = newnode(data);

  if(*head == NULL){
    temp->next=temp;
    *head = temp; 
  }else{
    struct Node *t = *head;
    while(t->next != *head){
      t=t->next;
    }
    t->next=temp;
    temp->next=*head;
  }
}
void duyett(struct Node *head){
    if(head == NULL) return ;
    struct Node *temp = head;
    struct Node *next_node;
    do{
        next_node = temp->next;
        printf("%d ", temp->data);
        temp = next_node;
    }while (temp != head);
}
void Free(struct Node *head) {
    if (head == NULL) return;  

    struct Node *temp = head;
    struct Node *next_node;

    
    do {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    } while (temp != head);
}

int main(){
  int n;
  scanf("%d" , &n);
  struct Node *head = NULL;
    for(int i =0 ; i< n;i++){
      int k;
      scanf("%d" , &k);
      themnode(&head,k);
    }
  
      duyett(head);
    Free(head);
}

