#include "cconsolewidget.h"

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>


CConsoleWidget::CConsoleWidget(QWidget *parent) : QWidget(parent) {
    QPushButton *send = new QPushButton("Send to Actor",this);
    QPushButton *button = new QPushButton("Close",this);
    connect(button,&QPushButton::clicked,this,&CConsoleWidget::sendText);
    connect(button,&QPushButton::clicked,this,&CConsoleWidget::hide);
    QVBoxLayout *layout = new QVBoxLayout;

    m_textedit = new QTextEdit(this);
    m_textedit->setPlainText(tr("Console text"));
    layout->addWidget(new QLabel("Enter some text"));
    layout->addWidget(m_textedit);
    layout->addWidget(send);
    layout->addWidget(button);
    setLayout(layout);
}

QTextEdit *CConsoleWidget::textedit() const
{
    return m_textedit;
}

void CConsoleWidget::sendText() {
    emit signalText(m_textedit->toPlainText().toLatin1().data());
}
