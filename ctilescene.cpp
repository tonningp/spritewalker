#include <QTimer>
#include "actor.h"
#include "cgameengine.h"
#include "cconsolewidget.h"
#include "ctilescene.h"
#include "scenemanager.h"
#include "cutilities.h"


CTileScene::CTileScene(SceneManager* sm,QObject *parent,const QRectF &rect) :
    QGraphicsScene(parent),
    m_scene_manager(sm),
    m_current_sprite(NULL),
    m_timer(new QTimer),
    m_console(new CConsoleWidget)
{
    this->addWidget(m_console);
    m_console->hide();
    this->setSceneRect(rect);
    drawGrid();
    connect(m_timer, &QTimer::timeout, this, &CTileScene::advance);
    connect(m_timer, &QTimer::timeout, this, &CTileScene::actorCollision);
    QObject::connect(m_console, SIGNAL(signalText(const char*)), parent, SLOT(consoleText(const char*)));
    timer()->start(30);
}

SceneManager *CTileScene::scene_manager() const
{
    return m_scene_manager;
}

void CTileScene::scene_manager(SceneManager *scene_manager)
{
    m_scene_manager = scene_manager;
}

QTimer *CTileScene::timer() {
    return m_timer;
}

mfg::Engine *CTileScene::gameengine()
{
    return scene_manager()->game_engine();
}

CConsoleWidget *CTileScene::console() {
    return m_console;
}

void CTileScene::drawGrid() {
    auto o1 = this->addLine(QLineF(QPointF(-25,0),QPointF(25,0)),QPen(Qt::blue));
    o1->setData(0,"XAxis");
    auto o2 = this->addLine(QLineF(QPointF(0,-25),QPointF(0,25)),QPen(Qt::blue));
    o2->setData(0,"YAxis");
    auto r = this->addRect(this->sceneRect(),QPen(Qt::black));
    r->setData(0,"Boundary");
}

void CTileScene::addItem(QGraphicsItem *item,const QString &name) {
    item->setData(0,name);  // key 0 is the type
    QGraphicsScene::addItem(item);
}

SceneActor *CTileScene::addActor(const QString &name,const QString &start_action,bool moving) {
    ActorPointer actor = new SceneActor(name,gameengine(),start_action,moving);
    addItem(actor,"Actor");
    actor->setPos(QPointF(CUtilities::randInt(this->sceneRect().left(),this->sceneRect().right()),
                          CUtilities::randInt(this->sceneRect().top(),this->sceneRect().bottom())));
    actor->direction((Sprite_Direction)CUtilities::randInt(0,3));
    return actor;

}

Sprite *CTileScene::addSprite(const QString &name,const QString &start_action,bool moving) {
    SpritePointer sprite = new Sprite(name,gameengine(),moving);
    addItem(sprite,"Sprite");
    sprite->setPos(QPointF(CUtilities::randInt(this->sceneRect().left(),this->sceneRect().right()),
                          CUtilities::randInt(this->sceneRect().top(),this->sceneRect().bottom())));
    sprite->direction((Sprite_Direction)CUtilities::randInt(0,3));
    return sprite;

}

void CTileScene::removeActor(SceneActor* item) {
    item = ActorPointer(item);
    if(item && item->scene() == this) {
        removeItem(item);
        m_deadlist << item; // clean this
    }
}

GraphicsItemList CTileScene::getDeadlist() const
{
    return m_deadlist;
}

void CTileScene::setDeadlist(const GraphicsItemList &deadlist)
{
    m_deadlist = deadlist;
}

QTime CTileScene::current_time() {
    return m_current_time;
}

QGraphicsItem *CTileScene::setBackgroundImageByName(const QString &name) {
    return addPixmap(*(gameengine()->pixMap(name)));
}


ActorCountMap CTileScene::getActorCounts() {
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

ActorList CTileScene::getAllActors() {
    ActorList list;
    for(auto item:this->items()) {
       if(isSceneActor(item)) {
           list << ActorPointer((SceneActor*)(item));
       }
    }
    return list;
}

QVector<QString> CTileScene::players() {
    return mfg::Engine::actors();
}

int CTileScene::deadCount() {
    return m_deadlist.count();
}

void CTileScene::clearDead() {
    m_deadlist.clear();
}

bool CTileScene::isSceneActor(QGraphicsItem *item) {
  return item->data(0) == "Actor";
}

void CTileScene::connectTimer(QTimer *timer) {
    connect(timer, &QTimer::timeout, this, &CTileScene::advance);
    connect(timer, &QTimer::timeout, this, &CTileScene::actorCollision);
}

void CTileScene::clearActors() {
    for(auto item : this->getAllActors()) {
        this->removeActor(item);
    }
    clearDead();
}

Sprite *CTileScene::current_sprite() {
    return m_current_sprite;
}

Sprite *CTileScene::current_sprite(Sprite *sprite)
{
    return m_current_sprite = sprite;
}




void CTileScene::actorCollision() {
    for(ActorPointer actor: this->getAllActors()) {
       if(actor && actor->isDead()) this->removeActor(actor);
    }

}

#include<QDebug>
void CTileScene::advance() {
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

void CTileScene::spriteSelected(QGraphicsSceneMouseEvent* event, Sprite *sprite) {
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
void CTileScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
