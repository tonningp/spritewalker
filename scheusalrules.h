#ifndef SCHEUSALRULES_H
#define SCHEUSALRULES_H
#include "cruleset.h"

class ScheusalRules : public CRuleSet
{
public:
    ScheusalRules(mfg::Engine *ge);
    virtual void apply(Actor*);
};

#endif // SCHEUSALRULES_H
