#ifndef CCONSOLEWIDGET_H
#define CCONSOLEWIDGET_H

#include <QTextEdit>
#include <QWidget>

class CConsoleWidget : public QWidget
{
    Q_OBJECT
    QTextEdit *m_textedit;
public:
    explicit CConsoleWidget(QWidget *parent = 0);

    QTextEdit *textedit() const;

signals:
    void signalText(const char*);

public slots:
    void sendText();
};

#endif // CCONSOLEWIDGET_H
