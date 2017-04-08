#ifndef CMENUACTION_H
#define CMENUACTION_H

#include <QAction>
#include <QMainWindow>

class MainWindow;
class CMenuAction : public QAction
{
public:
    CMenuAction(const QString& text,QObject *parent);
    CMenuAction* shortcut(const QKeySequence &shortcut);
    CMenuAction* statustip(const QString &tip);
    CMenuAction* connectMethod( QMainWindow *receiver,
                                           void (MainWindow::*method_ptr)());
};

#endif // CMENUACTION_H
