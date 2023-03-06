#include "stdthreadqt.h"
#include <QDebug>

stdthreadqt::stdthreadqt(QObject *parent) : QThread(parent)
{

}

void stdthreadqt::run()
{
    for(int i = 0; i < 100 ; i++)
    {
        emit updateResult(QString::number(i));
        qDebug()<< i <<"\n";
        sleep(1);
    }
}
