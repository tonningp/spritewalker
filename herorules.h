#ifndef HERORULES_H
#define HERORULES_H
#include "ruleset.h"

class Actor;
namespace mfg {
 class Engine;
}
/**
 * @brief The HeroRules class - define rules for a Hero Actor
 */
class HeroRules : public RuleSet
{
public:
    HeroRules(mfg::Engine *ge);
    virtual void apply(Actor*);
};

#endif // HERORULES_H
