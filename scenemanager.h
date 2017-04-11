#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <QMap>

class QObject;
class QString;
class GameScene;
typedef QMap<QString,GameScene*> SceneMap;
typedef QObject CObject;

namespace mfg {
  class Engine;
}

/**
 * @brief The SceneManager class - defines a SceneManager
 */
class SceneManager
{
    mfg::Engine *m_engine;
    SceneMap m_scene_map;
public:
    SceneManager(mfg::Engine *engine);
    GameScene *createScene(const QString &name, CObject *parent);
    GameScene *getScene(const QString &name);
    mfg::Engine *game_engine();
};

#endif // SCENEMANAGER_H
