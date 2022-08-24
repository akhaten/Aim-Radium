#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include <Engine/Scene/EntityManager.hpp>
#include <Engine/Scene/GeometrySystem.hpp>


class Map
{

    public:
        Map(Ra::Engine::Scene::System* geometrySystem, Ra::Engine::Scene::EntityManager* entityManager);
        ~Map();

    private:
        std::vector<Ra::Engine::Scene::Entity*> objects;
        
};

#endif // MAP_HPP