#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <QMap>

class QObject;
class QString;
class CTileScene;

typedef QMap<QString,CTileScene*> SceneMap;

namespace mfg {
  class Engine;
}
class CConsoleWidget;

class SceneManager
{
    mfg::Engine *m_engine;
    SceneMap m_scene_map;
public:
    SceneManager(mfg::Engine *engine);
    CTileScene *createScene(const QString &name, QObject *parent);
    CTileScene *getScene(const QString &name);
    mfg::Engine *game_engine();
};

#endif // SCENEMANAGER_H
