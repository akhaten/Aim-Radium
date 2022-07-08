#include <iostream>

//#include "Gui/MainWindow.hpp"
#include <QApplication>


// Radium includes
#include <Core/Math/DualQuaternion.hpp>

#include <Gui/BaseApplication.hpp>
#include <Gui/RadiumWindow/SimpleWindowFactory.hpp>
#include <Gui/Viewer/Viewer.hpp>

// My FPS application
#include "FPS/CameraManipulatorFPS.hpp"


int main( int argc, char* argv[] ) {

    //! [Creating the application]
    Ra::Gui::BaseApplication app( argc, argv );
    app.setOverrideCursor(Qt::BlankCursor);
    app.initialize( Ra::Gui::SimpleWindowFactory {} );
    
    app.m_mainWindow->prepareDisplay();
 
    auto viewer = app.m_mainWindow->getViewer();
    viewer->setCameraManipulator( new Ra::Gui::CameraManipulatorFPS( *( viewer->getCameraManipulator() ) ) );

    return app.exec();
}


// // include the Engine/entity/component interface
// #include <Core/Geometry/MeshPrimitives.hpp>
// #include <Engine/Scene/EntityManager.hpp>
// #include <Engine/Scene/GeometryComponent.hpp>
// #include <Engine/Scene/GeometrySystem.hpp>
// // Include Radium base application and its simple Gui
// #include <Gui/BaseApplication.hpp>
// #include <Gui/RadiumWindow/SimpleWindowFactory.hpp>
// #include <Gui/Viewer/TrackballCameraManipulator.hpp>
// #include <Gui/Viewer/Viewer.hpp>
// #include <Gui/Viewer/FlightCameraManipulator.hpp>
// #include "FPS/CameraManipulatorFPS.hpp"

// #include <QTimer>




