#include <stdio.h>
#include "cmsis_os2.h"
#include "ohos_init.h"

void TaskA(void *arg)
{
    (void)arg;
    while(1)
    {
        printf("====TaskA running====\r\n");
        osDelay(100);
    }
}

void TaskB(void *arg)
{
    (void)arg;
    while(1)
    {
        printf("-----TaskB running-----\r\n");
        osDelay(200);
    }
}

static void MultiTaskDemo(void)
{
    osThreadAttr_t attr;
    attr.name = "TaskA";
    attr.stack_size = 1024;
    attr.priority = osPriorityNormal;
    osThreadNew(TaskA,NULL,&attr);

    attr.name = "TaskB";
    attr.stack_size = 1024;
    attr.priority = osPriorityNormal;
    osThreadNew(TaskB,NULL,&attr);
}

SYS_RUN(MultiTaskDemo);
