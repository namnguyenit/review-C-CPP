#include <stdio.h>
#include "callback.h"
#include "button.h"

int main()
{

    int menu;
    int event;

    while (1)
    {
        printf("\033[2J\033[H");
        printf("\n===== MENU =====\n");
        printf("1. DK Button Callback\n");
        printf("2. Nhan Nut\n");
        printf("0. Exit\n");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            printf("\033[2J\033[H");
            printf("\n===== Callback Table =====\n");
            for (int i = 0; i < callBackCount; i++)
            {
                printf("%d, %s\n", i + 1, callBackTable[i].name);
            }
            printf("Chon su kien: ");
            scanf("%d", &event);
            if (event >= 1 && event <= callBackCount)
            {
                dkButtonCallback(
                    callBackTable[event - 1].callback);
            }
            printf("Dang ky su kien thanh cong!\n");
            while (getchar() != '\n')
                ;
            printf("\nNhan Enter de tiep tuc...");
            getchar();
            break;
        case 2:
            nhanNut();
            while (getchar() != '\n')
                ;
            printf("\nNhan Enter de tiep tuc...");
            getchar();
            break;
        case 0:
            return 0;
        default:
            printf("Lua chon khong hop le!\n");
            while (getchar() != '\n')
                ;
            printf("\nNhan Enter de tiep tuc...");
            getchar();
            break;
        }
    }
}