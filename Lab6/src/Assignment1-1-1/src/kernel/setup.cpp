#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "program.h"
#include "thread.h"
#include "sync.h"

// 屏幕IO处理器
STDIO stdio;
// 中断管理器
InterruptManager interruptManager;
// 程序管理器
ProgramManager programManager;

int shared_variable;
SpinLock aLock;

int shadow;

void shadow_clone(void *arg)
{
    aLock.lock();
    int delay = 0;

    printf("Robot 21307289: start to make shadow clone, there are %d Liusenyuan now\n", shadow);
    // make 10 shadow
    shadow += 10;

    printf("Robot 21307289: Sleeping\n");
    // hanging clothes out
    delay = 0xffffff;
    while (delay)
        --delay;
    // done

    printf("Robot 21307289: There are %d Liusenyuan now\n", shadow);
    aLock.unlock();
}

void battle(void *arg)
{
    aLock.lock();
    printf("10 Liusenyuan disappear in the battle\n");
    shadow -= 10;
    aLock.unlock();
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

    shadow = 0;
    aLock.initialize();

    programManager.executeThread(shadow_clone, nullptr, "second thread", 1);
    programManager.executeThread(battle, nullptr, "third thread", 1);

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
