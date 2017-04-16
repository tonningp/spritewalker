#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsEllipseItem>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QTimer>
#include "typedefs.h"
#include "gamescene.h"
#include "sprite.h"
#include "consolewidget.h"

namespace Ui {
class MainWindow;
}
enum KeyState {KEY_UP,KEY_DOWN};

/**
 * @brief The MainWindow class - Defines Main window for application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    GameScene *m_scene;
    QGraphicsRectItem *rectangle;
    QGraphicsEllipseItem *ellipse;
    QGraphicsTextItem *text;
    Sprite *m_current_sprite;
    QLabel *m_status_label;
    QTimer* m_timer;
    void moveSprite(Sprite_Direction);
    QMediaPlayer *m_player;
    KeyState m_key_state;
    ConsoleWidget *m_console;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    GameScene* scene();
    void scene(GameScene*);
    QTimer *timer();
    void timer(QTimer*);
    QMediaPlayer *mediaPlayer() const;
    void mediaPlayer(QMediaPlayer *mediaPlayer);
    QLabel *status_label() const;
    void status_label(QLabel *status_label);
    ConsoleWidget *console() const;

    void showScene(const QString &name);
public slots:
    void addMaleVillager();
    void addFemaleVillager();
    void addHero();
    void addMonster();
    void addScheusal();
    void addMountain();
    void showConsole();
    void addStream();
    void consoleText(const char *);
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
    void scaleScene(int s);

protected:
    SceneActor* addActor(const QString &name);
    Sprite *currentSprite() const;
    void currentSprite(Sprite *currentSprite);

protected slots:
    void updateSpritePosition(Sprite *sprite);

private:
    Ui::MainWindow *ui;
    void setupTimer();

    void showMelba();
    void showSpace();

    void setupStatusLabel();
    void createMenus();
    QAction* createAction(const QString& menu,const QKeySequence&,const QString& tip);
    void newFile();
    void openFile();
    void saveFile();
};

#endif // MAINWINDOW_H
