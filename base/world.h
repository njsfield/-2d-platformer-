//
//  world.h
//  ecs
//
//  Created by Nicholas Field on 26/03/2021.
//

#ifndef world_h
#define world_h

#include <typeindex>
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <functional>
#include <SDL2/SDL.h>
#include "sprite_ids.h"

class World;

struct Component
{
    virtual ~Component() = default;
};

class Entity
{
private:
    std::unordered_map<std::type_index, Component*>* components;
public:
    Entity() : components{new std::unordered_map<std::type_index, Component*>()} {};
    
    template<typename ComponentType, typename... Args>
    void assign(Args&& ... arguments) {
        auto* component = new ComponentType(std::forward<Args&&>(arguments)...);
        auto typeIndex = std::type_index(typeid(ComponentType));
        components->insert_or_assign(typeIndex, component);
    };
    
    template<typename ComponentType>
    void remove(){
        auto typeIndex = std::type_index(typeid(ComponentType));
        components->erase(typeIndex);
    };
    
    template<typename ComponentType>
    bool has(){
        auto typeIndex = std::type_index(typeid(ComponentType));
        return components->find(typeIndex) != components->end();
    };
    
    template<typename A, typename B, typename... Rest>
    bool has(){
        return has<A>() && has<B, Rest...>();
    };
    
    template<typename A, typename B, typename... Rest>
    bool hasAny(){
        return has<A>() || has<B, Rest...>();
    };
    
    bool clearComponents() {
        components->clear();
        return true;
    }
    
    template<typename C>
    C* get() {
        return static_cast<C*>((*components)[std::type_index(typeid(C))]);
    }
    
    ~Entity() {
        for (auto& component : *components) delete component.second;
        components->clear();
    }
};

// Systems should be stateless!
class System {

    friend class World;

public:
    virtual void onAddedToWorld(World* world) {}

    virtual void tick(World* world) = 0;

    virtual void handleEvent(SDL_Event& event, World* world) {}

    virtual void onRemovedFromWorld(World* world) {}

    virtual ~System() = default;

};

struct SpriteCoord
{
    int x, y, w, h;
};

class World
{
private:
    std::vector<Entity*> entities;
    std::vector<System*> systems;
public:
    int countedFrames;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int LEVEL_WIDTH;
    int LEVEL_HEIGHT;

    World() {};
    
    Entity* create()
    {
        Entity* e = new Entity();
        entities.push_back(e);
        return e;
    };
    
    void destroyEntity(Entity* e)
    {
        if (!e) return;
        auto it = std::find(entities.begin(), entities.end(), e);
        if (it != entities.end()) entities.erase(it);
        delete e;
    };
    
    void destroyEntities()
    {
        for (auto entity : entities) delete entity;
        entities.clear();
    };
    
    template <typename S, typename... Args>
    S* registerSystem(Args&& ... arguments) {
        auto system = new S(std::forward<Args&&>(arguments)...);
        systems.push_back(system);
        system->onAddedToWorld(this);
        return system;
    }
    
    void unregisterSystem(System* s)
    {
        if (!s) return;
        auto it = std::find(systems.begin(), systems.end(), s);
        if (it != systems.end()) systems.erase(it);
        s->onRemovedFromWorld(this);
        delete s;
    };
    
    ~World() {
        for (auto system : systems) {
            system->onRemovedFromWorld(this);
            delete system;
        }
        systems.clear();

        for (auto entity : entities) delete entity;
        entities.clear();
    }
    
    template<typename...Components>
    Entity* find()
    {
        for (auto e : entities) {
            if (e->has<Components...>()) { return e; };
        };
        return nullptr;
    };
    
    template<typename...Components>
    void findFirst(const std::function<void(Entity*)>& callback)
    {
        for (auto e : entities) {
            if (e->has<Components...>()) { return callback(e); };
        };
    }
    
    template<typename...Components>
    void findAll(const std::function<void(Entity*)>& callback)
    {
        for (auto e : entities) {
            if (e->has<Components...>()) callback(e);
        };
    }
    
    template<typename...Components>
    void findAny(const std::function<void(Entity*)>& callback)
    {
        for (auto e : entities) {
            if (e->hasAny<Components...>()) callback(e);
        };
    }
    
    void tick() {
        for (auto system : systems) system->tick(this);
    }

    void handleEvent(SDL_Event& event) {
        for (auto system : systems) system->handleEvent(event, this);
    }
};

#endif /* world_h */
