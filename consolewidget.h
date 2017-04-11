#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QTextEdit>
#include <QWidget>

/**
 * @brief The ConsoleWidget class -- Provides a console for use in a Graphics scene
 */
class ConsoleWidget : public QWidget
{
    Q_OBJECT
    QTextEdit *m_textedit;
public:
    explicit ConsoleWidget(QWidget *parent = 0);

    QTextEdit *textedit() const;

signals:
    void signalText(const char*);

public slots:
    void sendText();
};

#endif // CONSOLEWIDGET_H
