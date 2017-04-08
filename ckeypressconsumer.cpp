#include "ckeypressconsumer.h"

#include <QKeyEvent>

#include<QDebug>

CKeyPressConsumer::CKeyPressConsumer(QObject *target,QObject *parent) : QObject(parent),m_target(target) {
    QObject::connect(this,SIGNAL(arrowKey(QKeyEvent*)),target,SLOT(keyPressEvent(QKeyEvent*)));
}

bool CKeyPressConsumer::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(QSet<int>({Qt::Key_Left,Qt::Key_Right,Qt::Key_Up,Qt::Key_Down}).contains(keyEvent->key()) ||
                    event->type() == QEvent::KeyRelease ) {
                    emit arrowKey(keyEvent);
            }
            return QObject::eventFilter(obj, event);
        } else {
            // standard event processing
            return QObject::eventFilter(obj, event);
        }
}

QObject *CKeyPressConsumer::target() const {
    return m_target;
}

void CKeyPressConsumer::setTarget(QObject *target) {
    m_target = target;
}
