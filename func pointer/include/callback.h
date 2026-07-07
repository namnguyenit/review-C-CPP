#ifndef CALLBACK_H
#define CALLBACK_H

typedef void (*buttonCallback)(void);

/// @brief Ham callback bat den LED
void ledOn(void);

/// @brief Ham callback tat den LED
void ledOff(void);

/// @brief Ham callback in ra chuoi "Hello"
void printHello(void);

typedef struct
{
    char *name;
    buttonCallback callback;

} callBackEvent;

extern callBackEvent callBackTable[];
extern const int callBackCount;

#endif