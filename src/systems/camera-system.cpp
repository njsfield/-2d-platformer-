#include "game.h"
#include "components.h"
#include "camera-system.h"
#include "constants.h"
#include <unordered_map>

CameraSystem::CameraSystem() {}

void CameraSystem::onAddedToWorld(World* world)
{

};

void CameraSystem::tick(World* world)
{
    Entity* camera = world->find<CameraComponent>();
    CameraComponent* cam = camera->get<CameraComponent>();

    Entity* player = world->find<PlayerComponent>();
    PositionComponent* pos = player->get<PositionComponent>();
    TransformComponent* t = player->get<TransformComponent>();
    
    cam->x = ( pos->x + t->w / 2 ) - SCREEN_WIDTH / 2;
    cam->y = ( pos->y + t->h / 2 ) - SCREEN_HEIGHT / 2;
        
    //Keep the camera in bounds.
    if( cam->x < 0 )
    {
        cam->x = 0;
    }
    if( cam->y < 0 )
    {
        cam->y = 0;
    }
    if( cam->x > world->LEVEL_WIDTH - cam->w )
    {
        cam->x = world->LEVEL_WIDTH - cam->w;
    }
    if( cam->y > world->LEVEL_HEIGHT - cam->h )
    {
        cam->y = world->LEVEL_HEIGHT - cam->h;
    }
};

void CameraSystem::handleEvent(SDL_Event& event, World* world)
{
};

void CameraSystem::onRemovedFromWorld(World* world)
{
}




