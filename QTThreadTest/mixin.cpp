#include "mixin.h"
#include <QDebug>
#include <unistd.h>

Mixin::Mixin()
{

}

void Mixin::Start(){
    for (int i = 0; i < 10000; i++)
    {
        qDebug()<<"this is mixin" << i <<"\n";
        m_data = i;
        notify(this);
        usleep(16000);
    }
}
