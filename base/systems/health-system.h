//
//  health-system.h
//  ecs
//
//  Created by Nicholas Field on 31/03/2021.
//

#ifndef health_system_h
#define health_system_h

#include "world.h"
#include <unordered_map>

class HealthSystem : public System
{
public:
    HealthSystem(std::function<void(void)> cb);

    void onAddedToWorld(World* world) override;

    void tick(World* world) override;

    void handleEvent(SDL_Event& event, World* world) override;

    void onRemovedFromWorld(World* world) override;

    ~HealthSystem() = default;
private:
    std::function<void(void)> gameOverCallback;
};

#endif /* animation_system_h */

