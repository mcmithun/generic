#ifndef NAVI_H
#define NAVI_H
#include "subscription.h"
#include "Server/datalistener.h"

class Navi
{
public:
    Navi(Subscription<Navi> *sub);

    void Start();
    int m_data;

private:
    Subscription<Navi> *m_sub;
};

#endif // NAVI_H
