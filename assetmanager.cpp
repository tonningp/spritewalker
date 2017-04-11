#include "assetmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

AssetMap AssetManager::m_asset_map;

AssetManager::AssetManager(const QString& name) {
    m_name = name;
    init(name);
}

/**
 * @brief AssetManager::init - initialize the asset manager
 * @param name
 */
void AssetManager::init(const QString &name) {
    QString settings;
    QFile file;
    file.setFileName(":/config/characters/"+name+".json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    settings = file.readAll();
    file.close();
    QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());
    if(sd.isEmpty()) {
        throw "Error with JSON Document: " + name + ".json";
    }
    QJsonObject sett2 = sd.object();
    m_asset_map[name+"_sprite_sheet_name"] = sett2["spritesheet"].toString();
    m_asset_map[name+"_friends"] = sett2["friends"].toArray();
    m_asset_map[name+"_foes"] = sett2["foes"].toArray();
    m_asset_map[name+"_actions"] = sett2["actions"].toArray();
    m_asset_map[name+"_directions"] = sett2["directions"].toArray();
    m_asset_map[name+"_primary_fight_action"] = sett2["primary_fight_action"].toString();
    m_asset_map[name+"_default"] = QPixmap(sett2["spritesheet"].toString());
    QVariantMap imp = sett2["image_properties"].toVariant().toMap();
    for(auto key : imp.keys()) {
        m_asset_map[name+"_image_properties_"+key] = imp[key].value<int>();
    }
    m_asset_map[name+"_image_properties"] = sett2["image_properties"].toVariant().toMap();
    QVariantMap m = sett2["sprite_pages"].toVariant().toMap();
    for(auto key : m.keys()) {
        m_asset_map[name+"_sprite_"+key+"_row"] = m[key].value<QVariantMap>()["row"].value<int>();
        m_asset_map[name+"_sprite_"+key+"_col"] = m[key].value<QVariantMap>()["col"].value<int>();
        m_asset_map[name+"_sprite_"+key+"_cells"] = m[key].value<QVariantMap>()["cells"].value<int>();
    }
}


int AssetManager::spriteSheetHeight() {
    return map()[m_name+"_image_properties_height"].toInt();
}

int AssetManager::spriteSheetWidth() {
    return map()[m_name+"_image_properties_width"].toInt();
}

int AssetManager::spriteSheetColumns() {
    return map()[m_name+"_image_properties_columns"].toInt();
}

int AssetManager::spriteSheetRows() {
    return map()[m_name+"_image_properties_rows"].toInt();
}

int AssetManager::spriteWidth() {
    return map()[m_name+"_image_properties_sprite_width"].toInt();
}

int AssetManager::spriteHeight() {
    return map()[m_name+"_image_properties_sprite_height"].toInt();
}

QPixmap AssetManager::getSpriteImage(const QString &page) {
    return map()[m_name+"_"+page].value<QPixmap>();
}

QString AssetManager::getSpriteSheetName() {
   return map()[m_name+"_sprite_sheet_name"].toString();
}

int AssetManager::spritePageRow(const QString& page) {
    return map()[m_name+"_sprite_"+page+"_row"].toInt();
}

int AssetManager::spritePageCol(const QString& page) {
    return map()[m_name+"_sprite_"+page+"_col"].toInt();
}

int AssetManager::spritePageColumns(const QString& page) {
    return map()[m_name+"_sprite_"+page+"_cells"].toInt();
}

QJsonArray AssetManager::actorFriends() {
    return map()[m_name+"_friends"].toJsonArray();
}

QJsonArray AssetManager::actorFoes() {
    return map()[m_name+"_foes"].toJsonArray();
}

QJsonArray AssetManager::actorActions() {
    return map()[m_name+"_actions"].toJsonArray();
}

QJsonArray AssetManager::actorDirectionSet() {
    return map()[m_name+"_directions"].toJsonArray();

}

QString AssetManager::actorPrimaryFightAction() {
    return map()[m_name+"_primary_fight_action"].toString();
}

bool AssetManager::hasAction(const QString &name) {
    return actorActions().contains(name);
}

AssetMap AssetManager::map() {
    return m_asset_map;
}

QString AssetManager::name() {
    return m_name;
}

CoordinatesVector AssetManager::image_coordinates(int frame)
{

}
