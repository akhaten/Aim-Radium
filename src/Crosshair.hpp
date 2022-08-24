#ifndef CROSSHAIR_HPP
#define CROSSHAIR_HPP


#include <Engine/Scene/EntityManager.hpp>
#include <Engine/Scene/GeometrySystem.hpp>

class Crosshair
{

    public:
        Crosshair(Ra::Engine::Scene::System* geometrySystem, Ra::Engine::Scene::EntityManager* entityManager);
        ~Crosshair();
        void update(Ra::Core::Transform transform);
        // void load();


    private:
        // Ra::Engine::Scene::Entity* entity_quad1;
        // Ra::Engine::Scene::Entity* entity_quad2;
        Ra::Engine::Scene::Entity* e;
    
    protected:

};

#endif // CROSSHAIR_HPP