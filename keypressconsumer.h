#ifndef KEYPRESSCONSUMER_H
#define KEYPRESSCONSUMER_H

#include <QEvent>
#include <QKeyEvent>
#include <QObject>


/**
 * @brief The KeyPressConsumer class -- traps keyboard events so arrow keys can be filtered from application
 */
class KeyPressConsumer : public QObject
{
    Q_OBJECT
    QObject *m_target;
public:
    explicit KeyPressConsumer(QObject *target,QObject *parent = 0);

    QObject *target() const;
    void setTarget(QObject *target);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void arrowKey(QKeyEvent*);

public slots:
};



#endif // KEYPRESSCONSUMER_H
