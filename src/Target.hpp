#ifndef TARGET_HPP
#define TARGET_HPP

#include <Core/Types.hpp>

#include <Engine/RadiumEngine.hpp>
#include <Engine/Scene/EntityManager.hpp>
#include <Engine/Scene/GeometrySystem.hpp>

#include "Animation/Animation.hpp"
#include "Spot.hpp"

class Target
{

    public:

        Target(Scalar radius);
        ~Target();

        bool is_shooted(Ra::Core::Ray ray);
        Ra::Core::Vector3 get_position();
        void set_spot(Spot* s);
        Spot* get_spot();


        void load(Ra::Engine::Scene::System* system, Ra::Engine::Scene::EntityManager* entity_manager);
        void configure_animation(Scalar nb_frame, Scalar speed, int direction, Ra::Core::Vector3 vector);
        
        Ra::Engine::Scene::Entity* entity;
    
    private:

        Spot* spot;
        Scalar radius;

        Ra::Engine::Scene::System* system;
        Ra::Engine::Scene::EntityManager* entity_manager;
        
        Animation* animation;



    

};

#endif // TARGET_HPP