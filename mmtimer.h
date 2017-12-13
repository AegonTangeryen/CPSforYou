#ifndef MMTIMER_H
#define MMTIMER_H

#include <qt_windows.h>
#include <QObject>

class MMTimer : public QObject
{
    Q_OBJECT
public:
    explicit MMTimer(int interval, QObject *parent = 0);
    ~MMTimer();

signals:
    void timeout();

public slots:
    void start();
    void stop();

friend void WINAPI CALLBACK mmtimer_proc(uint, uint, DWORD_PTR, DWORD_PTR, DWORD_PTR);

private:
    int m_interval;
    int m_id;
};

#endif // MMTIMER_H
