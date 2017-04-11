#ifndef MONSTERRULES_H
#define MONSTERRULES_H
#include "ruleset.h"

class Actor;
class MonsterRules : public RuleSet
{
public:
    MonsterRules(mfg::Engine *ge);
    virtual void apply(Actor*);
};

#endif // MONSTERRULES_H
