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







int main() {
    LinkList my_list;
    khoi_tao(&my_list);
    int choice;

    do {
        printf("\033[2J\033[H");
        printf("\n===== MENU =====\n");
        printf("1. Them dau\n");
        printf("2. Them cuoi\n");
        printf("3. Them giua\n");
        printf("4. Xoa dau\n");
        printf("5. Xoa cuoi\n");
        printf("6. Xoa giua\n");
        printf("7. Cap nhat sinh vien\n");
        printf("8. Tim kiem theo ID\n");
        printf("9. Xem toan bo\n");
        printf("10. Sap xep theo GPA (Giam dan)\n");
        printf("11. Sap xep theo Ten (A-Z)\n");
        printf("0. Thoat\n");
        printf("Chon: ");

        if (scanf("%d", &choice) != 1) {
            printf("Lua chon khong hop le!\n");
            clearInputBuffer();
            pauseScreen();
            continue;
        }
        clearInputBuffer();

        if (choice == 1) {
            student s;
            nhap_student(&s);
            if (themdau(&my_list, s)) printf("Them thanh cong!\n");
            else printf("Them that bai!\n");
            pauseScreen();
        } else if (choice == 2) {
            student s;
            nhap_student(&s);
            if (themcuoi(&my_list, s)) printf("Them thanh cong!\n");
            else printf("Them that bai!\n");
            pauseScreen();
        } else if (choice == 3) {
            student s;
            int vt;
            nhap_student(&s);
            printf("Nhap vi tri chen: ");
            if (scanf("%d", &vt) == 1) {
                clearInputBuffer();
                if (themgiua(&my_list, s, vt)) printf("Them thanh cong!\n");
                else printf("Vi tri khong hop le hoac loi bo nho!\n");
            } else {
                clearInputBuffer();
                printf("Vi tri khong hop le!\n");
            }
            pauseScreen();
        } else if (choice == 4) {
            if (xoadau(&my_list)) printf("Xoa thanh cong!\n");
            else printf("Danh sach rong!\n");
            pauseScreen();
        } else if (choice == 5) {
            if (xoacuoi(&my_list)) printf("Xoa thanh cong!\n");
            else printf("Danh sach rong!\n");
            pauseScreen();
        } else if (choice == 6) {
            int vt;
            printf("Nhap vi tri xoa: ");
            if (scanf("%d", &vt) == 1) {
                clearInputBuffer();
                if (xoagiua(&my_list, vt)) printf("Xoa thanh cong!\n");
                else printf("Vi tri khong hop le!\n");
            } else {
                clearInputBuffer();
                printf("Vi tri khong hop le!\n");
            }
            pauseScreen();
        } else if (choice == 7) {
            printf("Nhap ID sinh vien can cap nhat: ");
            if (scanf("%d", &target_id) == 1) {
                clearInputBuffer();
                Node *found = search(&my_list, tim_theo_id);
                if (found != NULL) {
                    student new_info;
                    printf("Nhap thong tin moi:\n");
                    nhap_student(&new_info);
                    cn_student(&(found->data), &new_info);
                    printf("Cap nhat thanh cong!\n");
                } else {
                    printf("Khong tim thay sinh vien co ID = %d!\n", target_id);
                }
            } else {
                clearInputBuffer();
                printf("ID khong hop le!\n");
            }
            pauseScreen();
        } else if (choice == 8) {
            printf("Nhap ID can tim: ");
            if (scanf("%d", &target_id) == 1) {
                clearInputBuffer();
                Node *found = search(&my_list, tim_theo_id);
                if (found != NULL) {
                    printf("DA TIM THAY:\n");
                    in_student(found->data);
                } else {
                    printf("Khong tim thay sinh vien co ID = %d!\n", target_id);
                }
            } else {
                clearInputBuffer();
                printf("ID khong hop le!\n");
            }
            pauseScreen();
        } else if (choice == 9) {
            printf("\n===== DANH SACH SINH VIEN =====\n");
            all(&my_list, in_sinh_vien_cb);
            pauseScreen();
        } else if (choice == 10) {
            arrange(&my_list, so_sanh_gpa_giam_dan);
            printf("Da sap xep theo GPA giam dan!\n");
            pauseScreen();
        } else if (choice == 11) {
            arrange(&my_list, so_sanh_ten_tang_dan);
            printf("Da sap xep theo Ten tu A-Z!\n");
            pauseScreen();
        } else if (choice == 0) {
            printf("Thoat chuong trinh!\n");
        } else {
            printf("Lua chon khong hop le!\n");
            pauseScreen();
        }
    } while (choice != 0);

    xoa_list(&my_list);
    return 0;
}
