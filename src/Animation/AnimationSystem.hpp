#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP


#include <Core/Tasks/TaskQueue.hpp>
#include <Core/Tasks/Task.hpp>



// To terminate the demo after 4 seconds
#include <QTimer>


#include "Animation/Animation.hpp"


class AnimationSystem :
    public Ra::Engine::Scene::System
{
  public:
    virtual void generateTasks( Ra::Core::TaskQueue* q,
                                const Ra::Engine::FrameInfo& info ) override {
        
        for(int index = 0; index < m_components.size(); ++index){
            Animation* c = static_cast<Animation*>( m_components[index].second );
            q->registerTask( new Ra::Core::FunctionTask(
                std::bind( &Animation::update, c, info.m_animationTime ), "spin" ) );
        }
        
    }
};

#endif // ANIMATION_SYSTEM_HPP