//
//  animation-system.h
//  ecs
//
//  Created by Nicholas Field on 31/03/2021.
//

#ifndef animation_system_h
#define animation_system_h

#include "world.h"
#include <unordered_map>

class AnimationSystem : public System
{
public:
    AnimationSystem();

    void onAddedToWorld(World* world) override;

    void tick(World* world) override;

    void handleEvent(SDL_Event& event, World* world) override;

    void onRemovedFromWorld(World* world) override;

    ~AnimationSystem() = default;
};

#endif /* animation_system_h */
