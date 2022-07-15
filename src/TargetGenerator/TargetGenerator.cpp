#include "TargetGenerator.hpp"

#include <time.h>
#include <stdlib.h>

TargetGenerator::TargetGenerator(Ra::Engine::Scene::EntityManager m_entity, std::vector<Ra::Core::Vector3> spots)
{
    srand(time(NULL));
    auto sphere = Ra::Core::Geometry::makeParametricSphere(0.5_ra);
    sphere_entity = m_entity.createEntity( "Green sphere" );
    this->spots = spots;
    
}

TargetGenerator::~TargetGenerator(){}

void TargetGenerator::make_target(unsigned int index)
{
    Ra::Core::Transform transform_t( Ra::Core::Transform::Identity() );
    Ra::Core::Vector3 vec = spots[index];
    transform_t.translation() = vec;
    sphere_entity->setTransform(transform_t);
}

void TargetGenerator::next_target(){
    unsigned int nb_spot = spots.size();
    unsigned int random_index = rand() % nb_spot;
    make_target(random_index);
}



