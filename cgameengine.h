#ifndef CGAMEENGINE_H
#define CGAMEENGINE_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QScriptEngine>
#include <QUrl>
#include <QVector>
#include "assetmanager.h"
#include "scenemanager.h"

class CRuleSet;
namespace mfg {

struct Stats{
    int health,stamina,wealth,manna,life;
};

typedef QMap<QString,CRuleSet*> RuleMap;
typedef QMap<QString,AssetManager*> AssetManagerMap;
typedef QMap<QString,QPixmap*> PixmapMap;

class Engine {
    QScriptEngine *m_script_engine;
    SceneManager *m_scene_manager;
    RuleMap m_actor_rules;
    AssetManagerMap m_assets;
    PixmapMap m_pixmaps;
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;

public:
    Engine();
    static QVector<QString> actors();
    QScriptEngine *scriptengine(){return m_script_engine;}
    QUrl audioFile(const QString &file);
    Stats getDefaultStats(const QString& name);//{}
    int max_life(const QString &name) const;
    void buildActorRules();
    void buildAssetMap();
    void buildPixmaps();
    AssetManager* addAssetManager(const QString& name,AssetManager* am);
    AssetManager* assetManager(const QString& name);
    CRuleSet* ruleFactory(const QString &name);
    CRuleSet *actorRule(const QString &name);
    CRuleSet *addActorRule(const QString &name,CRuleSet *rule);
    QPixmap *addPixmap(const QString &name,QPixmap *pm);
    QPixmap *pixMap(const QString &name);
    RuleMap getActor_rules() const;
    void setActor_rules(const RuleMap &player_rules);
    QMediaPlayer *mediaplayer() const;
    void setMediaPlayer(QMediaPlayer *player);
    QMediaPlaylist *mediaplaylist() const;
    void setPlaylist(QMediaPlaylist *playlist);
    SceneManager *sceneManager() const;
    void setSceneManager(SceneManager *sceneManager);
};

};

#endif // CGAMEENGINE_H
