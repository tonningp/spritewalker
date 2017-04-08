#include "cruleset.h"
#include "actor.h"


CRuleSet::CRuleSet(mfg::Engine *ge):m_game_engine(ge) {
}

Actor* CRuleSet::actor(Actor* actor) {
    m_actor = actor;
    return m_actor;
}

Actor* CRuleSet::actor() {
    return m_actor;
}

QJsonArray CRuleSet::friends() {
    return m_actor->friends();
}

QJsonArray CRuleSet::foes() {
    return m_actor->foes();
}

