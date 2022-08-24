#ifndef AIM_TRAINER_HPP
#define AIM_TRAINER_HPP

#include <Engine/Scene/EntityManager.hpp>

#include "Spot.hpp"

#include "Target.hpp"



// #include "TargetGenerator/TargetGenerator.hpp"

class AimTrainer
{

    public:
        AimTrainer(Ra::Engine::Scene::System* system, Ra::Engine::Scene::EntityManager* entity_manager, unsigned int nb_target=1);
        ~AimTrainer();
        void add_spot(Spot* spot);
        bool target_shooted(Ra::Core::Ray ray);
        void initialize();

    private:

        unsigned int nb_target;
        Scalar radius;
        std::vector<Target*> targets;
        std::vector<Spot*> spots;

        Ra::Engine::Scene::System* system;
        Ra::Engine::Scene::EntityManager* entity_manager;
        


};

#endif // AIM_TRAINER_HPP