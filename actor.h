#ifndef ACTOR_H
#define ACTOR_H
#include "sprite.h"
#include "gameengine.h"
#include <QGraphicsSceneMouseEvent>
#include <QPointer>


/**
 * @brief The Actor class - provides a specific type of Sprite that defines both non player and player characters
 * @description
 */
class Actor : public Sprite {

    mfg::Stats m_stats;


public:
    explicit Actor(const QString &name,mfg::Engine *game_engine,const QString& start_action,bool moving,QObject *parent = 0);
    void connectAnimationTimer();
    void stats(const mfg::Stats&);
    mfg::Stats stats();
    int life(int);
    int life();
    int max_life()const;
    void drawStats(QPainter*);
    int isDead();
    QString name() const override;
    QString action();
    void speak(const QString &message);
    bool is_moving();
    void action(const QString&);
    void addRule(RuleSet*);
    QJsonArray friends();
    QJsonArray foes();
    QJsonArray actions();
    QString primaryFightAction();
    QVector<RuleSet*> rules();
    mfg::Engine *game_engine() const;
    void game_engine(mfg::Engine *game_engine);
    AssetManager *asset_manager() const;
    QPainterPath shape() const override;

friend Actor *operator<<(Actor* actor,const QString &message);
//friend Actor *operator<<(Actor* actor,const char *message);


public slots:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void animate();

private slots:
    virtual void changeAnimationFrames(Sprite* sprite);

protected:
    void buildActorPageCoordinates();
    void timerEvent(QTimerEvent *event) override;
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int step) Q_DECL_OVERRIDE;
    QVector<RuleSet*> m_rules;
    QString m_action;
    QString m_name;
    AssetManager* m_asset_manager;
    //QPixmap *m_pixmap;
    mfg::Engine *m_game_engine;
    //QElapsedTimer elapsed;
    //QBasicTimer elapsed;

};


typedef Actor SceneActor;
typedef RuleSet ActorRuleSet;
typedef QList<SceneActor*> ActorList;
typedef QPointer<SceneActor> ActorPointer;

#endif // ACTOR_H
