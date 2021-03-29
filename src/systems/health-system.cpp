#include "game.h"
#include "components.h"
#include "health-system.h"
#include "constants.h"
#include <unordered_map>

HealthSystem::HealthSystem(std::function<void(void)> cb) : gameOverCallback(cb) {}

void HealthSystem::onAddedToWorld(World* world) {};

void HealthSystem::tick(World* world)
{
    Entity* player = world->find<PlayerComponent>();
    HealthComponent* h = player->get<HealthComponent>();
    if (h->health == 0)
        gameOverCallback();
};

void HealthSystem::handleEvent(SDL_Event& event, World* world)
{
};

void HealthSystem::onRemovedFromWorld(World* world)
{
}




