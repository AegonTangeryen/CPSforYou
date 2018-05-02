#ifndef EXECDOSCMD_H
#define EXECDOSCMD_H

#include <QProcess>
#include "tools.h"
#include "hnc848system.h"
#include "ds18b20sensor.h"
#include "fbgsensos.h"
#include "envisensor.h"

class ExecDosCmd: public QThread
{
    Q_OBJECT

public:
    ExecDosCmd();

public:
    void run();
};

#endif // EXECDOSCMD_H
