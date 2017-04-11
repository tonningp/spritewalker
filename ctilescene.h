#ifndef CTILESCENE_H
#define CTILESCENE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTime>

namespace mfg {
    class Engine;
};
class Sprite;
class Actor;
class SceneManager;
class CConsoleWidget;
typedef Actor SceneActor;
typedef QList<SceneActor*> ActorList;
typedef QMap<QString,int> ActorCountMap;
typedef QList<QGraphicsItem*> GraphicsItemList;

class CTileScene : public QGraphicsScene
{
    Q_OBJECT

    QString m_name;
    Sprite *m_current_sprite;
    mfg::Engine *m_game_engine;
    SceneManager *m_scene_manager;
    GraphicsItemList m_deadlist;
    QTime m_current_time;
    QTimer *m_timer;
    CConsoleWidget *m_console;

public:
    explicit CTileScene(SceneManager* sm,QObject *parent = 0,const QRectF &rect=QRectF(-300,-300,600,600));
    void connectTimer(QTimer*);
    void drawGrid();
    void addItem(QGraphicsItem* item,const QString &name);
    SceneActor* addActor(const QString &name,const QString &start_action,bool moving);
    Sprite *addSprite(const QString &name, const QString &start_action, bool moving);
    void removeActor(SceneActor* );
    Sprite* current_sprite();
    Sprite* current_sprite(Sprite*);
    ActorCountMap getActorCounts();
    ActorList getAllActors();
    QVector<QString> players();
    int deadCount();
    void clearDead();
    bool isSceneActor(QGraphicsItem* item);
    void clearActors();
    GraphicsItemList getDeadlist() const;
    void setDeadlist(const GraphicsItemList &deadlist);
    QTime current_time();
    QGraphicsItem* setBackgroundImageByName(const QString& name);
    mfg::Engine *gameEngine();
    CConsoleWidget *console();

    SceneManager *sceneManager() const;
    void sceneManager(SceneManager *sceneManager);

    QTimer *timer();

    QString name() const;
    void setName(const QString &name);

protected slots:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

signals:

public slots:
    void spriteSelected(QGraphicsSceneMouseEvent*,Sprite*);
    void advance();
    void actorCollision();
};

#endif // CTILESCENE_H
