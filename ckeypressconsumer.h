#ifndef CKEYPRESSCONSUMER_H
#define CKEYPRESSCONSUMER_H

#include <QEvent>
#include <QKeyEvent>
#include <QObject>



class CKeyPressConsumer : public QObject
{
    Q_OBJECT
    QObject *m_target;
public:
    explicit CKeyPressConsumer(QObject *target,QObject *parent = 0);

    QObject *target() const;
    void setTarget(QObject *target);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void arrowKey(QKeyEvent*);

public slots:
};



#endif // CKEYPRESSCONSUMER_H
