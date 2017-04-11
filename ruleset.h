#ifndef RULESET_H
#define RULESET_H

#include <QJsonArray>
#include <QSet>
#include <QString>

class Actor;
namespace mfg {
  class Engine;
}

typedef QSet<QString> StringSet;

/**
 * @brief The RuleSet class - define rules for characters
 */
class RuleSet
{
    Actor* m_actor;
public:
    RuleSet(mfg::Engine *ge);
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



#endif // RULESET_H
