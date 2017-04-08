#ifndef MONSTERRULES_H
#define MONSTERRULES_H
#include "cruleset.h"

class Actor;
class MonsterRules : public CRuleSet
{
public:
    MonsterRules(mfg::Engine *ge);
    virtual void apply(Actor*);
};

#endif // MONSTERRULES_H
