

#include "Target.hpp"

Target::Target(Scalar radius) 
{

    this->radius = radius;

    this->spot = nullptr;
    this->entity = nullptr;
    this->animation = nullptr;

}

Target::~Target() {}

void Target::load(Ra::Engine::Scene::System* system, Ra::Engine::Scene::EntityManager* entity_manager)
{

    this->system = system;
    this->entity_manager = entity_manager;
    
    auto sphere = Ra::Core::Geometry::makeParametricSphere(this->radius);
    sphere.addAttrib("in_color", Ra::Core::Vector4Array { sphere.vertices().size(), Ra::Core::Utils::Color::Green() } );
                
    this->entity = this->entity_manager->createEntity();
    

    this->animation = new Animation(this->entity->getName()+" Mesh", this->entity, std::move(sphere));

    this->system->addComponent(this->entity, this->animation);

}


Spot* Target::get_spot()
{

    return this->spot;
}


void Target::set_spot(Spot* s)
{

    this->spot = s;
    

    Ra::Core::Transform transform_t( Ra::Core::Transform::Identity() );
    transform_t.translation() = this->spot->position;
    this->entity->setTransform(transform_t);

    this->animation->configure(this->spot->animation_datas);

}


Ra::Core::Vector3 Target::get_position()
{

    auto entity_postion = this->entity->getTransform().translation();
    auto animation_transformer = this->animation->transformer;
    auto translation = animation_transformer.translation();
    auto target_position = entity_postion+translation;
    return target_position;

}

bool Target::is_shooted(Ra::Core::Ray ray)
{

    auto target_position = this->get_position();
    Ra::Core::Vector3 proj = ray.projection(target_position);
    auto vec = proj-target_position;
    return vec.norm() <= this->radius;

}