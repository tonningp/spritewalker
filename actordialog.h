#ifndef ACTORDIALOG_H
#define ACTORDIALOG_H
#include "actor.h"

#include <QDialog>

namespace Ui {
class ActorDialog;
}
/**
 * @brief The ActorDialog class - defines a dialog box for actor properties
 */
class ActorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActorDialog(QWidget* parent,SceneActor* actor);
    ~ActorDialog();

    ActorPointer actor() const;
    void actor(SceneActor *actor);

    bool ready() const;
    void ready(bool ready);

private slots:
    void actionChanged();
    void directionChanged();

private:
    Ui::ActorDialog *ui;
    ActorPointer m_actor;
    bool m_ready;

};

#endif // CACTORDIALOG_H
