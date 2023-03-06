#include "navi.h"
#include <QDebug>
#include <unistd.h>

Navi::Navi(Subscription<Navi> *sub) : m_sub(sub)
{

}

void Navi::Start()
{
    for (int i = 0; i < 100; i++)
    {
        qDebug()<<"this is navi" << i <<"\n";
        m_data = i;
        m_sub->notify(this);
        sleep(1);
    }
}
