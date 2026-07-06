#include <stdio.h>
#include "callback.h"

void ledOn(void)
{
    printf("LED ON\n");
}


void ledOff(void)
{
    printf("LED OFF\n");
}
void printHello(void)
{
    printf("Hello\n");
}

callBackEvent callBackTable[] =
{
    {"LED ON", ledOn},
    {"LED OFF", ledOff},
    {"Print Hello", printHello}
};

const int callBackCount = sizeof(callBackTable) / sizeof(callBackTable[0]);