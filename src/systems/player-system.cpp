#include "game.h"
#include "components.h"
#include "player-system.h"

PlayerSystem::PlayerSystem() {}

void PlayerSystem::onAddedToWorld(World* world)
{
}

void PlayerSystem::tick(World* world)
{
}

void PlayerSystem::handleEvent(SDL_Event& event, World* world)
{
    if (event.type != SDL_KEYUP && event.type != SDL_KEYDOWN) return;
    
    Entity* player = world->find<PlayerComponent>();
    PlayerComponent* p = player->get<PlayerComponent>();
    
    if( event.type == SDL_KEYDOWN && event.key.repeat == 0 ) {
        switch( event.key.keysym.sym ){
            case SDLK_LEFT:
            {
                if (p->RIGHT) p->RIGHT = false;
                p->LEFT = true;
                p->forwardFacing = false;
                break;
            }
            case SDLK_RIGHT:
            {
                if (p->LEFT) p->LEFT = false;
                p->RIGHT = true;
                p->forwardFacing = true;
                break;
            }
            case SDLK_UP:
            {
                p->UP = true;
                break;
            }
            case SDLK_DOWN: {
                p->DOWN = true;
                break;
            }
            default:
                break;
        }
    }
    
    if ( event.type == SDL_KEYUP && event.key.repeat == 0 ) {
        switch( event.key.keysym.sym ){
            case SDLK_LEFT:
            {
                p->LEFT = false;
                break;
            }
            case SDLK_RIGHT:
            {
                p->RIGHT = false;
                break;
            }
            case SDLK_UP:
            {
                p->UP = false;
                break;
            }
            case SDLK_DOWN:
            {
                p->DOWN = false;
                break;
            }
            default:
                break;
        }
    };
};

void PlayerSystem::onRemovedFromWorld(World* world)
{
}

