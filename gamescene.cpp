#include <QTimer>
#include "actor.h"
#include "gameengine.h"
#include "consolewidget.h"
#include "gamescene.h"
#include "scenemanager.h"
#include "cutilities.h"



GameScene::GameScene(SceneManager* sm,QObject *parent,const QRectF &rect) :
    QGraphicsScene(parent),
    m_scene_manager(sm),
    m_current_sprite(NULL),
    m_timer(new QTimer),
    m_console(new ConsoleWidget)
{
    this->addWidget(m_console);
    m_console->hide();
    this->setSceneRect(rect);
    drawGrid();
    connect(m_timer, &QTimer::timeout, this, &GameScene::advance);
    connect(m_timer, &QTimer::timeout, this, &GameScene::actorCollision);
    QObject::connect(m_console, SIGNAL(signalText(const char*)), parent, SLOT(consoleText(const char*)));
    timer()->start(30);
}

QString GameScene::name() const
{
    return m_name;
}

void GameScene::setName(const QString &name)
{
    m_name = name;
}

SceneManager *GameScene::sceneManager() const
{
    return m_scene_manager;
}

void GameScene::sceneManager(SceneManager *scene_manager)
{
    m_scene_manager = scene_manager;
}

QTimer *GameScene::timer() {
    return m_timer;
}

mfg::Engine *GameScene::gameEngine()
{
    return sceneManager()->game_engine();
}

ConsoleWidget *GameScene::console() {
    return m_console;
}

void GameScene::drawGrid() {
    auto o1 = this->addLine(QLineF(QPointF(-25,0),QPointF(25,0)),QPen(Qt::blue));
    o1->setData(0,"XAxis");
    auto o2 = this->addLine(QLineF(QPointF(0,-25),QPointF(0,25)),QPen(Qt::blue));
    o2->setData(0,"YAxis");
    auto r = this->addRect(this->sceneRect(),QPen(Qt::black));
    r->setData(0,"Boundary");
}

void GameScene::addItem(QGraphicsItem *item,const QString &name) {
    item->setData(0,name);  // key 0 is the type
    QGraphicsScene::addItem(item);
}

SceneActor *GameScene::addActor(const QString &name,const QString &start_action,bool moving) {
    ActorPointer actor = new SceneActor(name,gameEngine(),start_action,moving);
    addItem(actor,"Actor");
    actor->setPos(QPointF(CUtilities::randInt(this->sceneRect().left(),this->sceneRect().right()),
                          CUtilities::randInt(this->sceneRect().top(),this->sceneRect().bottom())));
    actor->direction((Sprite_Direction)CUtilities::randInt(0,3));
    return actor;

}

Sprite *GameScene::addSprite(const QString &name,const QString &start_action,bool moving) {
    SpritePointer sprite = new Sprite(name,gameEngine(),moving);
    addItem(sprite,"Sprite");
    sprite->setPos(QPointF(CUtilities::randInt(this->sceneRect().left(),this->sceneRect().right()),
                          CUtilities::randInt(this->sceneRect().top(),this->sceneRect().bottom())));
    sprite->direction((Sprite_Direction)CUtilities::randInt(0,3));
    return sprite;

}

void GameScene::removeActor(SceneActor* item) {
    item = ActorPointer(item);
    if(item && item->scene() == this) {
        removeItem(item);
        m_deadlist << item; // clean this
    }
}

GraphicsItemList GameScene::getDeadlist() const
{
    return m_deadlist;
}

void GameScene::setDeadlist(const GraphicsItemList &deadlist)
{
    m_deadlist = deadlist;
}

QTime GameScene::current_time() {
    return m_current_time;
}

QGraphicsItem *GameScene::setBackgroundImageByName(const QString &name) {
    return addPixmap(*(gameEngine()->pixMap(name)));
}


ActorCountMap GameScene::getActorCounts() {
    ActorCountMap actor_count_map;
    for(auto name :  players()) {
       actor_count_map[name]=0;
    }
    for(auto item : this->items()) {
        if(isSceneActor(item)) {
            ActorPointer actor = (SceneActor*)item;
            if(actor) actor_count_map[actor->name()]++;
        }
    }
    return actor_count_map;
}

ActorList GameScene::getAllActors() {
    ActorList list;
    for(auto item:this->items()) {
       if(isSceneActor(item)) {
           list << ActorPointer((SceneActor*)(item));
       }
    }
    return list;
}

QVector<QString> GameScene::players() {
    return mfg::Engine::actors();
}

int GameScene::deadCount() {
    return m_deadlist.count();
}

void GameScene::clearDead() {
    m_deadlist.clear();
}

bool GameScene::isSceneActor(QGraphicsItem *item) {
  return item->data(0) == "Actor";
}

void GameScene::connectTimer(QTimer *timer) {
    connect(timer, &QTimer::timeout, this, &GameScene::advance);
    connect(timer, &QTimer::timeout, this, &GameScene::actorCollision);
}

void GameScene::clearActors() {
    for(auto item : this->getAllActors()) {
        this->removeActor(item);
    }
    clearDead();
}

Sprite *GameScene::current_sprite() {
    return m_current_sprite;
}

Sprite *GameScene::current_sprite(Sprite *sprite)
{
    return m_current_sprite = sprite;
}




void GameScene::actorCollision() {
    for(ActorPointer actor: this->getAllActors()) {
       if(actor && actor->isDead()) this->removeActor(actor);
    }

}

#include<QDebug>
void GameScene::advance() {
    m_current_time = QTime();
    m_current_time.start();
    QGraphicsScene::advance();
/*
    for(auto item : items()) {
            if(item->data(0) == "Actor") {
                ActorPointer actor = ActorPointer((Actor*)item);
                if(actor && actor->animating() && actor->is_moving()) {
                    switch(actor->direction()) {
                    case SPRITE_DOWN:
                        actor->setPos(actor->pos()+QPointF(0,actor->advance_distance()));
                        break;
                    case SPRITE_UP:
                        actor->setPos(actor->pos()+QPointF(0,-1*actor->advance_distance()));
                        break;
                    case SPRITE_LEFT:
                        actor->setPos(actor->pos()+QPointF(-1 * actor->advance_distance(),0));
                        break;
                    case SPRITE_RIGHT:
                        actor->setPos(actor->pos()+QPointF(actor->advance_distance(),0));
                        break;
                    }
                }

            }
    }
    */
}

void GameScene::spriteSelected(QGraphicsSceneMouseEvent* event, Sprite *sprite) {
    for(auto item : items()) {
       item->setSelected(false);
    }
    sprite->setSelected(true);
    m_current_sprite = sprite;
}
/**

 * @param mouseEvent
 *
 * Need to setMouseTracking = true in the view
 */
void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
