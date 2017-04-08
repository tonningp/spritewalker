#include "cconsolewidget.h"
#include "ui_mainwindow.h"

#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QTextBlock>
#include <QTime>
#include "mainwindow.h"
#include "cactordialog.h"
#include "actor.h"
#include "cgameengine.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_current_sprite(NULL)

{
    ui->setupUi(this);
    createMenus();

    setupTimer();
    createScene();
    setupStatusLabel();
    //spawnAll();

    timer()->start(10);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupTimer() {
    timer(new QTimer);
    QObject::connect(timer(), SIGNAL(timeout()), this, SLOT(updateGameStatus()));
}

void MainWindow::createScene() {
    scene(new CTileScene(new mfg::Engine,this,QRectF(-475,-300,950,600)));
    scene()->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->graphicsView->setScene(scene());
    drawScene();
    m_console = new CConsoleWidget;
    scene()->addWidget(m_console)->setFlag(QGraphicsItem::ItemIsFocusable);
    m_console->hide();
    scene()->gameengine()->mediaplayer()->setPlaylist(scene()->gameengine()->mediaplaylist());
    scene()->gameengine()->mediaplayer()->setVolume(5);

    connect(timer(), &QTimer::timeout, scene(), &CTileScene::advance);
    connect(timer(), &QTimer::timeout, scene(), &CTileScene::actorCollision);
}

void MainWindow::setupStatusLabel() {
    status_label(new QLabel(this));
    status_label()->setText("");
    ui->statusBar->addPermanentWidget(status_label());
}

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
    connect(action,&QAction::triggered,this,&MainWindow::addConsole);
    menu->addAction(action);

}

QAction *MainWindow::createAction(const QString &menu, const QKeySequence &shortcut,const QString &tip) {
    QAction *newAct = new QAction(tr(menu.toLatin1().data()), this);
    newAct->setShortcut(shortcut);
    newAct->setStatusTip(tr(tip.toLatin1().data()));
    return newAct;
}

#include<QDebug>
void MainWindow::newFile() {
    qDebug() << "newFile";
}

void MainWindow::openFile() {
    qDebug() << "openFile";
}

void MainWindow::saveFile()
{
    qDebug() << "saveFile";

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
    scene()->gameengine()->mediaplayer()->play();
}

void MainWindow::musicOff() {
    scene()->gameengine()->mediaplayer()->pause();
}

void MainWindow::changeVolume(int v) {
    scene()->gameengine()->mediaplayer()->setVolume(v);
}

void MainWindow::drawScene() {
    auto bkg = scene()->setBackgroundImageByName("background01");
    bkg->setPos(-1*scene()->sceneRect().height()/2-175, -1*scene()->sceneRect().height()/2);
    //bkg->hide();
    bkg->setZValue(-1000);
}

void MainWindow::addHero() {
    current_sprite(addActor("hero"));
}

void MainWindow::addMonster() {
    current_sprite(addActor("monster"));
}

void MainWindow::addMaleVillager() {
    current_sprite(addActor("male_villager"));
}

void MainWindow::addFemaleVillager() {
    current_sprite(addActor("female_villager"));
}

void MainWindow::addScheusal() {
    current_sprite(addActor("scheusal"));
}

void MainWindow::addMountain() {
    SpritePointer sprite = scene()->addSprite("mountain","stationary",false);
    sprite->setZValue(-100);
    connect(sprite,&Sprite::spriteClick,this,&MainWindow::actorClicked);
    connect(sprite,&Sprite::spriteClick,scene(),&CTileScene::spriteSelected);
}

void MainWindow::addConsole() {
    m_console->show();
    m_console->textedit()->setFocus();
    //QPointer<CConsoleWidget>((CConsoleWidget*)m_console)->textedit()->setFocus();
}

void MainWindow::addStream() {
    /*
    SpritePointer sprite = scene()->addSprite("tree01","stationary",false);
    sprite->setZValue(-100);
    connect(sprite,&Sprite::spriteClick,this,&MainWindow::actorClicked);
    connect(sprite,&Sprite::spriteClick,scene(),&CTileScene::spriteSelected);
    */
    QLineEdit *edit = new QLineEdit();
    QGraphicsProxyWidget *widgetproxy = scene()->addWidget(edit);

    widgetproxy->setFlag(QGraphicsItem::ItemIsSelectable); // Also tried
    widgetproxy->setFlag(QGraphicsItem::ItemIsMovable); // this and
    widgetproxy->setFlag(QGraphicsItem::ItemIsFocusable); // this

}

SceneActor *MainWindow::addActor(const QString& name) {
    ActorPointer actor = scene()->addActor(name,"walking",false);
    connect(actor,&Sprite::spriteClick,this,&MainWindow::actorClicked);
    connect(actor,&Sprite::spriteClick,scene(),&CTileScene::spriteSelected);
    connect(actor,&Sprite::spriteMove,this,&MainWindow::updateSpritePosition);
    //QObject::connect(timer(),SIGNAL(timeout()),actor,SLOT(animate()));
    return actor;
}

void MainWindow::updateSpritePosition(Sprite* sprite) {
    status_label()->setText(sprite->name() + ": " +
                            QString("%1,%2").arg(QString::number((double)sprite->pos().x()),
                                    QString::number((double)sprite->pos().y())));
}

void MainWindow::actorClicked(QGraphicsSceneMouseEvent* event,Sprite* sprite) {
    current_sprite(sprite);

    status_label()->setText(current_sprite()->name() +  " - "
                            + QString::number(current_sprite()->pos().x())
                            +","
                            +QString::number(current_sprite()->pos().y()));

    if(event->button() == Qt::RightButton && scene()->isSceneActor(current_sprite())) {
        CActorDialog *dlg = new CActorDialog(0,(SceneActor*)current_sprite());
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
   if(QPointer<Sprite>(current_sprite())) current_sprite()->animating(false);
}

void MainWindow::spriteStart() {
   if(QPointer<Sprite>(current_sprite())) current_sprite()->animating(true);
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


CTileScene* MainWindow::scene() {
    return m_scene;
}

void MainWindow::scene(CTileScene *scene) {
   m_scene = scene;
}

QTimer *MainWindow::timer() {
    return m_timer;
}

void MainWindow::timer(QTimer *timer) {
   m_timer = timer;
}


void MainWindow::updateGameStatus() {
    ActorCountMap actor_count_map = scene()->getActorCounts();
    ui->lbl_hero_count->setText(QString::number(actor_count_map["hero"]));
    ui->lbl_monster_count->setText(QString::number(actor_count_map["monster"]));
    ui->lbl_villager_count->setText(QString::number(actor_count_map["female_villager"]+actor_count_map["male_villager"]));
    ui->lbl_scheusal_count->setText(QString::number(actor_count_map["scheusal"]));
    ui->lbl_deadcount->setText(QString::number(scene()->deadCount()));
    ui->lbl_timer_interval->setText(QString::number(timer()->interval()));
    scene()->clearDead();
}

Sprite *MainWindow::current_sprite() const
{
    return m_current_sprite;
}

void MainWindow::current_sprite(Sprite *current_sprite)
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
    Actor* actor = QPointer<Actor>((Actor*)current_sprite());
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

void MainWindow::moveSprite(Sprite_Direction direction) {
    if(QPointer<Sprite>(scene()->current_sprite(m_current_sprite))) {
            scene()->current_sprite(m_current_sprite)->direction(direction);
            scene()->current_sprite(m_current_sprite)->update_sprite();
    }
}

CConsoleWidget *MainWindow::console() const
{
    return m_console;
}

QMediaPlayer *MainWindow::mediaplayer() const
{
    return m_player;
}

void MainWindow::mediaplayer(QMediaPlayer *player)
{
    m_player = player;
}
