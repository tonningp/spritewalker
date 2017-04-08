#include "herorules.h"
#include "cutilities.h"

HeroRules::HeroRules(mfg::Engine *ge):CRuleSet::CRuleSet(ge) {
}

void HeroRules::apply(Actor* actor) {
    actor = ActorPointer(actor);
    if(actor && actor->isColliding()) {
        for(auto item: actor->collidingList()) {
                ActorPointer is_colliding_with = ActorPointer((Actor*)item);
                if(is_colliding_with && actor->foes().contains(is_colliding_with->name())) {
                         actor->collisionState(Collision_State::FOE);
                         is_colliding_with->collisionState(Collision_State::FOE);
                         if(is_colliding_with->life(-5) <= 0) {
                             actor->direction((Sprite_Direction)CUtilities::randInt(0,3));
                         }
                         actor->direction((Sprite_Direction)CUtilities::randInt(0,3));
                }
                else{
                        if(actor)  actor->collisionState(Collision_State::FRIEND);
                        if(is_colliding_with) is_colliding_with->collisionState(Collision_State::FRIEND);
                }
       }
    }

}