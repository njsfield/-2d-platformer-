//
//  camera-system.h
//  ecs
//
//  Created by Nicholas Field on 31/03/2021.
//

#ifndef camera_system_h
#define camera_system_h

#include "world.h"
#include <unordered_map>

class CameraSystem : public System
{
public:
    CameraSystem();

    void onAddedToWorld(World* world) override;

    void tick(World* world) override;

    void handleEvent(SDL_Event& event, World* world) override;

    void onRemovedFromWorld(World* world) override;

    ~CameraSystem() = default;
};

#endif /* animation_system_h */

