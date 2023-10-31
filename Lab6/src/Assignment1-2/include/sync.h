#ifndef SYNC_H
#define SYNC_H

#include "os_type.h"

class SpinLock
{
private:
    uint32 bolt;

public:
    SpinLock();
    void initialize();
    void lock();
    void unlock();
};

class MutexLock
{
private:
    uint32 state;

public:
    MutexLock();
    void initialize();
    void lock();
    void unlock();
};

#endif
