#include <QGraphicsProxyWidget>
#include "ctilescene.h"
#include "cgameengine.h"
#include "scenemanager.h"
#include "cconsolewidget.h"

SceneManager::SceneManager(mfg::Engine *engine) : m_engine(engine) {

}

CTileScene *SceneManager::createScene(const QString &name,QObject* parent) {
    CTileScene *scene = new CTileScene(this,parent,QRectF(-475,-300,950,600));
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->gameengine()->mediaplayer()->setPlaylist(scene->gameengine()->mediaplaylist());
    scene->gameengine()->mediaplayer()->setVolume(5);
    if(name == "melba01") {
        scene->setBackgroundBrush(Qt::black);
        auto bkg = scene->setBackgroundImageByName("background01");
        bkg->setPos(-1*scene->sceneRect().height()/2-175, -1*scene->sceneRect().height()/2);
        bkg->setZValue(-1000);
    }
    else if(name == "space01") {
        scene->setBackgroundBrush(Qt::black);
    }
    return scene;
}

mfg::Engine *SceneManager::game_engine() {
    return m_engine;
}


