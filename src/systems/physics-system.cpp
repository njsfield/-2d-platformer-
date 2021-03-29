#include "game.h"
#include "components.h"
#include "physics-system.h"
#include "aabb.h"

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::onAddedToWorld(World* world)
{
}

void PhysicsSystem::tick(World* world)
{
    world->findAll<PlayerComponent>([&](Entity* player){
        PlayerComponent* p = player->get<PlayerComponent>();
        VelocityComponent* v = player->get<VelocityComponent>();
        PositionComponent* pos = player->get<PositionComponent>();
        TransformComponent* t = player->get<TransformComponent>();
        HealthComponent* h = player->get<HealthComponent>();
        
        // 1. Set X velocity
        v->velX = p->RIGHT ? 1 : p->LEFT ? -1 : 0;
        
        // 2. Speed speed (slide)
        if (world->countedFrames % 4 == 0) {
            // If right move, add 1 (max 5)
            if (v->velX > 0) v->speed = std::min(v->speed + 1, 3);
            
            // If left move, minus 1 (max -5)
            else if (v->velX < 0) v->speed = std::max(v->speed - 1, -3);
            
            // If no move, minus 1 if right, plus 1 if left
            else v->speed = v->speed > 0 ? std::max(v->speed - 1, 0) : std::min(v->speed + 1, 0);
        }
        
        // 2. Determine positions
        int prevX = pos->x;
        int prevY = pos->y;
        
        pos->x += v->velX + v->speed;
        pos->y += v->velY;
        
        // Gravity
        v->velY = std::min(v->velY + 1, 13);
        
        // Check if fall to death
        if (pos->y > world->LEVEL_HEIGHT) {
            h->health = 0;
            return;
        }
        
        world->findAll<TileComponent>([&](Entity* tile){

            PositionComponent* t_pos = tile->get<PositionComponent>();
            TransformComponent* t_trans = tile->get<TransformComponent>();
            
            AABB tileQuad = {t_pos->x, t_pos->y, t_pos->x + t_trans->w, t_pos->y + t_trans->h};
            AABB playerQuad = {pos->x, pos->y, pos->x + t->w, pos->y + t->h};

            // 4. If collision
            if (collide(&playerQuad, &tileQuad)) {
                // Reset
                
                // ALIGNED BOTTOM
                if (playerQuad.max.y == tileQuad.min.y) {
                    // Allow jump ?
                    v->velY = p->UP ? -16 : 0;
                    return;
                }
                
                // ALIGNED LEFT/RIGHT
                if (playerQuad.max.x == tileQuad.min.x ||
                    playerQuad.min.x == tileQuad.max.x) {
                    v->velX = 0;
                    return;
                }
                
                // ALIGNED TOP
                if (playerQuad.min.y == tileQuad.max.y) {
                    return;
                }
                
                // COLLISION - RESET
                // this will cause a loop if yVel unresolved
                pos->x = prevX;
                pos->y = prevY;
                
                if (v->velY > 0) {
                    pos->y = pos->y + (tileQuad.min.y - (pos->y + t->h));
                    v->velY = 0;
                };
            }
        });
        
    });
}

void PhysicsSystem::handleEvent(SDL_Event& event, World* world)
{
};

void PhysicsSystem::onRemovedFromWorld(World* world)
{
}


