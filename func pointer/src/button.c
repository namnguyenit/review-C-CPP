#include <stdio.h>
#include "button.h"

static buttonCallback buttonCb = NULL;

void dkButtonCallback(buttonCallback cb)
{
    buttonCb = cb;
}

void nhanNut(void)
{
    if (buttonCb == NULL)
    {
        printf("Khong co callback nao duoc dang ky.\n");
        return;
    }

    buttonCb();
}