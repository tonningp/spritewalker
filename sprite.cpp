#include "sprite.h"
#include <QGraphicsScene>

Sprite::Sprite(const QString &name,mfg::Engine* game_engine,bool moving,QObject *parent) :
    QObject(parent),QGraphicsItem(),
    m_game_engine(game_engine),
    m_pixmap(game_engine->pixMap(name)),
    m_asset_manager(game_engine->assetManager(name)),
    m_sprite_width(game_engine->assetManager(name)->spriteWidth()),
    m_sprite_height(game_engine->assetManager(name)->spriteHeight()),
    m_sprite_image_top(-10),
    m_sprite_image_left(-10),
    m_sprite_rows(game_engine->assetManager(name)->spriteSheetRows()),
    m_sprite_cols(game_engine->assetManager(name)->spriteSheetColumns()),
    m_animated(moving),
    m_start_row(0),m_sprite_speed(300),
    m_advance_distance(1.5) {

    if(this->assetmanager()->hasAction("stationary")) {
        m_stationary = true;
    }
    else {
        m_stationary = false;
    }

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    direction(Sprite_Direction::SPRITE_DOWN);
    m_sprite_name = name;
    m_left_adjust=0;
    m_top_adjust=0;
    m_right_adjust = 0;
    m_bottom_adjust = 0;

    buildCoordinates();
    guid(SequentialGUID::GetSequentialGUID(SequentialGUID::SequentialAsString));
}


Sprite_Direction Sprite::direction() {
    return m_current_direction;
}

void Sprite::direction(Sprite_Direction d) {
    m_current_direction = d;
}


void Sprite::name(const QString& name) {
    m_sprite_name = name;
}

bool Sprite::isColliding() {
    return m_collision;
}

void Sprite::collisionState(Collision_State state) {
    m_collision_state = state;
}

QBrush Sprite::getCollisionBrush() {
    if(m_collision_state == FOE)
        return Qt::red;
    else if(m_collision_state == FRIEND)
        return Qt::green;
    else
        return Qt::gray;

}

Collision_State Sprite::collisionState() {
    return m_collision_state;
}

SpriteList Sprite::collidingList() {
    return m_colliding_list;
}

QString Sprite::name() const{
    return m_sprite_name;
}


QRectF Sprite::boundingRect() const {
    return QRectF(m_sprite_image_top,m_sprite_image_left,m_sprite_width,m_sprite_height);
}

QUuid Sprite::guid() const
{
    return m_guid;
}

void Sprite::guid(const QUuid &guid)
{
    m_guid = guid;
}

void Sprite::buildCoordinates() {
    m_current_frame = 0;   // Sets the coordinates of the current frame of the sprite
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Q_UNUSED Indicates to the compiler that the parameter with the specified name
    // is not used in the body of a function. This can be used to suppress
    // compiler warnings while allowing functions to be defined with meaningful
    // parameter names in their signatures.
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_stationary) {
        painter->drawPixmap( m_sprite_image_top,m_sprite_image_left, *m_pixmap,0,0,m_sprite_width,m_sprite_height);
    }
    emit spritePainting(this,painter,option,widget);
}

void Sprite::checkIfOutOfBounds() {
    QRectF sceneRect = scene()->sceneRect();
    if (x() < sceneRect.left()+m_left_adjust) { // left
            //setPos(sceneRect.left()+left_adjust, y());
            direction(SPRITE_RIGHT);
    }
    else if (x() + boundingRect().right() > sceneRect.right()) {
            //setPos(sceneRect.right() - boundingRect().width()/2+right_adjust, y());
            direction(SPRITE_LEFT);
    }

    if (y() < sceneRect.top()+m_top_adjust) {
            //setPos(x(), sceneRect.top()+top_adjust);
            direction(SPRITE_DOWN);
    }
    else if ( y()+ boundingRect().bottom() > sceneRect.bottom()) {
            //setPos(x(), sceneRect.bottom() - boundingRect().height()/2+bottom_adjust);
            direction(SPRITE_UP);
    }
}

bool Sprite::isSprite(const QGraphicsItem *item) {
    return item->data(0) == "Sprite" || item->data(0) == "Actor";
}

mfg::Engine *Sprite::gameengine() {
    return m_game_engine;
}

AssetManager *Sprite::assetmanager() {
    return m_asset_manager;

}

SpriteFramesMap Sprite::spriteFrames() {
    return m_sprite_frames;
}

SpriteFramesMap Sprite::addSpriteFrameCoordinates(const QString &name,Coordinates coord) {
    m_sprite_frames[name] << coord;
    return m_sprite_frames;
}

int Sprite::spriteSize() {
    return m_sprite_width;
}

void Sprite::checkCollision() {
    ItemList list = scene()->collidingItems(this);
    //SpriteList sprite_list;
    m_colliding_list.clear();
    m_collision = false;
    for(auto item : list) {
      if( isSprite(item)) { // we are colliding with a Sprite
          m_collision = true;
          //SpritePointer current = (Sprite*)item;
          m_colliding_list << (Sprite*)item;
      }
    }
    if(m_colliding_list.empty()) {
        m_collision = false;
    }// else {
      // emit spriteCollision(this,&sprite_list);
    //}
}

/**
 * @brief Sprite::nextFrame
 * Will set the frame as well as the position of the sprite in the scene
 */
void Sprite::advance(int step) {
    //QGraphicsItem::advance(step);
    if (!step) return;
    this->update_sprite();
}

int Sprite::animation_cells() const
{
    return m_animation_cells;
}

void Sprite::animation_cells(int animation_cells)
{
    m_animation_cells = animation_cells;
}

bool Sprite::stationary() const
{
    return m_stationary;
}

int Sprite::sprite_height() const
{
    return m_sprite_height;
}

int Sprite::sprite_width() const
{
    return m_sprite_width;
}

void Sprite::update_sprite() {
    if(m_animated)
       this->update(m_sprite_image_top,m_sprite_image_left,m_sprite_width,m_sprite_height);
}

bool Sprite::animating() const
{
    return m_animated;
}

void Sprite::animating(bool animated)
{
    m_animated = animated;
}

int Sprite::sprite_image_left() const
{
    return m_sprite_image_left;
}

void Sprite::sprite_image_left(int sprite_image_left)
{
    m_sprite_image_left = sprite_image_left;
}

int Sprite::sprite_image_top() const
{
    return m_sprite_image_top;
}

void Sprite::sprite_image_top(int sprite_image_top)
{
    m_sprite_image_top = sprite_image_top;
}

float Sprite::advance_distance() const
{
    return m_advance_distance;
}

void Sprite::advance_distance(float advance_distance)
{
    m_advance_distance = advance_distance;
}

int Sprite::current_frame() const
{
    return m_current_frame;
}

void Sprite::current_frame(int current_frame)
{
    m_current_frame = current_frame;
}

int Sprite::advance_frame(int i) {
    return m_current_frame += i;
}

void Sprite::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit spriteClick(event,this);
}

void Sprite::animate() {

}
