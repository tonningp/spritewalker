#ifndef HERORULES_H
#define HERORULES_H
#include "actor.h"
#include "cruleset.h"
class HeroRules : public CRuleSet
{
public:
    HeroRules(mfg::Engine *ge);
    virtual void apply(Actor*);
};

#endif // HERORULES_H
