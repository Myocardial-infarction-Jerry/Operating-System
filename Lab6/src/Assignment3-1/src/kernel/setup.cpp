#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "program.h"
#include "thread.h"
#include "sync.h"
#include "stdarg.h"

// 屏幕IO处理器
STDIO stdio;
// 中断管理器
InterruptManager interruptManager;
// 程序管理器
ProgramManager programManager;

const int N = 5;

SpinLock chopstick[N];
int full[N];

void delay(int val = 0xffffff)
{
    while (val)
        val--;
}

void philosopher(void *arg)
{
    int num = (int)(arg);
    chopstick[num].lock();
    printf("Liusenyuan %d pick up Chopstick %d\n", num, num);
    delay();
    chopstick[(num + 1) % N].lock();
    printf("Liusenyuan %d pick up Chopstick %d\n", num, (num + 1) % N);
    delay();
    printf("Liusenyuan %d is full\n");
    delay();
    chopstick[num].unlock();
    chopstick[(num + 1) % N].unlock();
    full[num] = 1;
}

void first_thread(void *arg)
{
    // 第1个线程不可以返回
    stdio.moveCursor(0);
    for (int i = 0; i < 25 * 80; ++i)
    {
        stdio.print(' ');
    }
    stdio.moveCursor(0);

    for (int i = 0; i < N; i++)
    {
        chopstick[i].initialize();
        full[i] = 0;
    }

    programManager.executeThread(philosopher, (void *)(0), "", 1);
    delay();
    programManager.executeThread(philosopher, (void *)(4), "", 1);
    programManager.executeThread(philosopher, (void *)(1), "", 1);
    programManager.executeThread(philosopher, (void *)(3), "", 1);
    programManager.executeThread(philosopher, (void *)(2), "", 1);

    int counter = 0;
    while (counter < N)
    {
        counter = 0;
        for (int i = 0; i < N; i++)
            counter += full[i];
    }

    printf("All the Liusenyuan are full! The 21307289th job has been done.\n");

    asm_halt();
}

extern "C" void setup_kernel()
{

    // 中断管理器
    interruptManager.initialize();
    interruptManager.enableTimeInterrupt();
    interruptManager.setTimeInterrupt((void *)asm_time_interrupt_handler);

    // 输出管理器
    stdio.initialize();

    // 进程/线程管理器
    programManager.initialize();

    // 创建第一个线程
    int pid = programManager.executeThread(first_thread, nullptr, "first thread", 1);
    if (pid == -1)
    {
        printf("can not execute thread\n");
        asm_halt();
    }

    ListItem *item = programManager.readyPrograms.front();
    PCB *firstThread = ListItem2PCB(item, tagInGeneralList);
    firstThread->status = RUNNING;
    programManager.readyPrograms.pop_front();
    programManager.running = firstThread;
    asm_switch_thread(0, firstThread);

    asm_halt();
}
