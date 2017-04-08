#include "cmenuaction.h"


CMenuAction::CMenuAction(const QString& menu,QObject* parent=0) : QAction(menu,parent)
{
}

CMenuAction *CMenuAction::shortcut(const QKeySequence &p_shortcut) {
    this->setShortcut(p_shortcut);
    return this;
}

CMenuAction *CMenuAction::statustip(const QString &p_tip) {
    this->setStatusTip(p_tip);
    return this;
}


CMenuAction *CMenuAction::connectMethod(QMainWindow *receiver, void (MainWindow::*method)())
{
     connect(this, &QAction::triggered,receiver,method);
     return this;

}
