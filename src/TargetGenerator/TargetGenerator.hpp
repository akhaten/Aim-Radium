#ifndef TARGET_GENERATOR_HPP
#define TARGET_GENERATOR_HPP

#include <Core/Types.hpp>
#include <Engine/Scene/EntityManager.hpp>
#include <Engine/Scene/GeometryComponent.hpp>

#include <vector>

class TargetGenerator
{

    
    public:
        TargetGenerator(Ra::Engine::Scene::EntityManager m_entity, std::vector<Ra::Core::Vector3> spots);
        ~TargetGenerator();
        void next_target();
        

    protected:

    private:
        
        Ra::Core::Vector3 coord;
        Ra::Engine::Scene::Entity *sphere_entity;
        std::vector<Ra::Core::Vector3> spots;
        void make_target(unsigned int index);

        

};


#endif // TARGET_GENERATOR_HPP