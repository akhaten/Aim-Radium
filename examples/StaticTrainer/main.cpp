#include <iostream>


#include <QApplication>


// Radium includes
#include <Core/Math/DualQuaternion.hpp>

#include <Core/Geometry/Curve2D.hpp>
#include <Core/Geometry/PolyLine.hpp>

#include <Engine/Data/Mesh.hpp>
#include <Engine/Data/RawShaderMaterial.hpp>
#include <Engine/Data/ShaderConfiguration.hpp>
#include <Engine/Data/ShaderProgramManager.hpp>



#include <Engine/Scene/Component.hpp>
#include <Engine/Scene/CameraComponent.hpp>
#include <Engine/Scene/EntityManager.hpp>
#include <Engine/Scene/GeometryComponent.hpp>
#include <Engine/Scene/GeometrySystem.hpp>
#include <Engine/Scene/Light.hpp>
#include <Engine/Scene/SpotLight.hpp>
#include <Engine/Scene/PointLight.hpp>

#include <Gui/BaseApplication.hpp>
#include <Gui/RadiumWindow/SimpleWindowFactory.hpp>
#include <Gui/Viewer/Viewer.hpp>


// My FPS application

#include "AimRadium.hpp"
#include "ShooterFPS.hpp"
#include "AimTrainer.hpp"
#include "Crosshair.hpp"
#include "Map.hpp"
#include "Animation/AnimationSystem.hpp"
#include "Animation/AnimationDatas.hpp"
#include "Target.hpp"



int main( int argc, char* argv[] ) {

    //! [Creating the application]
    Ra::Gui::BaseApplication app( argc, argv );
    app.setOverrideCursor(Qt::BlankCursor);
    
    app.initialize(AimRadiumFactory{});

    //![Parameterize the Engine  time loop]
    app.m_engine->setEndTime( 20_ra ); // <-- 3 relates to the keyframes of the demo component.
    app.m_engine->setRealTime( false );
    app.m_engine->play( true );


    // //! [Create the demo animation system]
    AnimationSystem* animation_systeme = new AnimationSystem;
    app.m_engine->registerSystem( "Animation Target System", animation_systeme );
    auto geometry_system = app.m_engine->getSystem( "GeometrySystem" );
    auto entity_manager = app.m_engine->getEntityManager();
    auto light_system = app.m_engine->getSystem( "LightSystem" );
    auto appWindow = dynamic_cast<AimRadium*>( app.m_mainWindow.get() );
    auto viewer = appWindow->getViewer();

    // Make light

    auto pos_light = Ra::Core::Vector3(-10_ra, 5_ra, -10_ra);
    auto x_acc = Ra::Core::Vector3(20_ra, 0_ra, 0_ra);
    auto z_acc = Ra::Core::Vector3(0_ra, 0_ra, 20_ra);

    for(int x = 0; x < 2; ++x){
        for(int z = 0; z < 2; ++z){
            auto token = pos_light + x*x_acc + z*z_acc;
            auto light_entity_left = entity_manager->createEntity();
            auto light_left = new Ra::Engine::Scene::PointLight(light_entity_left);
            light_left->setColor(Ra::Core::Utils::Color::White());
            light_left->setPosition(token);
            viewer->getRenderer()->addLight(light_left);
        }
    }

    // auto light_entity_left = entity_manager->createEntity();
    // auto light_left = new Ra::Engine::Scene::PointLight(light_entity_left);
    // light_left->setColor(Ra::Core::Utils::Color::White());
    // light_left->setPosition(Ra::Core::Vector3(-10_ra, 5_ra, 0_ra));
    // viewer->getRenderer()->addLight(light_left);

    // auto light_entity_right = entity_manager->createEntity();
    // auto light_right = new Ra::Engine::Scene::PointLight(light_entity_right);
    // light_right->setColor(Ra::Core::Utils::Color::White());
    // light_right->setPosition(Ra::Core::Vector3(10_ra, 5_ra, 0_ra));
    // viewer->getRenderer()->addLight(light_right);

    // Make Aim Trainer

    auto aim_trainer = AimTrainer(animation_systeme, entity_manager, 3);

    auto anime_datas = new AnimationDatas(5_ra, 0_ra, 1, Ra::Core::Vector3(1_ra, 0_ra, 0_ra));

    
    auto position = Ra::Core::Vector3(-3_ra, 1_ra, -5_ra);
    auto up = Ra::Core::Vector3(0_ra, 1_ra, 0_ra);
    auto right = Ra::Core::Vector3(1_ra, 0_ra, 0_ra);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            auto token = position + i*up + j*right;
            auto spot = new Spot(token, anime_datas);
            aim_trainer.add_spot(spot);
        }
    }

    aim_trainer.initialize();

    // Make Shooter FPS
    
    auto shooter = new Ra::Gui::ShooterFPS( *( viewer->getCameraManipulator() ) );
    viewer->setCameraManipulator( shooter );
    shooter->setAimTrainer(aim_trainer);
    
    // Make crosshair
    auto crosshair = Crosshair(geometry_system, entity_manager);
    shooter->setCrosshair(crosshair);

    // Make basic map
    auto map = Map(geometry_system, entity_manager);

    // Prepare window
    appWindow->prepareDisplay();
    
    return app.exec();


}