#include "gameengine.h"
#include "herorules.h"
#include "monsterrules.h"
#include "villagerrules.h"
#include "scheusalrules.h"

using namespace mfg;

Engine::Engine() {
    m_script_engine = new QScriptEngine;
    m_scene_manager = new SceneManager(this);
    buildAssetMap();
    buildActorRules();
    buildPixmaps();
    
    //qDebug() << scriptengine()->evaluate("function testf(v1){  return v1*2;};testf(10);").toNumber();
    addPixmap("background01",new QPixmap(":/assets/images/background_01.png"));
    m_player = new QMediaPlayer;
    m_playlist = new QMediaPlaylist();
    m_playlist->addMedia(audioFile("fantasy01"));
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

}

SceneManager *Engine::sceneManager() const
{
    return m_scene_manager;
}

void Engine::setSceneManager(SceneManager *scene_manager)
{
    m_scene_manager = scene_manager;
}

QMediaPlaylist *Engine::mediaplaylist() const
{
    return m_playlist;
}

void Engine::setPlaylist(QMediaPlaylist *playlist)
{
    m_playlist = playlist;
}

RuleMap Engine::getActor_rules() const
{
    return m_actor_rules;
}

void Engine::setActor_rules(const RuleMap &player_rules)
{
    m_actor_rules = player_rules;
}

QMediaPlayer *Engine::mediaplayer() const {
    return m_player;
}

void Engine::setMediaPlayer(QMediaPlayer *player) {
    m_player = player;
}

QVector<QString> Engine::actors() {
    return QVector<QString>({"monster","hero","male_villager","female_villager","scheusal","mountain","wilderness01","tree01"});
}

QUrl Engine::audioFile(const QString& file) {
    return QUrl("qrc:/assets/sound/"+file+".mp3");
}

Stats Engine::getDefaultStats(const QString &name) {
    Stats s;
    s.life = max_life(name);
    s.manna = 100;
    s.stamina = 100;
    s.wealth = 100;
    return s;
}

int Engine::max_life(const QString &name) const {
    return 300;
}

void Engine::buildActorRules() {
    for(auto name : actors()) {
       addActorRule(name,ruleFactory(name));
    }
}

#include<QDebug>
#include <QMediaPlaylist>
void Engine::buildAssetMap() {
    try{
        for(auto name : actors()) {
            addAssetManager(name,new AssetManager(name));
        }
    }
    catch(const QString &e) {
       qDebug() << e;
    }
}

void Engine::buildPixmaps() {
    for(auto name : actors()) {
        QPixmap *pm = new QPixmap(assetManager(name)->getSpriteImage("default"));
        addPixmap(name,pm);
    }
}

AssetManager *Engine::addAssetManager(const QString &name, AssetManager *am) {
    m_assets.insert(name,am);
    return am;
}

RuleSet *Engine::ruleFactory(const QString &name) {
    if(name == "hero") {
        return new HeroRules(this);
    }
    else if(name == "female_villager") {
        return new VillagerRules(this);
    }
    else if(name == "male_villager") {
        return new VillagerRules(this);
    }
    else if(name == "monster") {
        return new MonsterRules(this);
    }
    else if(name == "scheusal") {
        return new ScheusalRules(this);
    }
}

AssetManager *Engine::assetManager(const QString &name) {
    return m_assets[name];
}

RuleSet *Engine::actorRule(const QString &name) {
    return m_actor_rules[name];
}

RuleSet *Engine::addActorRule(const QString &name,RuleSet *rule) {
    m_actor_rules.insert(name,rule);
    return rule;
}

QPixmap *Engine::addPixmap(const QString &name, QPixmap *pm) {
    m_pixmaps.insert(name,pm);
    return pm;
}

QPixmap *Engine::pixMap(const QString &name) {
   return m_pixmaps[name];
}
