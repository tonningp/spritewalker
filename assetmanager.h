#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QJsonArray>
#include <QMap>
#include <QPixmap>
#include <QSet>
#include <QVariantMap>


typedef QPair<float,float> SpriteCoordinate;
typedef QVector<SpriteCoordinate> Coordinates;
typedef QVector<Coordinates> CoordinatesVector;

typedef QVariantMap AssetMap;
typedef QVariantMap ImageMap;
typedef QVariantMap PropertyMap;

enum Sprite_Direction {SPRITE_DOWN,SPRITE_LEFT,SPRITE_RIGHT,SPRITE_UP};
enum Collision_State {FRIEND,FOE,NEUTRAL};

struct {
    int width,height;
} ImageInfo;

class AssetManager
{
    static AssetMap m_asset_map;
    QString m_name;
    CoordinatesVector m_sprite_image_coordinates;

public:
    AssetManager(const QString& name);
    QPixmap getSpriteImage(const QString& page);
    QString getSpriteSheetName();
    AssetMap map();
    QString name();
    CoordinatesVector image_coordinates(int frame);
    int spriteSheetHeight();
    int spriteSheetWidth();
    int spriteSheetColumns();
    int spriteSheetRows();
    int spriteWidth();
    int spriteHeight();
    int spritePageRow(const QString &);
    int spritePageCol(const QString &page);
    int spritePageColumns(const QString &name);
    QJsonArray actorFriends();
    QJsonArray actorFoes();
    QJsonArray actorActions();
    QJsonArray actorDirectionSet();
    QString actorPrimaryFightAction();
    bool hasAction(const QString& name);
private:
    void init(const QString &name);

};

#endif // IMAGEMANAGER_H
