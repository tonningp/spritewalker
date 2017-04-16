#include<QGraphicsScene>
#include "actor.h"
#include "ruleset.h"
#include "gamescene.h"



Actor::Actor(const QString &name,mfg::Engine *ge,const QString& start_action,bool moving,QObject *parent) :
    Sprite::Sprite(name,ge,moving,parent),
    m_name(name),
    m_asset_manager(ge->assetManager(name)) {

    game_engine(ge);
    stats(game_engine()->getDefaultStats(name));
    addRule(game_engine()->actorRule(name));
    buildActorPageCoordinates();
    action(start_action);
    m_animation_cells = this->asset_manager()->spritePageColumns("walking_down");
    connect(this,&Actor::actionChanged,this,&Actor::changeAnimationFrames);
    //startTimer(30);
}


void Actor::stats(const mfg::Stats &s) {
    m_stats = s;
}

mfg::Stats Actor::stats() {
    return m_stats;
}

QPainterPath Actor::shape() const
{
    //return Sprite::shape();
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}


int Actor::life() {
    return life(0);
}

int Actor::max_life() const {
    return game_engine()->max_life(name());
}

int Actor::life(int inc) {
    return m_stats.life += inc;
}

int Actor::isDead() {
    return stats().life <= 0;
}

void Actor::buildActorPageCoordinates() {
    Coordinates list;
    for(auto page : this->actions()) {
        for(auto direction: this->asset_manager()->actorDirectionSet()) {
            int row = this->asset_manager()->spritePageRow(page.toString()+"_"+direction.toString());
            int columns = this->asset_manager()->spritePageColumns(page.toString()+"_"+direction.toString());
            for(int col=this->asset_manager()->spritePageCol(page.toString()+"_"+direction.toString());col<columns;col++) {
              list << SpriteCoordinate(this->spriteSize()*col,this->spriteSize()*row);
            }
            this->addSpriteFrameCoordinates(page.toString(),list);
            list.clear();
        }
    }
}

void Actor::timerEvent(QTimerEvent *event) {
    animate();
    updateSprite();
}


QString Actor::name() const{
    return m_name;
}

QString Actor::action() {
    return m_action;
}

#include<QDebug>
void Actor::speak(const QString &message) {
     qDebug() << message;
}

void Actor::action(const QString &action) {
   if(asset_manager()->hasAction(action)) {
        m_action = action;
        emit actionChanged(this);
  }
   else
       throw "Actor::action unknown action : " + action;
}

bool Actor::is_moving() {
    return action() == "walking";
}

void Actor::addRule(RuleSet *rule) {
    m_rules << rule;
}

QJsonArray Actor::friends() {
    return assetmanager()->actorFriends();
}

QJsonArray Actor::foes() {
    return assetmanager()->actorFoes();
}

QJsonArray Actor::actions() {
    return assetmanager()->actorActions();
}

QString Actor::primaryFightAction() {
    return assetmanager()->actorPrimaryFightAction();
}

QVector<RuleSet *> Actor::rules() {
    return m_rules;
}


void Actor::advance(int step) {
    Sprite::advance(step);
    if (!step) return;
    animate();
}



AssetManager *Actor::asset_manager() const
{
    return m_asset_manager;
}


mfg::Engine *Actor::game_engine() const
{
    return m_game_engine;
}

void Actor::game_engine(mfg::Engine *game_engine)
{
    m_game_engine = game_engine;
}


void Actor::drawStats(QPainter* painter) {
    const int rect_length = m_sprite_width/2;
    QFont font = painter->font();
    font.setPixelSize(6);
    painter->setFont(font);
    QPen pen;  // creates a default pen
    pen.setWidth(1);
    pen.setBrush(Qt::blue);
    pen.setBrush(Qt::blue);
    float life_left = rect_length * life() / max_life();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::gray);
    painter->drawRect(0,-5,rect_length,3);
    if(life()>60) {
       painter->setBrush(Qt::green);
    }
    else if(life()>30) {
       painter->setBrush(Qt::yellow);
    }
    else {
       painter->setBrush(Qt::red);
    }
    painter->setPen(Qt::NoPen);
    painter->drawRect(0,-5,life_left,3);
    painter->setPen(pen);
    painter->drawText(QPoint(0,0),QString::number(life()));
}

void Actor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        Sprite::paint(painter,option,widget);

    /* In this graphic renderer we draw the sprite
     * The first two arguments - are the X and Y coordinates of where to put QPixmap
     * The third argument - a pointer to QPixmap which is the sprite sheet
     * 4 and 5 of the arguments - The coordinates in the image QPixmap, where the image is displayed
     * By setting the X coordinate with the variable currentFrame we are moving the camera
     * to the sprite frame in the sprite sheet
     * and the last two arguments - the width and height of the displayed area, that is, the frame
     * */
        QString currentAction = action();
        int currentDirection = direction();
        SpriteCoordinate coord = m_sprite_frames[currentAction][currentDirection][current_frame()];
        painter->drawPixmap( m_sprite_image_top,m_sprite_image_left, *m_pixmap,
                         coord.first, coord.second, this->m_sprite_width,this->m_sprite_height);

        if(isColliding()) {
        painter->setBrush( getCollisionBrush() );
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(QPoint(-5,-5),2,2);
        }
        drawStats(painter);
        setToolTip(name()+QString(" - (")+QString::number(x())+QString(",")+QString::number(y())+QString(")"));
}

void Actor::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Sprite::mousePressEvent(event);
}

#include<QDebug>
void Actor::animate() {
    float distance=m_advance_distance;
    //if(!step) return;
    advance_frame(1);
    int elapsed = ((GameScene*)scene())->current_time().elapsed();
    if(elapsed > 1) {
        m_current_frame++;
        distance+=2.0;
    }
    if(m_current_frame > m_animation_cells -1)
        //then
        m_current_frame = 0;
//    if(name() != "hero") {
       checkBoundary();
//    }
    checkCollision();
    for(auto rule : rules()) {
       rule->apply(this);  // Apply the rules for the actor
    }
    if(m_animated && is_moving()) {
        switch(m_current_direction) {
            case SPRITE_DOWN:
                this->setPos(this->pos()+QPointF(0,distance));
                break;
            case SPRITE_UP:
                this->setPos(this->pos()+QPointF(0,-1*distance));
                break;
            case SPRITE_LEFT:
                this->setPos(this->pos()+QPointF(-1 * distance,0));
                break;
            case SPRITE_RIGHT:
                this->setPos(this->pos()+QPointF(distance,0));
                break;
        }
        emit spriteMove(this);
    }

}

void Actor::changeAnimationFrames(Sprite *sprite) {
     m_animation_cells =  this->asset_manager()->spritePageColumns(action()+"_down");
}


#include<QDebug>
Actor *operator<<(Actor *actor, const QString &message) {
    qDebug() << message;
    return actor;
}

/*
Actor *operator<<(Actor *actor, const char *message) {
    actor << QString(message);
    return actor;
}
*/
