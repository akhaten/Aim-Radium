#include <Engine/Scene/GeometryComponent.hpp>
#include <Engine/Scene/GeometrySystem.hpp>

#include <random>

#include "AimTrainer.hpp"

AimTrainer::AimTrainer(Ra::Engine::Scene::System* system, Ra::Engine::Scene::EntityManager* entity_manager, unsigned int nb_target)
{
    this->system = system;
    this->entity_manager = entity_manager;
    this->nb_target = nb_target;

    for(int index = 0; index < this->nb_target; ++index){
        this->targets.push_back(new Target(0.2_ra));
        this->targets[index]->load(this->system, this->entity_manager);
    }
}

AimTrainer::~AimTrainer() {}



void AimTrainer::add_spot(Spot* spot)
{
    this->spots.push_back(spot);
}




bool AimTrainer::target_shooted(Ra::Core::Ray ray)
{

    bool shooted = false;
    
    unsigned int index = 0;
    
    for(; (index < this->targets.size()) && !shooted; index += 1){
        shooted = this->targets[index]->is_shooted(ray);
    }
        

    // printf("Post For : index = %i, shooted = %i\n", index, shooted);
    std::random_device random_device;
    std::mt19937 engine{random_device()};
    
    if(shooted)
    {

        auto target_shooted = this->targets[index-1];
        auto spot = target_shooted->get_spot();
        
        std::uniform_int_distribution<int> dist(0, this->spots.size() - 1);
        
        int random_index = dist(engine);

        auto new_spot = this->spots[random_index];
        
        std::vector<Spot*>::iterator rand_spot_it = this->spots.begin() + random_index;
        this->spots.erase(rand_spot_it);

        target_shooted->set_spot(new_spot);
        this->spots.push_back(spot);
        
    }

    return shooted;

}


void AimTrainer::initialize()
{
        
    std::random_device random_device;
    std::mt19937 engine{random_device()};


    for(unsigned int index = 0; index < this->targets.size(); ++index)
    {

        std::uniform_int_distribution<int> dist(0, this->spots.size() - 1);
        int random_index = dist(engine);
      
        std::vector<Spot*>::iterator rand_spot_it = this->spots.begin() + random_index;

        auto spot = this->spots[random_index];
        this->spots.erase(rand_spot_it);
        auto target = this->targets[index];
        target->set_spot(spot);

    }
    
}