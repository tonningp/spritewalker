#include "cconsolewidget.h"

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>


CConsoleWidget::CConsoleWidget(QWidget *parent) : QWidget(parent) {
    QPushButton *button = new QPushButton("Close",this);
    connect(button,&QPushButton::clicked,this,&CConsoleWidget::hide);
    //QGroupBox *gridGroupBox = new QGroupBox(tr("Grid layout"),this);
    //QGridLayout *layout = new QVBoxLayout;
    QVBoxLayout *layout = new QVBoxLayout;

    m_textedit = new QTextEdit(this);
    m_textedit->setPlainText(tr("Console text"));
//    layout->addWidget(text, 0, 2, 4, 1);
//    layout->addWidget(button,0,2,4,4,Qt::AlignCenter);
//    layout->setColumnStretch(1, 10);
//    layout->setColumnStretch(2, 20);
//    layout->addWidget(text, 0, 2, 4, 1);
//    layout->addWidget(button,0,2,4,4,Qt::AlignCenter);
    layout->addWidget(new QLabel("Enter some text"));
    layout->addWidget(m_textedit);
    layout->addWidget(button);
    setLayout(layout);
}

QTextEdit *CConsoleWidget::textedit() const
{
    return m_textedit;
}

