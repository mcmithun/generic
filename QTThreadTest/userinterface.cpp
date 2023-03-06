#include "userinterface.h"
#include "ui_userinterface.h"
#include <QtDebug>

UserInterface::UserInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserInterface)
{
    ui->setupUi(this);
    ui->label->setText("-1");
    navisubscriber = new Subscription<Navi>();
    m_navi = new Navi(navisubscriber);

    navisubscriber->subscribe([this](const Navi *data){
        qDebug() <<  data->m_data <<" received. \n";
        this->updateLabel(QString::number(data->m_data));
    });
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startNaviThread()));
}

void UserInterface::updateLabel(QString val)
{
    ui->label->setText(val);
}

void UserInterface::startNaviThread()
{
    InstallNewThread(m_navi);
}

template<typename T>
void UserInterface::InstallNewThread(T& obj)
{
    m_stdthread = new std::thread([&obj](){
        obj->Start();
    });
}

UserInterface::~UserInterface()
{
    m_stdthread->join();
    delete m_stdthread;
    delete ui;
}
