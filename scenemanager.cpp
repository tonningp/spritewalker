#include <QGraphicsProxyWidget>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "ctilescene.h"
#include "cgameengine.h"
#include "scenemanager.h"
#include "cconsolewidget.h"

SceneManager::SceneManager(mfg::Engine *engine) : m_engine(engine) {

}

/**
 * @brief SceneManager::createScene
 * 		creates the scene by name
 * 		TODO: build scene from json description if available
 * @param name:string the name of the scene
 * @param parent the parent for the scene, usually the main window
 * @return scene the newly created scene
 */
#include<QDebug>
CTileScene *SceneManager::createScene(const QString &name,QObject* parent) {
    QString settings;
    QFile file;
    file.setFileName(":/config/scenes/"+name+".json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    settings = file.readAll();
    file.close();
    QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());
    if(sd.isEmpty()) {
        throw "Error with JSON Document: " + name + ".json";
    }
    QJsonObject sett2 = sd.object();
    auto properties = sett2["properties"].toObject();
    int x = properties["rect"].toObject()["x"].toInt();
    int y = properties["rect"].toObject()["y"].toInt();
    int width = properties["rect"].toObject()["width"].toInt();
    int height = properties["rect"].toObject()["height"].toInt();
    CTileScene *scene = new CTileScene(this,parent,QRectF(x,y,width,height));
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->gameEngine()->mediaplayer()->setPlaylist(scene->gameEngine()->mediaplaylist());
    scene->gameEngine()->mediaplayer()->setVolume(5);
    scene->setName(name);
    if(name == "melba01") {
        scene->setBackgroundBrush(Qt::gray);
        auto bkg = scene->setBackgroundImageByName("background01");
        bkg->setPos(-1*scene->sceneRect().height()/2-175, -1*scene->sceneRect().height()/2);
        bkg->setZValue(-1000);
    }
    else if(name == "space01") {
        scene->setBackgroundBrush(Qt::black);
    }
    m_scene_map.insert(name,scene);
    return scene;
}

CTileScene *SceneManager::getScene(const QString &name) {
    return m_scene_map[name];
}

mfg::Engine *SceneManager::game_engine() {
    return m_engine;
}


