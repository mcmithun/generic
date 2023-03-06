#ifndef STDTHREADQT_H
#define STDTHREADQT_H

#include <QObject>
#include <QThread>

class stdthreadqt : public QThread
{
    Q_OBJECT
public:
    explicit stdthreadqt(QObject *parent = nullptr);

    void run() override;

signals:
    void updateResult(const QString &s);
};

#endif // STDTHREADQT_H
