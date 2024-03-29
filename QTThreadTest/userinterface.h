#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>
#include "stdthreadqt.h"
#include "mixin.h"
#include "navi.h"
#include "subscription.h"

namespace Ui {
class UserInterface;
}

class UserInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserInterface(QWidget *parent = nullptr);
    ~UserInterface();

private:
    Ui::UserInterface *ui;

    stdthreadqt *m_thread;
    std::thread *m_stdthread;
    Navi *m_navi;
    Mixin *m_mixin;
    Subscription<Navi> *navisubscriber;

    //void InstallNewThread(Navi *);
    template<typename T> void InstallNewThread(T&);

public slots:
    void updateLabel(QString );
    void startNaviThread();
    void startMixinThread();
};

#endif // USERINTERFACE_H
