#include <iostream>


#include <QApplication>


// Radium includes
#include <Core/Math/DualQuaternion.hpp>
#include <Core/Geometry/Curve2D.hpp>
#include <Core/Geometry/PolyLine.hpp>

#include <Gui/BaseApplication.hpp>
#include <Gui/RadiumWindow/SimpleWindowFactory.hpp>
#include <Gui/Viewer/Viewer.hpp>

#include <Engine/Data/RawShaderMaterial.hpp>
#include <Engine/Data/ShaderConfiguration.hpp>
#include <Engine/Data/ShaderProgramManager.hpp>

#include <Engine/Scene/Component.hpp>
#include <Engine/Scene/CameraComponent.hpp>
#include <Engine/Scene/EntityManager.hpp>
#include <Engine/Scene/GeometryComponent.hpp>
#include <Engine/Scene/GeometrySystem.hpp>



#include <Gui/Viewer/FlightCameraManipulator.hpp>

// My FPS application
#include "AimRadium.hpp"
#include "FPS/ShooterFPS.hpp"


const std::string vertex_shader {
    "#version 450 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 0, 0);\n"
    "}\n"
};

const std::string fragment_shader {
    "#version 450 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "}\n"
};



// bool eventFilter(QObject * obj, QEvent * event)
// {

//     if ( event->type() == QEvent::KeyPress ) {

//         pressedKeys += ((QKeyEvent*)event)->key();

//         if ( pressedKeys.contains(Qt::Key_D) && pressedKeys.contains(Qt::Key_W) )
//         {
//             // D and W are pressed
//         }

//     }
//     else if ( event->type() == QEvent::KeyRelease )
//     {

//         pressedKeys -= ((QKeyEvent*)event)->key();
//     }


//     return false;
// }
int main( int argc, char* argv[] ) {

    //! [Creating the application]
    Ra::Gui::BaseApplication app( argc, argv );
    app.setOverrideCursor(Qt::BlankCursor);
    // app.initialize( Ra::Gui::SimpleWindowFactory {} );
    app.initialize(AimRadiumFactory{});

    // auto crosshair_config = Ra::Engine::Data::ShaderConfiguration("Crosshair", vertex_shader, fragment_shader);
    // auto shader_program = Ra::Engine::Data::ShaderProgram(crosshair_config);
    // auto m_shaderProgram = app.m_engine->getShaderProgramManager();
    // m_shaderProgram->addShaderProgram(crosshair_config);


    
    auto sphere = Ra::Core::Geometry::makeParametricSphere(0.5_ra);
    
    sphere.addAttrib("in_color", Ra::Core::Vector4Array { sphere.vertices().size(), Ra::Core::Utils::Color::Green() } );
    auto e = app.m_engine->getEntityManager()->createEntity( "Green sphere" );

    Ra::Core::Transform transform_t( Ra::Core::Transform::Identity() );
    transform_t.translation() = Ra::Core::Vector3(0_ra, 0.5_ra, -5_ra);
    e->setTransform(transform_t);

    auto c = new Ra::Engine::Scene::TriangleMeshComponent( "Sphere Mesh", e, std::move( sphere ), nullptr );
    auto geometrySystem = app.m_engine->getSystem( "GeometrySystem" );
    geometrySystem->addComponent( e, c );
    


    app.m_mainWindow->prepareDisplay();
 
    auto appWindow = dynamic_cast<AimRadium*>( app.m_mainWindow.get() );
    // appWindow->installEventFilter();
    auto viewer = appWindow->getViewer();;
    // auto shooter = new Ra::Gui::FlightCameraManipulator( *( viewer->getCameraManipulator() ) );
    auto shooter = new Ra::Gui::ShooterFPS( *( viewer->getCameraManipulator() ) );
    viewer->setCameraManipulator( shooter );
    

    // auto m_entity = app.m_engine->getEntityManager();
    // m_entity->removeEntity(e);
    
    return app.exec();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // Include Radium base application and its simple Gui
// #include <Gui/BaseApplication.hpp>
// #include <Gui/RadiumWindow/SimpleWindowFactory.hpp>

// // include the core geometry/appearance interface
// #include <Core/Asset/BlinnPhongMaterialData.hpp>
// #include <Core/Geometry/MeshPrimitives.hpp>

// // include the Engine/entity/component/system/animation interface
// #include <Engine/FrameInfo.hpp>
// #include <Engine/Scene/EntityManager.hpp>
// #include <Engine/Scene/GeometryComponent.hpp>
// #include <Engine/Scene/System.hpp>

// // include the keyframe animation interface
// #include <Core/Animation/KeyFramedValueController.hpp>
// #include <Core/Animation/KeyFramedValueInterpolators.hpp>
// #include <Core/Tasks/Task.hpp>

// // include the render object interface to keyframe the material
// #include <Engine/Rendering/RenderObjectManager.hpp>

// // To terminate the demo after 4 seconds
// #include <QTimer>

// #include "FPS/ShooterFPS.hpp"
// #include <Gui/Viewer/Viewer.hpp>

// //! [Define a key-framed geometry component]
// /**
//  * KeyFramedGeometryComponent : example on extending a geometry component to animate its
//  * material color.
//  *
//  *   When creating a KeyFramedGeometryComponent with a Core::TriangleMesh, this associate an
//  *   animated Blinn-Phong material to the geometry and update both the transformation and the
//  *   diffuse color at each time step.
//  *
//  *   @note This is only for demo purpose. A more simpler approach could be :
//  *      - Create and add a geometry component to the Engine geometry system (like in HelloRadium)
//  *      - Get the renderobject associated with this component and create an animation component
//  *              that associates the RenderObject with an animation controller
//  *      - Add the animation component to the animation system
//  *
//  */
// class KeyFramedGeometryComponent : public Ra::Engine::Scene::TriangleMeshComponent
// {
//   public:
//     /*!
//      * Constructor from an existing core mesh
//      * \warning Moves the mesh and takes its ownership
//      */
//     inline KeyFramedGeometryComponent( const std::string& name,
//                                        Ra::Engine::Scene::Entity* entity,
//                                        Ra::Core::Geometry::TriangleMesh&& mesh ) :
//         Ra::Engine::Scene::TriangleMeshComponent( name,
//                                                   entity,
//                                                   std::move( mesh ),
//                                                   new Ra::Core::Asset::BlinnPhongMaterialData {} ),
//         m_transform( 0_ra, Ra::Core::Transform::Identity() ) {

//         //! [Creating the transform KeyFrames]
//         //Ra::Core::Transform T = Ra::Core::Transform::Identity();

//         Ra::Core::Transform transform_t( Ra::Core::Transform::Identity() );
//         transform_t.translation() = Ra::Core::Vector3(0.5_ra, 0_ra, 0_ra);

//         unsigned int counter = 0;
//         Scalar t = 1_ra;

//         for(unsigned int index = 1; index <= 20_ra; index+=1){

//             if (index%10 == 0){
//                 counter += 1;
//             }

//             m_transform.insertKeyFrame(t, transform_t);
//             t += 1_ra;
            
//             if (counter % 2 == 0) {
//                 transform_t.translate(Ra::Core::Vector3(0.5_ra, 0_ra, 0_ra));
//             }else{
//                 transform_t.translate(Ra::Core::Vector3(-0.5_ra, 0_ra, 0_ra));
//             }
            
//         }

        
//         // transform_t.translate(Ra::Core::Vector3(0.1_ra, 0_ra, 0_ra));
//         // m_transform.insertKeyFrame(2_ra, transform_t);
//         // transform_t.translate(Ra::Core::Vector3(0.1_ra, 0_ra, 0_ra));
//         // m_transform.insertKeyFrame(3_ra, transform_t);
//         // m_transform.removeKeyFrame(0_ra);
    
        

//         // //! [Creating the transform KeyFrames]
//         // //! [Creating the color KeyFrames]
//         auto colors = new Ra::Core::Animation::KeyFramedValue<Ra::Core::Utils::Color>(
//             0_ra, Ra::Core::Utils::Color::Green() );
//         // colors->insertKeyFrame( 1_ra, Ra::Core::Utils::Color::Red() );
//         // colors->insertKeyFrame( 2_ra, Ra::Core::Utils::Color::Blue() );
//         // colors->insertKeyFrame( 3_ra, Ra::Core::Utils::Color::Green() );
//         // //! [Attach the color KeyFrames to a controller of the Render object material]
//         m_colorController.m_value = colors;
//         m_ro                      = getRoMgr()->getRenderObject( m_roIndex );
//         auto material =
//             dynamic_cast<Ra::Engine::Data::BlinnPhongMaterial*>( m_ro->getMaterial().get() );
//         m_colorController.m_updater = [colors, material]( const Scalar& t ) {
//             auto C =
//                 colors->at( t, Ra::Core::Animation::linearInterpolate<Ra::Core::Utils::Color> );
//             material->m_kd = C;
//             material->needUpdate();
//         };
//         //! [Attach the color KeyFrames to a controller]
//         //! [Creating the color KeyFrames]
//     }
//     /// This function uses the keyframes to update the cube to time \p t.
//     void update( Scalar t ) {
//         //! [Fetch transform from KeyFramedValue]

//         // transform_t.translate(Ra::Core::Vector3(0.1_ra, 0_ra, 0_ra));
//         // m_transform.insertKeyFrame(t+1_ra, transform_t);

//         auto T = m_transform.at( t, Ra::Core::Animation::linearInterpolate<Ra::Core::Transform> );
//         //! [Fetch transform from KeyFramedValue]
//         m_ro->setLocalTransform( T );

//         //! [Update color from KeyFramedValue]
//         m_colorController.updateKeyFrame( t );
//         //! [Update color from KeyFramedValue]
//     }

//     /// The render object to animate
//     std::shared_ptr<Ra::Engine::Rendering::RenderObject> m_ro;

//     /// The Keyframes for the render object's tranform.
//     Ra::Core::Animation::KeyFramedValue<Ra::Core::Transform> m_transform;

//     /// The Keyframes for the render object's color.
//     Ra::Core::Animation::KeyFramedValueController m_colorController;

//     // Ra::Core::Transform transform_t;
// };
// //! [Define a key-framed geometry component]

// //! [Define a simple animation system]
// /// This system will be added to the engine. Every frame it will
// /// add a task to be executed, calling the update function of the component.
// /// \note This system makes time loop around.
// class SimpleAnimationSystem : public Ra::Engine::Scene::System
// {
//   public:
//     virtual void generateTasks( Ra::Core::TaskQueue* q,
//                                 const Ra::Engine::FrameInfo& info ) override {
//         KeyFramedGeometryComponent* c =
//             static_cast<KeyFramedGeometryComponent*>( m_components[0].second );

//         // Create a new task which wil call c->spin() when executed.
//         q->registerTask( new Ra::Core::FunctionTask(
//             std::bind( &KeyFramedGeometryComponent::update, c, info.m_animationTime ), "spin" ) );
//     }
// };

// int main( int argc, char* argv[] ) {

//     //! [Creating the application]
//     Ra::Gui::BaseApplication app( argc, argv );
//     app.setOverrideCursor(Qt::BlankCursor);
//     app.initialize( Ra::Gui::SimpleWindowFactory {} );

//     //![Parameterize the Engine  time loop]
//     app.m_engine->setEndTime( 20_ra ); // <-- 3 relates to the keyframes of the demo component.
//     app.m_engine->setRealTime( true );
//     app.m_engine->play( true );

//     //! [Create the demo animation system]
//     SimpleAnimationSystem* sys = new SimpleAnimationSystem;
//     app.m_engine->registerSystem( "Minimal system", sys );

//     //! [Create the demo animated component]
//     //! [Creating the cube]
//     auto sphere = Ra::Core::Geometry::makeParametricSphere(0.5_ra);
//     //! [Creating the cube]

//     //! [Create the engine entity for the cube]
//     auto e = app.m_engine->getEntityManager()->createEntity( "Green sphere" );
//     //! [Create the engine entity for the cube]
//     Ra::Core::Transform transform_t( Ra::Core::Transform::Identity() );
//     transform_t.translation() = Ra::Core::Vector3(-5_ra, 0.5_ra, -5_ra);
//     e->setTransform(transform_t);

    
//     //! [Create a KeyFramedGeometryComponent component with the cube]
//     auto c = new KeyFramedGeometryComponent( "Sphere Mesh", e, std::move( sphere ) );

//     //! [Create a KeyFramedGeometryComponent component with the cube]
//     //! [Create the demo animated component]

//     //! [add the component to the animation system]
//     sys->addComponent( e, c );
//     //! [add the component to the animation system]

//     //! [Tell the window that something is to be displayed]
//     app.m_mainWindow->prepareDisplay();
//     //! [Tell the window that something is to be displayed]

//     auto viewer = app.m_mainWindow->getViewer();
//     viewer->setCameraManipulator( new Ra::Gui::ShooterFPS( *( viewer->getCameraManipulator() ) ) );

//     // terminate the app after 6 second (approximatively). Camera can be moved using mouse moves.
//     // auto close_timer = new QTimer( &app );
//     // close_timer->setInterval( 6000 );
//     // QObject::connect( close_timer, &QTimer::timeout, [&app]() { app.appNeedsToQuit(); } );
//     // close_timer->start();

//     return app.exec();
// }




