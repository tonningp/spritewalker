#include "actordialog.h"
#include "ui_actordialog.h"

ActorDialog::ActorDialog(QWidget *parent,SceneActor* s_actor) :
    QDialog(parent),
    ui(new Ui::ActorDialog),
    m_ready(false)
{
    actor(s_actor),
    ui->setupUi(this);
    int index=0;
    for(auto action : m_actor->actions()) {
       ui->cb_action->addItem(action.toString());
       if(actor() && actor()->action() == action.toString()) {
          ui->cb_action->setCurrentIndex(index);
       }
       index++;
    }
    ui->cb_direction->setCurrentIndex(actor()->direction());
    ui->lbl_name->setText(actor()->name());
    ui->lbl_position->setText(QString::number(actor()->pos().x())+","+QString::number(actor()->pos().y()));
    ui->lbl_primary_fight->setText(actor()->primaryFightAction());
    ui->tbl_stats->setItem(0,0,new QTableWidgetItem(QString::number(actor()->stats().life)));
    ui->tbl_stats->setItem(1,0,new QTableWidgetItem(QString::number(actor()->stats().manna)));
    ui->tbl_stats->setItem(2,0,new QTableWidgetItem(QString::number(actor()->stats().stamina)));
    ui->tbl_stats->setItem(3,0,new QTableWidgetItem(QString::number(actor()->stats().wealth)));
    ui->tbl_stats->setItem(4,0,new QTableWidgetItem(actor()->assetmanager()->getSpriteSheetName()));
    ready(true);
}

ActorDialog::~ActorDialog()
{
    delete ui;
}

void ActorDialog::actionChanged() {
    if(ready() && actor())
       actor()->action(ui->cb_action->currentText());
}

void ActorDialog::directionChanged() {
    if(ready() && actor())
       actor()->direction((Sprite_Direction)ui->cb_direction->currentIndex());

}

bool ActorDialog::ready() const
{
    return m_ready;
}

void ActorDialog::ready(bool ready)
{
    m_ready = ready;
}

ActorPointer ActorDialog::actor() const
{
    return m_actor;
}

void ActorDialog::actor(SceneActor *actor)
{
    m_actor = actor;
}
