#include <Engine/Scene/Component.hpp>
#include <Engine/Scene/GeometryComponent.hpp>
#include <Engine/Scene/CameraComponent.hpp>

#include "Crosshair.hpp"

Crosshair::Crosshair(Ra::Engine::Scene::System* geometrySystem, Ra::Engine::Scene::EntityManager* entityManager)
{

    
   
    
    // auto q1 = Ra::Core::Geometry::makeZNormalQuad(Ra::Core::Vector2(0.001_ra/2_ra, 0.005_ra/2_ra), Ra::Core::Utils::Color::Red());
    // this->entity_quad1 = entityManager->createEntity( "Quad 1" );
    // this->entity_quad1->setTransform(transform_t);
    // auto c1 = new Ra::Engine::Scene::TriangleMeshComponent( "Quad 1 Mesh", this->entity_quad1, std::move( q1 ), nullptr );
    // geometrySystem->addComponent(this->entity_quad1, c1);

    // auto q2 = Ra::Core::Geometry::makeZNormalQuad(Ra::Core::Vector2(0.005_ra/2_ra, 0.001_ra/2_ra), Ra::Core::Utils::Color::Red());
    // this->entity_quad2 = entityManager->createEntity( "Quad 2" );
    // this->entity_quad2->setTransform(transform_t);
    // auto c2 = new Ra::Engine::Scene::TriangleMeshComponent( "Quad 2 Mesh", this->entity_quad2, std::move( q2 ), nullptr );
    // geometrySystem->addComponent(this->entity_quad2, c2);

    auto sphere = Ra::Core::Geometry::makeParametricSphere(0.0001_ra);
    sphere.addAttrib("in_color", Ra::Core::Vector4Array { sphere.vertices().size(), Ra::Core::Utils::Color::Black() } );
    this->e = entityManager->createEntity();
    auto c = new Ra::Engine::Scene::TriangleMeshComponent( this->e->getName()+" Mesh", this->e, std::move( sphere ), nullptr );
    geometrySystem->addComponent( this->e, c );




}


void Crosshair::update(Ra::Core::Transform transform)
{
    // this->entity_quad1->setTransform(transform);
    // this->entity_quad2->setTransform(transform);
    this->e->setTransform(transform);

}

Crosshair::~Crosshair() {}