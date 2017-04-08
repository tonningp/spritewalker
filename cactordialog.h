#ifndef CACTORDIALOG_H
#define CACTORDIALOG_H
#include "actor.h"

#include <QDialog>

namespace Ui {
class CActorDialog;
}

class CActorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CActorDialog(QWidget* parent,SceneActor* actor);
    ~CActorDialog();

    ActorPointer actor() const;
    void actor(SceneActor *actor);

    bool ready() const;
    void ready(bool ready);

private slots:
    void actionChanged();
    void directionChanged();

private:
    Ui::CActorDialog *ui;
    ActorPointer m_actor;
    bool m_ready;

};

#endif // CACTORDIALOG_H
