#ifndef CRULESET_H
#define CRULESET_H

#include <QJsonArray>
#include <QSet>
#include <QString>

#include "gameengine.h"
#include "actor.h"

typedef QSet<QString> StringSet;
class CRuleSet
{
    Actor* m_actor;
public:
    CRuleSet(mfg::Engine *ge);
    virtual void apply(Actor*) = 0;

    Actor* actor(Actor *actor);
    Actor* actor();
    QJsonArray friends();
    QJsonArray foes();

protected:
    QJsonArray m_friends;
    QJsonArray m_foes;
    mfg::Engine *m_game_engine;
};



#endif // CRULESET_H
