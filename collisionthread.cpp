#include "collisionthread.h"
#include<QDebug>


CollisionThread::CollisionThread(QObject *parent) : QThread(parent) {
    m_abort = false;
}

CollisionThread::~CollisionThread() {
    mutex.lock();
    m_abort = true;
    mutex.unlock();

    wait();
}

void CollisionThread::processScene(CTileScene* scene) {
    if (scene == NULL)
            return;
    m_scene = scene;
    m_abort = false;
    start();

}

void CollisionThread::stopProcess()
{

}

int CollisionThread::randInt(int low, int high)
{
// Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

void CollisionThread::run() {
    StringSet badguys({"monster","scheusal"});
    StringSet goodguys({"villager","hero"});
    SpriteList deadlist;
    for(auto item: m_scene->items()) {
        if(item != NULL && item->data(0) == "Sprite" && dynamic_cast<characters::Actor*>(item)->isColliding()) {
            characters::Actor* actor = dynamic_cast<characters::Actor*>(item);
            for(auto collides_with: actor->collidingList()) {
                if(badguys.contains(actor->name())) {
                      if(goodguys.contains(collides_with->name())) {
                         actor->collisionState(Collision_State::FOE);
                         collides_with->collisionState(Collision_State::FOE);
                      if(collides_with->name() == "villager"){
                         actor->direction((Sprite_Direction)randInt(0,3));
                         if(dynamic_cast<characters::Actor*>(collides_with)->life(-5) <= 0) {
                             deadlist << collides_with;
                         }
                    }
                    else {
                         if(dynamic_cast<characters::Actor*>(collides_with)->life(-1) <= 0) {
                             deadlist << collides_with;
                         }
                    }
                      }
                      else{
                        actor->collisionState(Collision_State::FRIEND);
                        collides_with->collisionState(Collision_State::FRIEND);
                      }
                } else if(goodguys.contains(actor->name())) {
                      if(badguys.contains(collides_with->name())) {
                         actor->collisionState(Collision_State::FOE);
                         collides_with->collisionState(Collision_State::FOE);
                      if(actor->name() == "villager"){
                         actor->direction((Sprite_Direction)randInt(0,3));
                         if(dynamic_cast<characters::Actor*>(collides_with)->life(-5) <= 0) {
                             deadlist << collides_with;
                         }
                    }
                    else {
                         if(dynamic_cast<characters::Actor*>(collides_with)->life(-1) <= 0) {
                             deadlist << collides_with;
                         }
                    }
                      }
                      else{
                         actor->collisionState(Collision_State::FRIEND);
                      }
                }
            }
        }
    }
    qDebug() << "Begin";
    for(auto item : deadlist) {
        m_scene->removeActor(item);
    }
    qDebug() << "End";
    msleep(10);

}
