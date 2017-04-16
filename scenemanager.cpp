#include <QGraphicsProxyWidget>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "gamescene.h"
#include "gameengine.h"
#include "scenemanager.h"
#include "consolewidget.h"

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
GameScene *SceneManager::createScene(const QString &name,QObject* parent) {
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
    // "x" : -525,"y" : -300, "width" : 1000, "height" : 600
    //QRectF rect = QRectF(QPointF(-1000,-2000), QSizeF(1000,200));
    QRectF rect = QRectF(QPointF(x,y), QSizeF(width,height));
    //QRectF rect = QRectF(QPointF(0,0), QSizeF(0,0));
    GameScene *scene = new GameScene(this,parent,rect);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->gameEngine()->mediaplayer()->setPlaylist(scene->gameEngine()->mediaplaylist());
    scene->gameEngine()->mediaplayer()->setVolume(5);
    scene->setName(name);
    if(name == "melba01") {
        QRectF sceneRect = scene->sceneRect();
        scene->setBackgroundBrush(Qt::gray);
        scene->addText("("+QString::number(0)+","+QString::number(0)+")");
        scene->addText("("+QString::number(sceneRect.x())+","+QString::number(sceneRect.y())+")")->setPos(sceneRect.x(),sceneRect.y());
        scene->addText("("+QString::number(sceneRect.x())+","+QString::number(sceneRect.y()+sceneRect.height())+")")
                      ->setPos(sceneRect.x(),sceneRect.y()+sceneRect.height());
        scene->addText("("+QString::number(sceneRect.x()+sceneRect.width())+","+QString::number(sceneRect.y())+")")
                      ->setPos(sceneRect.x()+sceneRect.width(),sceneRect.y());
        scene->addText("("+QString::number(sceneRect.x()+sceneRect.width())+","+QString::number(sceneRect.y()+sceneRect.height())+")")
                      ->setPos(sceneRect.x()+sceneRect.width(),sceneRect.y()+sceneRect.height());
        auto bkg = scene->setBackgroundImageByName("background01");
        bkg->setPos(-1*scene->sceneRect().height()/2-175, -1*scene->sceneRect().height()/2);
        bkg->setZValue(-1000);
        scene->addLine(scene->sceneRect().x(),scene->sceneRect().y(),scene->sceneRect().x()+scene->sceneRect().width(),scene->sceneRect().y());
        auto o1 = scene->addLine(QLineF(QPointF(-25,0),QPointF(25,0)),QPen(Qt::blue));
        o1->setData(0,"XAxis");
        auto o2 = scene->addLine(QLineF(QPointF(0,-25),QPointF(0,25)),QPen(Qt::blue));
        o2->setData(0,"YAxis");
        auto r = scene->addRect(scene->sceneRect(),QPen(Qt::black));
        r->setData(0,"Boundary");
    }
    else if(name == "space01") {
        scene->setBackgroundBrush(Qt::black);
    }
    m_scene_map.insert(name,scene);
    return scene;
}

GameScene *SceneManager::getScene(const QString &name) {
    return m_scene_map[name];
}

mfg::Engine *SceneManager::game_engine() {
    return m_engine;
}


