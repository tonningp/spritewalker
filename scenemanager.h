#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

class QObject;
class QString;
class CTileScene;
namespace mfg {
  class Engine;
}
class CConsoleWidget;

class SceneManager
{
    mfg::Engine *m_engine;
public:
    SceneManager(mfg::Engine *engine);
    CTileScene *createScene(const QString &name, QObject *parent);
    mfg::Engine *game_engine();
};

#endif // SCENEMANAGER_H
