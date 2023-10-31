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

const int MALE = 6, FEMALE = 4;

Semaphore plate;
SpinLock A, B;
int matcha, mango;

void delay(int val = 0xffffff)
{
    while (val)
        val--;
}

void show()
{
    printf("There's %d matcha and %d mango.\n", matcha, mango);
}

void guest(void *arg)
{
    int num = (int)(arg);
    if (num >= FEMALE)
    {
        num -= FEMALE;
        while (!matcha)
        {
            plate.P();
            A.lock();
            matcha++;
            printf("Waiter-A 2130 add a matcha to plate for Male %d.\n", num);
            delay();
            A.unlock();
        }
        matcha--;
        printf("Male %d is full. %d matcha & %d mango remained.\n", num, matcha, mango);
        plate.V();
    }
    else
    {
        while (!mango)
        {
            plate.P();
            B.lock();
            mango++;
            printf("Waiter-B 7289 add a mango to plate for Female %d.\n", num);
            delay();
            B.unlock();
        }
        mango--;
        printf("Female %d is full. %d matcha & %d mango remained.\n", num, matcha, mango);
        plate.V();
    }
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

    plate.initialize(5);
    matcha = 5, mango = 0;
    for (int i = 0; i < matcha + mango; i++)
        plate.P();
    printf("There's %d matcha & %d mango at first.\n", matcha, mango);
    for (int i = 0; i < MALE + FEMALE; i++)
        programManager.executeThread(guest, (void *)(i), "", 1);

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
