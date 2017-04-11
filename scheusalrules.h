#ifndef SCHEUSALRULES_H
#define SCHEUSALRULES_H
#include "ruleset.h"

class Actor;
namespace mfg {
 class Engine;
}

/**
 * @brief The ScheusalRules class - Rule set for a Scheusal (Zombie)
 */
class ScheusalRules : public RuleSet
{
public:
    ScheusalRules(mfg::Engine *ge);
    virtual void apply(Actor*);
};

#endif // SCHEUSALRULES_H
