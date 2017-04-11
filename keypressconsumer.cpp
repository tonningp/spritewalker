#include "keypressconsumer.h"

#include <QKeyEvent>

#include<QDebug>

KeyPressConsumer::KeyPressConsumer(QObject *target,QObject *parent) : QObject(parent),m_target(target) {
    QObject::connect(this,SIGNAL(arrowKey(QKeyEvent*)),target,SLOT(keyPressEvent(QKeyEvent*)));
}

bool KeyPressConsumer::eventFilter(QObject *obj, QEvent *event) {
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

QObject *KeyPressConsumer::target() const {
    return m_target;
}

void KeyPressConsumer::setTarget(QObject *target) {
    m_target = target;
}
