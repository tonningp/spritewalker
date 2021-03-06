#include "consolewidget.h"
#include "ui_mainwindow.h"

#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QTextBlock>
#include <QTime>
#include <qmath.h>
#include "mainwindow.h"
#include "actordialog.h"
#include "actor.h"
#include "gameengine.h"
#include "scenemanager.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_current_sprite(NULL),
    m_scene(NULL)

{
    ui->setupUi(this);
    createMenus();
    setupStatusLabel();
    setupTimer();
    showMelba();

    QObject::connect(timer(), SIGNAL(timeout()), this, SLOT(updateGameStatus()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupTimer() {
    timer(new QTimer);
    timer()->start(100);
}

void MainWindow::showMelba() {
    showScene("melba01");
}

void MainWindow::showSpace() {
    showScene("space01");
}

void MainWindow::showScene(const QString &name) {
    if(scene() == NULL) {
        mfg::Engine *ge = new mfg::Engine;
        ge->sceneManager()->createScene(name,this);
        scene(ge->sceneManager()->getScene(name));
    }
    else if(scene()->sceneManager()->getScene(name) == NULL) {
        scene()->sceneManager()->createScene(name,this);
    }
    scene(scene()->sceneManager()->getScene(name));
    ui->graphicsView->setScene(scene()->sceneManager()->getScene(name));
}

void MainWindow::setupStatusLabel() {
    status_label(new QLabel(this));
    status_label()->setText("");
    ui->statusBar->addPermanentWidget(status_label());
}

/**
 * @brief MainWindow::createMenus
 */
void MainWindow::createMenus()
{
    QMenu* menu = menuBar()->addMenu(tr("&File"));
    QAction *action = createAction("&New",QKeySequence::New,"Create a new project");
    connect(action,&QAction::triggered,this,&MainWindow::newFile);
    menu->addAction(action);

    action = createAction("&Open",QKeySequence::Open,"Open project");
    connect(action,&QAction::triggered,this,&MainWindow::openFile);
    menu->addAction(action);

    action = createAction("&Save",QKeySequence::Open,"Save a project");
    connect(action,&QAction::triggered,this,&MainWindow::saveFile);
    menu->addAction(action);

    action = createAction("E&xit",QKeySequence::Quit,"Exit the application");
    connect(action, &QAction::triggered, this, &QWidget::close);
    menu->addSeparator();
    menu->addAction(action);

    menu = menuBar()->addMenu(tr("&Sprite"));
    action = createAction("&Hero",QKeySequence(tr("Shift+Ctrl+H","Sprite | Hero")),"Add A Hero");
    connect(action,&QAction::triggered,this,&MainWindow::addHero);
    menu->addAction(action);

    action = createAction("&Monster",QKeySequence(tr("Shift+Ctrl+M","Sprite | Monster")),"Add A Monster");
    connect(action,&QAction::triggered,this,&MainWindow::addMonster);
    menu->addAction(action);

    action = createAction("Male Villager",QKeySequence(tr("Shift+Ctrl+V","Sprite | Male Villager")),"Add A Male Villager");
    connect(action,&QAction::triggered,this,&MainWindow::addMaleVillager);
    menu->addAction(action);

    action = createAction("Female Villager",QKeySequence(tr("Alt+V","Sprite | Female Villager")),"Add A Female Villager");
    connect(action,&QAction::triggered,this,&MainWindow::addMaleVillager);
    menu->addAction(action);

    action = createAction("S&cheusal",QKeySequence(tr("Shift+Ctrl+C","Sprite | Scheusal")),"Add A Scheusal");
    connect(action,&QAction::triggered,this,&MainWindow::addScheusal);
    menu->addAction(action);

    action = createAction("Mountain",QKeySequence(tr("Alt+Ctrl+M","Sprite | Mountain")),"Add A Mountain");
    connect(action,&QAction::triggered,this,&MainWindow::addMountain);
    menu->addAction(action);

    menu = menuBar()->addMenu(tr("&Widget"));
    action = createAction("&Console",QKeySequence(tr("Alt+Ctrl+C","Widget | Console")),"Show Console Widget");
    connect(action,&QAction::triggered,this,&MainWindow::showConsole);
    menu->addAction(action);

    menu = menuBar()->addMenu(tr("Sc&enes"));
    action = createAction("Legend of Melba",QKeySequence(tr("Alt+Ctrl+L","Scene | Melba")),"Show the melba scene");
    connect(action,&QAction::triggered,this,&MainWindow::showMelba);
    menu->addAction(action);
    action = createAction("Space Scene",QKeySequence(tr("Alt+Ctrl+S","Scene | Space")),"Show the space scene");
    connect(action,&QAction::triggered,this,&MainWindow::showSpace);
    menu->addAction(action);

}

/**
 * @brief MainWindow::createAction create a menu action
 * @param menu
 * @param shortcut
 * @param tip
 * @return *QAction
 */
QAction *MainWindow::createAction(const QString &menu, const QKeySequence &shortcut,const QString &tip) {
    QAction *newAct = new QAction(tr(menu.toLatin1().data()), this);
    newAct->setShortcut(shortcut);
    newAct->setStatusTip(tr(tip.toLatin1().data()));
    return newAct;
}

#include<QDebug>
/**
 * @brief MainWindow::newFile -- TODO
 */
void MainWindow::newFile() {
    qDebug() << "TODO: newFile";
}

void MainWindow::openFile() {
    qDebug() << "TODO: openFile";
}

void MainWindow::saveFile()
{
    qDebug() << "TODO: saveFile";

}

void MainWindow::spawnAll() {
    for(int i=0;i<5;i++) {
        addHero();
        addMonster();
        addMaleVillager();
        addScheusal();
    }
}

void MainWindow::clearActors() {
    scene()->clearActors();
}

void MainWindow::musicOn() {
    scene()->gameEngine()->mediaplayer()->play();
}

void MainWindow::musicOff() {
    scene()->gameEngine()->mediaplayer()->pause();
}

void MainWindow::changeVolume(int v) {
    scene()->gameEngine()->mediaplayer()->setVolume(v);
}

void MainWindow::addHero() {
    currentSprite(addActor("hero"));
}

void MainWindow::addMonster() {
    currentSprite(addActor("monster"));
}

void MainWindow::addMaleVillager() {
    currentSprite(addActor("male_villager"));
}

void MainWindow::addFemaleVillager() {
    currentSprite(addActor("female_villager"));
}

void MainWindow::addScheusal() {
    currentSprite(addActor("scheusal"));
}

void MainWindow::addMountain() {
    SpritePointer sprite = scene()->addSprite("mountain","stationary",false);
    sprite->setZValue(-100);
    connect(sprite,&Sprite::spriteClick,this,&MainWindow::actorClicked);
    connect(sprite,&Sprite::spriteClick,scene(),&GameScene::spriteSelected);
}

void MainWindow::showConsole() {
    scene()->console()->show();
    scene()->console()->textedit()->setFocus();
}

void MainWindow::addStream() {
    QLineEdit *edit = new QLineEdit();
    QGraphicsProxyWidget *widgetproxy = scene()->addWidget(edit);

    widgetproxy->setFlag(QGraphicsItem::ItemIsSelectable); // Also tried
    widgetproxy->setFlag(QGraphicsItem::ItemIsMovable); // this and
    widgetproxy->setFlag(QGraphicsItem::ItemIsFocusable); // this

}

void MainWindow::consoleText(const char *s) {
   ActorPointer actor = ActorPointer((Actor*)currentSprite());
   actor << QString(s);
}

SceneActor *MainWindow::addActor(const QString& name) {
    ActorPointer actor = scene()->addActor(name,"walking",false);
    connect(actor,&Sprite::spriteClick,this,&MainWindow::actorClicked);
    connect(actor,&Sprite::spriteClick,scene(),&GameScene::spriteSelected);
    //connect(actor,&Sprite::spriteMove,this,&MainWindow::updateSpritePosition);
    return actor;
}

void MainWindow::updateSpritePosition(Sprite* sprite) {
    status_label()->setText(sprite->name() + ": " +
                            QString("%1,%2").arg(QString::number((double)sprite->pos().x()),
                                    QString::number((double)sprite->pos().y())));
}

void MainWindow::actorClicked(QGraphicsSceneMouseEvent* event,Sprite* sprite) {
    currentSprite(sprite);

    status_label()->setText(currentSprite()->name() +  " - "
                            + QString::number(currentSprite()->pos().x())
                            +","
                            +QString::number(currentSprite()->pos().y()));

    if(event->button() == Qt::RightButton && scene()->isSceneActor(currentSprite())) {
        ActorDialog *dlg = new ActorDialog(0,(SceneActor*)currentSprite());
        dlg->show();
    }
}

void MainWindow::spriteDown() {
    moveSprite(Sprite_Direction::SPRITE_DOWN);
}

void MainWindow::spriteLeft() {
    moveSprite(Sprite_Direction::SPRITE_LEFT);
}

void MainWindow::spriteRight() {
    moveSprite(Sprite_Direction::SPRITE_RIGHT);
}


void MainWindow::spriteUp() {
    moveSprite(Sprite_Direction::SPRITE_UP);
}

void MainWindow::spriteSpeedFast() {
    int step = timer()->interval()>11?timer()->interval()-10:1;
    timer()->setInterval(step);
}

void MainWindow::spriteSpeedSlow() {
    int step = timer()->interval()<1500?timer()->interval()+10:1500;
    timer()->setInterval(step);
}

void MainWindow::spriteStop() {
   if(QPointer<Sprite>(currentSprite())) currentSprite()->animating(false);
}

void MainWindow::spriteStart() {
   if(QPointer<Sprite>(currentSprite())) currentSprite()->animating(true);
}

void MainWindow::stopScene() {
    for(auto actor : scene()->getAllActors()) {
        actor->animating(false);
    }
}

void MainWindow::startScene() {
    for(auto actor : scene()->getAllActors()) {
        actor->animating(true);
    }
}


GameScene* MainWindow::scene() {
    return m_scene;
}

void MainWindow::scene(GameScene *scene) {
   m_scene = scene;
}

QTimer *MainWindow::timer() {
    return m_timer;
}

void MainWindow::timer(QTimer *timer) {
   m_timer = timer;
}


void MainWindow::updateGameStatus() {
    if(scene()) {
        ActorCountMap actor_count_map = scene()->getActorCounts();
        ui->lbl_hero_count->setText(QString::number(actor_count_map["hero"]));
        ui->lbl_monster_count->setText(QString::number(actor_count_map["monster"]));
        ui->lbl_villager_count->setText(QString::number(actor_count_map["female_villager"]+actor_count_map["male_villager"]));
        ui->lbl_scheusal_count->setText(QString::number(actor_count_map["scheusal"]));
        ui->lbl_deadcount->setText(QString::number(scene()->deadCount()));
        ui->lbl_timer_interval->setText(QString::number(timer()->interval()));
        if(m_current_sprite) {
            updateSpritePosition(m_current_sprite);
        }
        scene()->clearDead();
    }
}

Sprite *MainWindow::currentSprite() const
{
    return m_current_sprite;
}

void MainWindow::currentSprite(Sprite *current_sprite)
{
    m_current_sprite = current_sprite;
}

QLabel *MainWindow::status_label() const
{
    return m_status_label;
}

void MainWindow::status_label(QLabel *status_label)
{
    m_status_label = status_label;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    Actor* actor = QPointer<Actor>((Actor*)currentSprite());
    if(m_key_state != KeyState::KEY_DOWN) {
            m_key_state = KeyState::KEY_DOWN;
                switch(e->key()) {
                    case Qt::Key_A:  // a
                    case Qt::Key_H:  //h
                    case Qt::Key_Left:  // arrow left
                        spriteLeft();
                        spriteStart();
                        break;
                    case Qt::Key_J:  //j
                    case Qt::Key_S:  //s
                    case Qt::Key_Down:  // arrow up
                        spriteDown();
                        spriteStart();
                        break;
                    case Qt::Key_K:  //k
                    case Qt::Key_W:  //w
                    case Qt::Key_Up:  // arrow down
                        spriteUp();
                        spriteStart();
                        break;
                    case Qt::Key_D:  //d
                    case Qt::Key_L:  //l
                    case Qt::Key_Right:  // arrow right
                        spriteRight();
                        spriteStart();
                        break;
                    case Qt::Key_F:
                        if(actor) {
                            actor->action(actor->assetmanager()->actorPrimaryFightAction());
                            moveSprite(actor->direction());
                            actor << QString("I'm fighting");
                        }
                        break;
                    case Qt::Key_G:
                        if(actor) {
                            actor->action("walking");
                            moveSprite(actor->direction());
                        }
                        break;
                }
                //qDebug() << console()->textedit()->textCursor().block().length();

    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    m_key_state = KeyState::KEY_UP;
    switch(e->key()) {
        case Qt::Key_A:  // a
        case Qt::Key_H:  //h
        case Qt::Key_J:  //j
        case Qt::Key_S:  //s
        case Qt::Key_K:  //k
        case Qt::Key_W:  //w
        case Qt::Key_D:  //d
        case Qt::Key_L:  //l
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Left:
        case Qt::Key_Right:
            spriteStop();
            break;

    }

}

void MainWindow::scaleScene(int s) {

    qreal scale = qPow(qreal(2), (s - 250) / qreal(50));
    QMatrix matrix;
    matrix.scale(scale, scale);
    ui->graphicsView->setMatrix(matrix);
    qDebug() << ui->graphicsView->transform();
}

void MainWindow::moveSprite(Sprite_Direction direction) {
    if(QPointer<Sprite>(scene()->current_sprite(m_current_sprite))) {
            scene()->current_sprite(m_current_sprite)->direction(direction);
            scene()->current_sprite(m_current_sprite)->updateSprite();
            //ui->graphicsView->centerOn(m_current_sprite);
            QRect rcontent = ui->graphicsView->contentsRect();
            //ui->graphicsView->setSceneRect(0, 0, rcontent.width(), rcontent.height());
            ui->graphicsView->ensureVisible(m_current_sprite);
            ui->graphicsView->update();
    }
}

ConsoleWidget *MainWindow::console() const
{
    return m_console;
}

QMediaPlayer *MainWindow::mediaPlayer() const
{
    return m_player;
}

void MainWindow::mediaPlayer(QMediaPlayer *player)
{
    m_player = player;
}

