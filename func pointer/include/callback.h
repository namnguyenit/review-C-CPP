#ifndef CALLBACK_H
#define CALLBACK_H

typedef void (*buttonCallback)(void);

void ledOn(void);
void ledOff(void);
void printHello(void);

typedef struct
{
    char *name;
    buttonCallback callback;

} callBackEvent;

extern callBackEvent callBackTable[];
extern const int callBackCount;

#endif