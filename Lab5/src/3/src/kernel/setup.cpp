#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"

// 屏幕IO处理器
STDIO stdio;
// 中断管理器
InterruptManager interruptManager;

extern "C" void setup_kernel()
{
    // 中断处理部件
    interruptManager.initialize();
    // 屏幕IO处理部件
    stdio.initialize();
    interruptManager.enableTimeInterrupt();
    interruptManager.setTimeInterrupt((void *)asm_time_interrupt_handler);
    // asm_enable_interrupt();

    // printf("print percentage: %%\n"
    //        "print char \"N\": %c\n"
    //        "print string \"Hello World!\": %s\n"
    //        "print decimal: \"-1234\": %d\n"
    //        "print hexadecimal \"0x7abcdef0\": %x\n",
    //        'N', "Hello World!", -1234, 0x7abcdef0);

    printf("print percentage %%\n");
    printf("print char \"N\": %c\n", 'N');
    printf("print string \"liusenyuan\": %s\n", "liusenyuan");
    printf("print OCT \"21307289\": %o\n", 21307289);
    printf("print DEC \"21307289\": %d\n", 21307289);
    printf("print HEX \"21307289\": %x\n", 21307289);
    int num = 21307289;
    printf("print pointer: %p\n", &num);
    // uint a = 1 / 0;
    asm_halt();
}
