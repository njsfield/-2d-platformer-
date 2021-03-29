//
//  physics-system.h
//  ecs
//
//  Created by Nicholas Field on 30/03/2021.
//

#ifndef physics_system_h
#define physics_system_h

#include "world.h"

class PhysicsSystem : public System
{
public:
    PhysicsSystem();

    void onAddedToWorld(World* world) override;

    void tick(World* world) override;

    void handleEvent(SDL_Event& event, World* world) override;

    void onRemovedFromWorld(World* world) override;

    ~PhysicsSystem() = default;
};

#endif /* physics_system_h */
