#include "navi.h"
#include <QDebug>
#include <unistd.h>

Navi::Navi(Subscription<Navi> *sub) : m_sub(sub)
{

}

void Navi::Start()
{
    /*
    for (int i = 0; i < 10000; i++)
    {
        qDebug()<<"this is navi" << i <<"\n";
        m_data = i;
        m_sub->notify(this);
        usleep(16000);
    }
    */
    qDebug()<<"starting to listen on 1234\n";
    DataListener listener(1234);
    if (!listener.Init()) {
        return;
    }

    Header header;
    char *data = new char [1024];

    while (listener.Receive(header, data, sizeof(data))) {
        printf("Received data of type %d and size %d\n", header.type, header.size);
        qDebug()<< "Header:"<<header.type<< header.size<<", Received: "<<QString(data)<<"\n";
        sleep(1);
    }
    qDebug()<<"Exiting server.\n";
}
