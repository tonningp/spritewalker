#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsEllipseItem>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QTimer>
#include "typedefs.h"
#include "ctilescene.h"
#include "sprite.h"
#include "cconsolewidget.h"

namespace Ui {
class MainWindow;
}

enum KeyState {KEY_UP,KEY_DOWN};
class MainWindow : public QMainWindow
{
    Q_OBJECT

    CTileScene *m_scene;
    QGraphicsRectItem *rectangle;
    QGraphicsEllipseItem *ellipse;
    QGraphicsTextItem *text;
    Sprite *m_current_sprite;
    QLabel *m_status_label;
    QTimer* m_timer;
    void moveSprite(Sprite_Direction);
    QMediaPlayer *m_player;
    KeyState m_key_state;
    CConsoleWidget *m_console;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    CTileScene* scene();
    void scene(CTileScene*);
    QTimer *timer();
    void timer(QTimer*);
    QMediaPlayer *mediaplayer() const;
    void mediaplayer(QMediaPlayer *mediaplayer);
    QLabel *status_label() const;
    void status_label(QLabel *status_label);
    CConsoleWidget *console() const;

public slots:
    void drawScene();
    void addMaleVillager();
    void addFemaleVillager();
    void addHero();
    void addMonster();
    void addScheusal();
    void addMountain();
    void addConsole();
    void addStream();
    void spriteDown();
    void spriteLeft();
    void spriteRight();
    void spriteSpeedFast();
    void spriteSpeedSlow();
    void spriteUp();
    void spriteStop();
    void spriteStart();
    void stopScene();
    void startScene();
    void updateGameStatus();
    void spawnAll();
    void clearActors();
    void musicOn();
    void musicOff();
    void changeVolume(int);
    void actorClicked(QGraphicsSceneMouseEvent*,Sprite*);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

protected:
    SceneActor* addActor(const QString &name);
    Sprite *current_sprite() const;
    void current_sprite(Sprite *current_sprite);

protected slots:
    void updateSpritePosition(Sprite *sprite);

private:
    Ui::MainWindow *ui;
    void setupTimer();
    void createScene();
    void setupStatusLabel();
    void createMenus();
    QAction* createAction(const QString& menu,const QKeySequence&,const QString& tip);
    void newFile();
    void openFile();
    void saveFile();
};

#endif // MAINWINDOW_H
