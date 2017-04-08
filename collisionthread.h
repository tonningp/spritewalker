#ifndef COLLISIONTHREAD_H
#define COLLISIONTHREAD_H

#include <QThread>
#include <QMutex>
#include <QSet>
#include "actor.h"
#include "ctilescene.h"

typedef QSet<QString> StringSet;


class CollisionThread : public QThread
{
    Q_OBJECT

    public:
        CollisionThread(QObject *parent = 0);
        ~CollisionThread();

        void processScene(CTileScene *scene);

        int randInt(int low, int high);
signals:

    public slots:
        void stopProcess();

    protected:
        void run();

    private:
        bool m_abort;
        CTileScene *m_scene;
        QMutex mutex;
};

#endif // COLLISIONTHREAD_H
