#include <stdio.h>
#include <string.h>
#include "review-C/include/linklist.h"

static void input_student(student *s) {
    if (s == NULL) {
        return;
    }

    printf("Nhap id: ");
    scanf("%d", &s->id);
    getchar();

    printf("Nhap ten: ");
    fgets(s->name, sizeof(s->name), stdin);
    s->name[strcspn(s->name, "\n")] = '\0';

    printf("Nhap tuoi: ");
    scanf("%d", &s->age);

    printf("Nhap lop: ");
    scanf("%d", &s->clas);

    printf("Nhap gpa: ");
    scanf("%f", &s->gpa);
    getchar();
}

static void print_menu(void) {
    printf("\n===== MENU =====\n");
    printf("1. Them dau\n");
    printf("2. Them cuoi\n");
    printf("3. Them giua\n");
    printf("4. Xoa dau\n");
    printf("5. Xoa cuoi\n");
    printf("6. Xoa giua\n");
    printf("7. Cap nhat\n");
    printf("8. Xem 1 node\n");
    printf("9. Xem toan bo\n");
    printf("0. Thoat\n");
    printf("Chon: ");
}

int main(void) {
    Node *head = NULL;
    int choice;

    do {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Du lieu khong hop le.\n");
            return 1;
        }
        getchar();

        if (choice == 1) {
            student s;
            input_student(&s);
            themdau(&head, s);
        } else if (choice == 2) {
            student s;
            input_student(&s);
            themcuoi(&head, s);
        } else if (choice == 3) {
            student s;
            int vt;
            input_student(&s);
            printf("Nhap vi tri chen (0-based): ");
            scanf("%d", &vt);
            getchar();
            themgiua(&head, s, vt);
        } else if (choice == 4) {
            xoadau(&head);
        } else if (choice == 5) {
            xoacuoi(&head);
        } else if (choice == 6) {
            int vt;
            printf("Nhap vi tri xoa (0-based): ");
            scanf("%d", &vt);
            getchar();
            xoagiua(&head, vt);
        } else if (choice == 7) {
            student s;
            int vt;
            input_student(&s);
            printf("Nhap vi tri cap nhat (0-based): ");
            scanf("%d", &vt);
            getchar();
            capnhat(head, s, vt);
        } else if (choice == 8) {
            int vt;
            printf("Nhap vi tri can xem (0-based): ");
            scanf("%d", &vt);
            getchar();
            xemnode(head, vt);
        } else if (choice == 9) {
            xemtoanbo(head);
        } else if (choice == 0) {
            printf("Ket thuc chuong trinh.\n");
        } else {
            printf("Lua chon khong hop le.\n");
        }
    } while (choice != 0);

    freeall(&head);
    return 0;
}
