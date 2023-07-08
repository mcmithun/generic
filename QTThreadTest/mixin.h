#ifndef MIXIN_H
#define MIXIN_H
#include "subscription.h"

class Mixin : public Subscription<Mixin>
{
public:
    Mixin();

    void Start();
    int m_data;
private:
    // sub is not needed
};

#endif // MIXIN_H
