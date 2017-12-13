#include "mmtimer.h"
#include <MMSystem.h>
#ifdef __MINGW32__ //w32api bug
#define TIME_KILL_SYNCHRONOUS 0x0100
#endif

void WINAPI CALLBACK mmtimer_proc(uint timerId, uint, DWORD_PTR user, DWORD_PTR, DWORD_PTR)
{
    MMTimer *t = reinterpret_cast<MMTimer*>(user);
    emit t->timeout();
}

MMTimer::MMTimer(int interval, QObject *parent) :
    QObject(parent),m_interval(interval),m_id(0)
{}

MMTimer::~MMTimer()
{
    stop();
}

void MMTimer::start()
{
    m_id = timeSetEvent(m_interval, 1, mmtimer_proc, (DWORD_PTR)this,
                 TIME_CALLBACK_FUNCTION | TIME_PERIODIC | TIME_KILL_SYNCHRONOUS);

}

void MMTimer::stop()
{
    if (m_id){
        timeKillEvent(m_id);
        m_id = 0;
    }
}
