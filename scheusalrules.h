#ifndef SCHEUSALRULES_H
#define SCHEUSALRULES_H
#include "ruleset.h"

class ScheusalRules : public RuleSet
{
public:
    ScheusalRules(mfg::Engine *ge);
    virtual void apply(Actor*);
};

#endif // SCHEUSALRULES_H
