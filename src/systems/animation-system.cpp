#include "game.h"
#include "components.h"
#include "animation-system.h"
#include <unordered_map>

AnimationSystem::AnimationSystem() {}

void AnimationSystem::onAddedToWorld(World* world)
{
}

void AnimationSystem::tick(World* world)
{
    Entity* player = world->find<PlayerComponent>();
    PlayerComponent* p = player->get<PlayerComponent>();
    SpriteComponent* s = player->get<SpriteComponent>();
    
    if (p->UP) s->spriteId = PLAYER_JUMPING_1;
    else if (p->LEFT || p->RIGHT) {
        bool inc = world->countedFrames % 4 == 0;
        
        switch(s->spriteId) {
            case(PLAYER_RUNNING_1):
                if (inc) s->spriteId = PLAYER_RUNNING_2;
                break;
            case(PLAYER_RUNNING_2):
                if (inc) s->spriteId = PLAYER_RUNNING_3;
                break;
            case(PLAYER_RUNNING_3):
                if (inc) s->spriteId = PLAYER_RUNNING_4;
                break;
            case(PLAYER_RUNNING_4):
                if (inc) s->spriteId = PLAYER_RUNNING_5;
                break;
            case(PLAYER_RUNNING_5):
                if (inc) s->spriteId = PLAYER_RUNNING_6;
                break;
            default:
                if (inc) s->spriteId = PLAYER_RUNNING_1;
        }
    }
    else s->spriteId = PLAYER_IDLE_1;
}

void AnimationSystem::handleEvent(SDL_Event& event, World* world)
{
};

void AnimationSystem::onRemovedFromWorld(World* world)
{
}




