#include <Engine/Scene/Component.hpp>
#include <Engine/Scene/GeometryComponent.hpp>
#include <Engine/Scene/CameraComponent.hpp>

#include "Map.hpp"

Map::Map(Ra::Engine::Scene::System* geometrySystem, Ra::Engine::Scene::EntityManager* entityManager)
{

    auto ground = Ra::Core::Geometry::makeBox( { 10_ra, 0.05_ra, 10_ra } );
    ground.addAttrib("in_color", Ra::Core::Vector4Array { ground.vertices().size(), Ra::Core::Utils::Color::Grey() } );
    auto ground_entity = entityManager->createEntity( "Ground (box)" );

    Ra::Core::Transform ground_transform( Ra::Core::Transform::Identity() );
    ground_transform.translation() = Ra::Core::Vector3(0_ra, -0.1_ra/2, 0_ra);
    ground_entity->setTransform(ground_transform);

    auto ground_component = new Ra::Engine::Scene::TriangleMeshComponent( "Ground box Mesh", ground_entity, std::move( ground ), nullptr );
    geometrySystem->addComponent(ground_entity, ground_component);

    auto face = Ra::Core::Geometry::makeBox( { 10_ra, 10_ra, 0.1_ra/2 } );
    face.addAttrib("in_color", Ra::Core::Vector4Array { face.vertices().size(), Ra::Core::Utils::Color::Grey() } );
    auto face_entity = entityManager->createEntity( "Face (box)" );

    Ra::Core::Transform face_transform( Ra::Core::Transform::Identity() );
    face_transform.translation() = Ra::Core::Vector3(0_ra, 10_ra, -10_ra);
    face_entity->setTransform(face_transform);

    auto face_component = new Ra::Engine::Scene::TriangleMeshComponent( "Face box Mesh", face_entity, std::move( face ), nullptr );
    geometrySystem->addComponent(face_entity, face_component);


}

Map::~Map() {}
