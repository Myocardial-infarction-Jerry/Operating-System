#include "sync.h"
#include "asm_utils.h"
#include "stdio.h"
#include "os_modules.h"

SpinLock::SpinLock()
{
    initialize();
}

void SpinLock::initialize()
{
    bolt = 0;
}

void SpinLock::lock()
{
    uint32 key = 1;

    do
    {
        asm_atomic_exchange(&key, &bolt);
        // printf("pid: %d\n", programManager.running->pid);
    } while (key);
}

void SpinLock::unlock()
{
    bolt = 0;
}

MutexLock::MutexLock()
{
    initialize();
}

void MutexLock::initialize()
{
    state = 0;
}

void MutexLock::lock()
{
    while (state)
    {
    }
    state = 1;
}

void MutexLock::unlock()
{
    state = 0;
}