#include "actor.h"
#include "ruleset.h"
#include "utilities.h"
#include "scheusalrules.h"

ScheusalRules::ScheusalRules(mfg::Engine *ge):RuleSet::RuleSet(ge) {
}

void ScheusalRules::apply(Actor * actor) {
    actor = ActorPointer(actor);
    if(actor->isColliding()) {
        for(auto item: actor->collidingList()) {
                ActorPointer collides_with = (Actor*)item;
                // if collides_with is not valid Actor it is just a sprite
                if(collides_with && actor->foes().contains(collides_with->name())) {
                         actor->collisionState(Collision_State::FOE);
                         collides_with->collisionState(Collision_State::FOE);
                         if(collides_with->life(-5) <= 0) {
                             actor->direction((Sprite_Direction)Utilities::randInt(0,3));
                         }
                         actor->direction((Sprite_Direction)Utilities::randInt(0,3));
                }
                else{
                        actor->collisionState(Collision_State::FRIEND);
                        collides_with->collisionState(Collision_State::FRIEND);
                        actor->direction((Sprite_Direction)Utilities::randInt(0,3));
                }
       }
    }
}
