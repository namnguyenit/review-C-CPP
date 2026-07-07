#include <stdio.h>
#include "include/linklist.h"
#include "include/student.h"
#define CLEAR_SCREEN "\033[2J\033[H"
void in_sinh_vien_cb(student s)
{
    in_student(s);
}

int so_sanh_gpa_giam_dan(student s1, student s2)
{
    return ss_by_gpa(s1, s2);
}

int so_sanh_ten_tang_dan(student s1, student s2)
{
    return ss_by_name(s1, s2);
}

int target_id = 0;

int tim_theo_id(student s)
{
    return s.id == target_id;
}
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
void pauseScreen()
{
    printf("\nNhan Enter de tiep tuc...");
    getchar();
}

int main()
{
    LinkList my_list;
    khoi_tao(&my_list);
    int choice;

    do
    {
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

        if (scanf("%d", &choice) != 1)
        {
            printf("Lua chon khong hop le!\n");
            clearInputBuffer();
            pauseScreen();
            continue;
        }
        clearInputBuffer();

        if (choice == 1)
        {
            student s;
            nhap_student(&s);
            if (themdau(&my_list, s))
                printf("Them thanh cong!\n");
            else
                printf("Them that bai!\n");
            pauseScreen();
        }
        else if (choice == 2)
        {
            student s;
            nhap_student(&s);
            if (themcuoi(&my_list, s))
                printf("Them thanh cong!\n");
            else
                printf("Them that bai!\n");
            pauseScreen();
        }
        else if (choice == 3)
        {
            student s;
            int vt;
            nhap_student(&s);
            printf("Nhap vi tri chen: ");
            if (scanf("%d", &vt) == 1)
            {
                clearInputBuffer();
                if (themgiua(&my_list, s, vt))
                    printf("Them thanh cong!\n");
                else
                    printf("Vi tri khong hop le hoac loi bo nho!\n");
            }
            else
            {
                clearInputBuffer();
                printf("Vi tri khong hop le!\n");
            }
            pauseScreen();
        }
        else if (choice == 4)
        {
            if (xoadau(&my_list))
                printf("Xoa thanh cong!\n");
            else
                printf("Danh sach rong!\n");
            pauseScreen();
        }
        else if (choice == 5)
        {
            if (xoacuoi(&my_list))
                printf("Xoa thanh cong!\n");
            else
                printf("Danh sach rong!\n");
            pauseScreen();
        }
        else if (choice == 6)
        {
            int vt;
            printf("Nhap vi tri xoa: ");
            if (scanf("%d", &vt) == 1)
            {
                clearInputBuffer();
                if (xoagiua(&my_list, vt))
                    printf("Xoa thanh cong!\n");
                else
                    printf("Vi tri khong hop le!\n");
            }
            else
            {
                clearInputBuffer();
                printf("Vi tri khong hop le!\n");
            }
            pauseScreen();
        }
        else if (choice == 7)
        {
            printf("Nhap ID sinh vien can cap nhat: ");
            if (scanf("%d", &target_id) == 1)
            {
                clearInputBuffer();
                Node *found = search(&my_list, tim_theo_id);
                if (found != NULL)
                {
                    student new_info;
                    printf("Nhap thong tin moi:\n");
                    nhap_student(&new_info);
                    cn_student(&(found->data), &new_info);
                    printf("Cap nhat thanh cong!\n");
                }
                else
                {
                    printf("Khong tim thay sinh vien co ID = %d!\n", target_id);
                }
            }
            else
            {
                clearInputBuffer();
                printf("ID khong hop le!\n");
            }
            pauseScreen();
        }
        else if (choice == 8)
        {
            printf("Nhap ID can tim: ");
            if (scanf("%d", &target_id) == 1)
            {
                clearInputBuffer();
                Node *found = search(&my_list, tim_theo_id);
                if (found != NULL)
                {
                    printf("DA TIM THAY:\n");
                    in_student(found->data);
                }
                else
                {
                    printf("Khong tim thay sinh vien co ID = %d!\n", target_id);
                }
            }
            else
            {
                clearInputBuffer();
                printf("ID khong hop le!\n");
            }
            pauseScreen();
        }
        else if (choice == 9)
        {
            printf("\n===== DANH SACH SINH VIEN =====\n");
            all(&my_list, in_sinh_vien_cb);
            pauseScreen();
        }
        else if (choice == 10)
        {
            arrange(&my_list, so_sanh_gpa_giam_dan);
            printf("Da sap xep theo GPA giam dan!\n");
            pauseScreen();
        }
        else if (choice == 11)
        {
            arrange(&my_list, so_sanh_ten_tang_dan);
            printf("Da sap xep theo Ten tu A-Z!\n");
            pauseScreen();
        }
        else if (choice == 0)
        {
            printf("Thoat chuong trinh!\n");
        }
        else
        {
            printf("Lua chon khong hop le!\n");
            pauseScreen();
        }
    } while (choice != 0);

    xoa_list(&my_list);
    return 0;
}

// int main() {
//     // LinkList my_list;
//     // khoi_tao(&my_list);

//     // printf("--- KHOI TAO & THEM TEST DATA ---\n");
//     // themcuoi(&my_list, tao_student(101, "Nguyen Van An", 20, 12, 8.2));
//     // themcuoi(&my_list, tao_student(102, "Tran Thi Binh", 21, 12, 9.5));
//     // themdau(&my_list,  tao_student(103, "Le Van Cuong", 19, 11, 7.8));

//     // printf("\nDanh sach ban dau:\n");
//     // all(&my_list, in_sinh_vien_cb);

//     // printf("\n--- TEST: SAP XEP THEO GPA GIAM DAN ---\n");
//     // arrange(&my_list, so_sanh_gpa_giam_dan);
//     // all(&my_list, in_sinh_vien_cb);

//     // printf("\n--- TEST: SAP XEP THEO TEN TANG DAN (A-Z) ---\n");
//     // arrange(&my_list, so_sanh_ten_tang_dan);
//     // all(&my_list, in_sinh_vien_cb);

//     // printf("\n--- TEST: TIM KIEM THEO ID ---\n");
//     // target_id = 102;
//     // printf("Tim kiem sinh vien co ID = %d:\n", target_id);
//     // Node *found = search(&my_list, tim_theo_id);
//     // if (found != NULL) {
//     //     printf("TIM THAY: ");
//     //     in_student(found->data);
//     // } else {
//     //     printf("Khong tim thay sinh vien co ID = %d\n", target_id);
//     // }

//     // printf("\n--- TEST: XOA DAU VA XOA CUOI ---\n");
//     // printf("Xoa phan tu dau tien...\n");
//     // xoadau(&my_list);
//     // printf("Xoa phan tu cuoi cung...\n");
//     // xoacuoi(&my_list);

//     // printf("Danh sach con lai:\n");
//     // all(&my_list, in_sinh_vien_cb);

//     // xoa_list(&my_list);
//     // printf("\nDa giai phong danh sach!\n");

//     return 0;
// }