#include "ruleset.h"
#include "actor.h"


RuleSet::RuleSet(mfg::Engine *ge):m_game_engine(ge) {
}

Actor* RuleSet::actor(Actor* actor) {
    m_actor = actor;
    return m_actor;
}

Actor* RuleSet::actor() {
    return m_actor;
}

QJsonArray RuleSet::friends() {
    return m_actor->friends();
}

QJsonArray RuleSet::foes() {
    return m_actor->foes();
}

