#ifndef HERORULES_H
#define HERORULES_H
#include "actor.h"
#include "ruleset.h"
class HeroRules : public RuleSet
{
public:
    HeroRules(mfg::Engine *ge);
    virtual void apply(Actor*);
};

#endif // HERORULES_H
