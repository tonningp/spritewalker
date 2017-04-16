#include "consolewidget.h"

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>


ConsoleWidget::ConsoleWidget(QWidget *parent) : QFrame(parent) {
    QPushButton *send = new QPushButton("Send to Actor",this);
    QPushButton *button = new QPushButton("Close",this);
    connect(button,&QPushButton::clicked,this,&ConsoleWidget::sendText);
    connect(button,&QPushButton::clicked,this,&ConsoleWidget::hide);
    QVBoxLayout *layout = new QVBoxLayout;

    m_textedit = new QTextEdit(this);
    //m_textedit->setPlainText(tr("Console text"));
    layout->addWidget(new QLabel("Enter some text"));
    layout->addWidget(m_textedit);
    layout->addWidget(send);
    layout->addWidget(button);
    setLayout(layout);
}

QTextEdit *ConsoleWidget::textedit() const
{
    return m_textedit;
}

void ConsoleWidget::sendText() {
    emit signalText(m_textedit->toPlainText().toLatin1().data());
}
