#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QPair>
#include <QPointer>
#include "sequentialguid.h"
#include "gameengine.h"

class Sprite;
typedef QList<Sprite*> SpriteList;
typedef QList<QGraphicsItem*> ItemList;
typedef QMap<QString,CoordinatesVector> SpriteFramesMap;
typedef QPointer<Sprite> SpritePointer;

class Sprite : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    //QBrush collision_brush;
public:
    Sprite(){}
    explicit Sprite(const QString &name,mfg::Engine *engine,bool moving,QObject *parent = 0);

    Sprite_Direction direction();
    void direction(Sprite_Direction d);
    virtual QString name() const;
    void name(const QString &name);
    bool isColliding();
    void collisionState(Collision_State);
    QBrush getCollisionBrush();
    Collision_State collisionState();
    SpriteList collidingList();
    bool isSprite(const QGraphicsItem* item);
    mfg::Engine *gameengine();
    AssetManager* assetmanager();
    SpriteFramesMap spriteFrames();
    SpriteFramesMap addSpriteFrameCoordinates(const QString &name,Coordinates coord);
    int spriteSize();

    QUuid guid() const;
    void guid(const QUuid &guid);

    int current_frame() const;
    void current_frame(int current_frame);
    int advance_frame(int);

    float advance_distance() const;
    void advance_distance(float advance_distance);

    int sprite_image_top() const;
    void sprite_image_top(int sprite_image_top);

    int sprite_image_left() const;
    void sprite_image_left(int sprite_image_left);

    bool animating() const;
    void animating(bool animating);
    void update_sprite();
    int sprite_width() const;
    int sprite_height() const;
    bool stationary() const;
    int animation_cells() const;
    void animation_cells(int animation_cells);

signals:
    void spriteClick(QGraphicsSceneMouseEvent*,Sprite *);
    void spriteMove(Sprite *);
    void actionChanged(Sprite *);
    void spriteCollision(Sprite *,SpriteList *);
    void spritePainting(Sprite *,QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void animate();

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void advance(int step) Q_DECL_OVERRIDE;

    QString m_sprite_name;
    bool m_animated;
    bool m_stationary;
    bool m_collision;
    Collision_State m_collision_state;
    int m_sprite_width;
    int m_sprite_height;
    int m_sprite_speed;
    QPixmap *m_pixmap;
    float m_advance_distance;
    int m_left_adjust,m_top_adjust,m_right_adjust,m_bottom_adjust;
    int m_sprite_image_top,m_sprite_image_left;
    int m_start_row,m_start_col,m_sprite_rows,m_sprite_cols;
    int m_animation_cells;
    Sprite_Direction m_current_direction;
    int m_current_frame;   // Coordinates X, which starts the next frame of the sprite
    SpriteFramesMap m_sprite_frames;
    void buildCoordinates();
    SpriteList m_colliding_list;
    AssetManager* m_asset_manager;
    mfg::Engine* m_game_engine;
    void checkIfOutOfBounds();
    void checkCollision();
    QRectF boundingRect() const override;
    QUuid m_guid;
};


#endif // SPRITE_H
