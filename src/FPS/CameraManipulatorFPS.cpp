#include "CameraManipulatorFPS.hpp"

#include <Gui/Utils/KeyMappingManager.hpp>
#include <Core/Math/LinearAlgebra.hpp>
#include <Core/Math/Math.hpp>
#include <glm/glm.hpp>



namespace Ra {
namespace Gui {

using KeyMappingCameraManipulatorFPS = Ra::Gui::KeyMappingManageable<CameraManipulatorFPS>;
  
//#define KMA_VALUE( XX ) static KeyMappingManager::KeyMappingAction XX;
//KeyMappingCameraManipulatorFPS
//#undef KMA_VALUE

CameraManipulatorFPS::CameraManipulatorFPS():
	CameraManipulator()
{
	// m_camera->setPosition(Ra::Core::Vector3(0_ra, 2_ra, 0_ra));
	vector_up = Ra::Core::Vector3( 0_ra, 1_ra, 0_ra );
	this->cursor.setPos(m_camera->getWidth() / 2, m_camera->getWidth() / 2);
	theta = 0.f;

}

CameraManipulatorFPS::CameraManipulatorFPS(const Ra::Gui::CameraManipulator& other):	
	Ra::Gui::CameraManipulator(other)
{
	vector_up = Ra::Core::Vector3( 0_ra, 1_ra, 0_ra );;
	this->cursor.setPos(m_camera->getWidth() / 2, m_camera->getWidth() / 2);
	theta = 0.f;
}

CameraManipulatorFPS::~CameraManipulatorFPS() {}

/**
 * Allow configure action
 */
void CameraManipulatorFPS::configureKeyMapping_impl()
{
	
	// Create key mapping manager
	//Gui::KeyMappingManager* key_mapping_manager = Gui::KeyMappingManager::getInstance();
	KeyMappingCameraManipulatorFPS::setContext(Gui::KeyMappingManager::getInstance()->getContext( "FPSManipulatorContext" ));
	
	if ( KeyMappingCameraManipulatorFPS::getContext().isInvalid() ) {
        LOG( Ra::Core::Utils::logWARNING ) << "KeyMappingCameraManipulatorFPS not defined (maybe the "
                                               "configuration file do not contains it). Adding "
                                               "default configuration for KeyMappingCameraManipulatorFPS.";

		Gui::KeyMappingManager* key_mapping_manager = Gui::KeyMappingManager::getInstance();

		// Add actions

		key_mapping_manager->addAction(
			/* context = */ 			"FPSManipulatorContext",
			/* keyString = */ 			"Key_Z",
			/* modifiersString = */ 	"NoModifier",
			/* buttonString = */ 		"",
			/* wheelString = */ 		"",
			/* actionString = */ 		"TO_FORDWARD",
			/* saveToConfigFile = */ 	false
		);

		key_mapping_manager->addAction(    
			/* context = */             "FPSManipulatorContext",       
			/* keyString = */           "Key_S",           
			/* modifiersString = */     "NoModifier",           
			/* buttonString = */        "",                    
			/* wheelString = */         "",                    
			/* actionString = */        "TO_BACKWARD",      
			/* saveToConfigFile = */    false               
		);

		key_mapping_manager->addAction(    
			/* context = */             "FPSManipulatorContext",       
			/* keyString = */           "Key_D",           
			/* modifiersString = */     "NoModifier",           
			/* buttonString = */        "",                    
			/* wheelString = */         "",                    
			/* actionString = */        "TO_RIGHT",      
			/* saveToConfigFile = */    false               
		);
		
		key_mapping_manager->addAction(    
			/* context = */             "FPSManipulatorContext",       
			/* keyString = */           "Key_Q",           
			/* modifiersString = */     "NoModifier",           
			/* buttonString = */        "",                    
			/* wheelString = */         "",                    
			/* actionString = */        "TO_LEFT",      
			/* saveToConfigFile = */    false               
		);

		key_mapping_manager->addAction(    
			/* context = */             "FPSManipulatorContext",       
			/* keyString = */           "Key_SPACE",           
			/* modifiersString = */     "NoModifier",           
			/* buttonString = */        "",                    
			/* wheelString = */         "",                    
			/* actionString = */        "JUMP",      
			/* saveToConfigFile = */    false               
		);

		KeyMappingCameraManipulatorFPS::setContext(key_mapping_manager->getContext("FPSManipulatorContext"));
						
  
        //  Gui::KeyMappingManager::getInstance()->addAction(
        //      "FPSManipulatorContext", "", "", "LeftButton", "", "FLIGHTMODECAMERA_ROTATE" );
        //  Gui::KeyMappingManager::getInstance()->addAction( "FlightManipulatorContext",
        //                                                    "",
        //                                                    "ShiftModifier",
        //                                                    "LeftButton",
        //                                                    "",
        //                                                    "FLIGHTMODECAMERA_PAN" );
        //  Gui::KeyMappingManager::getInstance()->addAction( "FlightManipulatorContext",
        //                                                    "",
        //                                                    "ControlModifier",
        //                                                    "LeftButton",
        //                                                    "",
        //                                                    "FLIGHTMODECAMERA_ZOOM" );
        //  Gui::KeyMappingManager::getInstance()->addAction(
        //      "FlightManipulatorContext", "Key_A", "", "", "", "FLIGHTMODECAMERA_ROTATE_AROUND" );

        //  FlightCameraKeyMapping::setContext(
        //      Gui::KeyMappingManager::getInstance()->getContext( "FlightManipulatorContext" ) );
     }


	// // Add actions

	// key_mapping_manager->addAction(
	// 	/* context = */ 			"FPSCamera",
	// 	/* keyString = */ 			"Key_Z",
	// 	/* modifiersString = */ 	"NoModifier",
	// 	/* buttonString = */ 		"",
	// 	/* wheelString = */ 		"",
	// 	/* actionString = */ 		"TO_FORDWARD",
	// 	/* saveToConfigFile = */ 	false
	// );

	// key_mapping_manager->addAction(    
    //     /* context = */             "FPSCamera",       
    //     /* keyString = */           "Key_S",           
    //     /* modifiersString = */     "NoModifier",           
    //     /* buttonString = */        "",                    
    //     /* wheelString = */         "",                    
    //     /* actionString = */        "TO_BACKWARD",      
    //     /* saveToConfigFile = */    false               
    // );

	// key_mapping_manager->addAction(    
    //     /* context = */             "FPSCamera",       
    //     /* keyString = */           "Key_D",           
    //     /* modifiersString = */     "NoModifier",           
    //     /* buttonString = */        "",                    
    //     /* wheelString = */         "",                    
    //     /* actionString = */        "TO_RIGHT",      
    //     /* saveToConfigFile = */    false               
    // );
	
	// key_mapping_manager->addAction(    
    //     /* context = */             "FPSCamera",       
    //     /* keyString = */           "Key_Q",           
    //     /* modifiersString = */     "NoModifier",           
    //     /* buttonString = */        "",                    
    //     /* wheelString = */         "",                    
    //     /* actionString = */        "TO_LEFT",      
    //     /* saveToConfigFile = */    false               
    // );

	// key_mapping_manager->addAction(    
    //     /* context = */             "FPSCamera",       
    //     /* keyString = */           "Key_SPACE",           
    //     /* modifiersString = */     "NoModifier",           
    //     /* buttonString = */        "",                    
    //     /* wheelString = */         "",                    
    //     /* actionString = */        "JUMP",      
    //     /* saveToConfigFile = */    false               
    // );

	
	// KeyMapping::setContext(key_mapping_manager->getContext("FPSCamera"));
	// // KeyMapping::setContext(KeyMappingManager::getInstance()->getContext("FPSCamera"));
  
	// if(KeyMapping::getContext().isInvalid())
	// {
  	// 	LOG( Ra::Core::Utils::logINFO ) << "CameraContext not defined (maybe the configuration file do not contains it)";
  	// 	LOG( Ra::Core::Utils::logERROR ) << "CameraContext all keymapping invalid !";
  	// 	return;
	// }
 
	//#define KMA_VALUE( XX ) XX = key_mapping_manager->getActionIndex( KeyMapping::getContext(), #XX );
  	//KeyMappingCameraManipulatorFPS
 	//#undef KMA_VALUE
	Gui::KeyMappingManager* key_mapping_manager = Gui::KeyMappingManager::getInstance();
	TO_FORWARD = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "TO_FORWARD");
	TO_BACKWARD = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "TO_BACKWARD");
	TO_LEFT = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "TO_LEFT");
	TO_RIGHT = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "TO_RIGHT");
	JUMP = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "JUMP");
	ROTATE = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "ROTATE");

}

KeyMappingManager::Context CameraManipulatorFPS::mappingContext()
{
	return KeyMappingCameraManipulatorFPS::getContext();
}

bool CameraManipulatorFPS::handleMousePressEvent(
	QMouseEvent *event,
	const Qt::MouseButtons &buttons,
	const Qt::KeyboardModifiers &modifiers,
	int key)
{
	// SHOOT !?
	// Core::Vector3 position_shoot = m_camera->getPosition();
	// Core::Vector3 direction_shoot = m_camera->getDirection();
	// Compute intersection between straight and and object of scene.

	m_currentAction = KeyMappingManager::getInstance()->getAction(
		KeyMapping::getContext(), buttons, modifiers, false);

	return m_currentAction.isValid();
	
}

bool CameraManipulatorFPS::handleMouseReleaseEvent(QMouseEvent *event)
{

	m_currentAction = KeyMappingManager::KeyMappingAction::Invalid();
    return true;

}


bool CameraManipulatorFPS::handleMouseMoveEvent(    
	QMouseEvent *event,     
    const Qt::MouseButtons &buttons,     
    const Qt::KeyboardModifiers &modifiers,     
    int key)
{

	Scalar offset_x = cursor.pos().x() - (m_camera->getWidth() / 2);
	Scalar offset_y = cursor.pos().y() - (m_camera->getHeight() / 2);
	
	Scalar dx = offset_x / m_camera->getWidth();
    Scalar dy = offset_y / m_camera->getHeight();

	
    m_quickCameraModifier = 5.0_ra;

	Scalar dphi   = dx * m_cameraSensitivity * m_quickCameraModifier;
    Scalar dtheta = -dy * m_cameraSensitivity * m_quickCameraModifier;
	

	if (Ra::Core::Math::PiDiv2 <= theta+dtheta){
		dtheta = Ra::Core::Math::PiDiv2 - theta;
		theta = Ra::Core::Math::PiDiv2;
	}else if (theta+dtheta <= -Ra::Core::Math::PiDiv2){
		dtheta = Ra::Core::Math::PiDiv2 + theta;
		theta = -Ra::Core::Math::PiDiv2;
	}else{
		theta += dtheta;
	}

  
    Scalar d = ( m_target - m_camera->getPosition() ).norm();


	Core::Transform R1( Core::Transform::Identity() );
	R1 = Core::AngleAxis( -dphi, /*m_camera->getUpVector().normalized()*/ vector_up );

	Core::Transform R2( Core::Transform::Identity() );
	R2 = Core::AngleAxis( -dtheta, -m_camera->getRightVector().normalized() );

	
	m_target = m_camera->getPosition() + d * m_camera->getDirection();

	m_camera->applyTransform(R1 * R2);
    


	this->cursor.setPos(QPoint(m_camera->getWidth() / 2, m_camera->getHeight() / 2));

  
	return m_currentAction.isValid();

}


bool CameraManipulatorFPS::handleWheelEvent(
	QWheelEvent *event,                                                                     
    const Qt::MouseButtons &buttons, 
    const Qt::KeyboardModifiers &modifiers,                                                 
    int key)
{
                                                    
    m_currentAction = KeyMappingManager::KeyMappingAction::Invalid();
	return true;                                    
                                                       
}


bool CameraManipulatorFPS::handleKeyPressEvent( 
	QKeyEvent *event, 
	const KeyMappingManager::KeyMappingAction &action)
{

	printf("handleKeyPressEvent\n");
	if(action == TO_FORWARD)
	{
		printf("forward\n");
		Core::Vector3 point_proj = Ra::Core::Math::projectOnPlane(
            /* planePos = */ m_camera->getPosition(),
            /* planeNormal = */ m_camera->getUpVector(),
            /* point = */ m_camera->getPosition() + m_camera->getDirection());
        Core::Vector3 new_position = point_proj; 
        m_camera->setPosition(new_position);
	}

	if(action == TO_BACKWARD)
	{
		Core::Vector3 point_proj = Ra::Core::Math::projectOnPlane(
			/* planePos = */ m_camera->getPosition(),
			/* planeNormal = */ m_camera->getUpVector(),
			/* point = */ m_camera->getPosition() + m_camera->getDirection());
		Core::Vector3 vec_proj = point_proj - m_camera->getPosition();
		Core::Vector3 new_position = m_camera->getPosition() - vec_proj;
		m_camera->setPosition(new_position);
	}

	if(action == TO_RIGHT)
	{
		Core::Vector3 new_position = m_camera->getPosition() + m_camera->getRightVector();
		m_camera->setPosition(new_position);
	}

	if(action == TO_LEFT)
	{
		Core::Vector3 new_position = m_camera->getPosition() - m_camera->getRightVector();
		m_camera->setPosition(new_position);
	}

	if(action == JUMP)
	{
	}

	// this->updateCamera();

	return m_currentAction.isValid();

}


bool CameraManipulatorFPS::handleKeyReleaseEvent(
	QKeyEvent *event, 
	const KeyMappingManager::KeyMappingAction &action)
{
	printf("handleKeyReleaseEvent\n");
	m_currentAction = KeyMappingManager::KeyMappingAction::Invalid();
	return true;

}


void CameraManipulatorFPS::updateCamera()
{

	// m_referenceFrame = m_camera->getFrame();

}


void CameraManipulatorFPS::fitScene(const Core::Aabb &aabb){
  
} 


void CameraManipulatorFPS::setCameraPosition(const Core::Vector3 &position)
{

}


void CameraManipulatorFPS::setCameraTarget(const Core::Vector3 &target)
{

	//m_referenceFrame.translation() = target;

}


void CameraManipulatorFPS::resetCamera(){}

}
}

















