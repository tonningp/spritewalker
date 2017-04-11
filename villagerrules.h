#ifndef VILLAGERRULES_H
#define VILLAGERRULES_H
#include "actor.h"
#include "ruleset.h"

class VillagerRules : public RuleSet
{
public:
    VillagerRules(mfg::Engine *ge);
    virtual void apply(Actor*);
};

#endif // VILLAGERRULES_H
