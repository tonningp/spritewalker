#ifndef VILLAGERRULES_H
#define VILLAGERRULES_H
#include "ruleset.h"

class Actor;
namespace mfg {
 class Engine;
}

/**
 * @brief The VillagerRules class - Rule set for a Villager
 */
class VillagerRules : public RuleSet
{
public:
    VillagerRules(mfg::Engine *ge);
    virtual void apply(Actor*);
};

#endif // VILLAGERRULES_H
