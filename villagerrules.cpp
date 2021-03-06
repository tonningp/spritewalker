#include "actor.h"
#include "utilities.h"
#include "ruleset.h"
#include "villagerrules.h"

VillagerRules::VillagerRules(mfg::Engine *ge):RuleSet::RuleSet(ge) {
}

void VillagerRules::apply(Actor * actor) {
    actor = ActorPointer(actor);
    if(actor && actor->isColliding()) {
        for(auto item: actor->collidingList()) {
                ActorPointer collides_with = (Actor*)item;
                if(collides_with && actor->foes().contains(collides_with->name())) {
                         actor->collisionState(Collision_State::FOE);
                         collides_with->collisionState(Collision_State::FOE);
                         if(collides_with->life(-3) <= 0) {
                             actor->direction((Sprite_Direction)Utilities::randInt(0,3));
                         }
                         actor->direction((Sprite_Direction)Utilities::randInt(0,3));
                }
                else{
                        if(actor) actor->collisionState(Collision_State::FRIEND);
                        if(collides_with) collides_with->collisionState(Collision_State::FRIEND);
                        actor->direction((Sprite_Direction)Utilities::randInt(0,3));
                }
       }
    }
}
