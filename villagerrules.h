#ifndef VILLAGERRULES_H
#define VILLAGERRULES_H
#include "actor.h"
#include "cruleset.h"

class VillagerRules : public CRuleSet
{
public:
    VillagerRules(mfg::Engine *ge);
    virtual void apply(Actor*);
};

#endif // VILLAGERRULES_H
