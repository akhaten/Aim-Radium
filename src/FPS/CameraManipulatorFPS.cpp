#include "CameraManipulatorFPS.hpp"

#include <Gui/Utils/KeyMappingManager.hpp>
#include <Core/Math/LinearAlgebra.hpp>

namespace Ra {
namespace Gui {

using KeyMappingCameraManipulatorFPS = Ra::Gui::KeyMappingManageable<CameraManipulatorFPS>;
  
//#define KMA_VALUE( XX ) static KeyMappingManager::KeyMappingAction XX;
//KeyMappingCameraManipulatorFPS
//#undef KMA_VALUE

CameraManipulatorFPS::CameraManipulatorFPS():
	CameraManipulator()
{
	first_mouse = true;
	last_x = m_camera->getWidth() / 2;
	last_y = m_camera->getHeight() / 2;
	yaw = -90;
}

CameraManipulatorFPS::CameraManipulatorFPS(const Ra::Gui::CameraManipulator& other):	
	Ra::Gui::CameraManipulator(other)
{
	first_mouse = true;
	last_x = m_camera->getWidth() / 2;
 	last_y = m_camera->getHeight() / 2;
	yaw = -90;
}

CameraManipulatorFPS::~CameraManipulatorFPS() {}

/**
 * Allow configure action
 */
void CameraManipulatorFPS::configureKeyMapping_impl()
{
	
	// Create key mapping manager
	Gui::KeyMappingManager* key_mapping_manager = Gui::KeyMappingManager::getInstance();

	// Add actions
	
	key_mapping_manager->addAction(
		/* context = */ 			"FPSCamera",
		/* keyString = */ 			"Key_Z",
		/* modifiersString = */ 	"NoModifiers",
		/* buttonString = */ 		"-1",
		/* wheelString = */ 		"-1",
		/* actionString = */ 		"TO_FORDWARD",
		/* saveToConfigFile = */ 	false
	);

	key_mapping_manager->addAction(    
        /* context = */             "FPSCamera",       
        /* keyString = */           "Key_S",           
        /* modifiersString = */     "NoModifiers",           
        /* buttonString = */        "-1",                    
        /* wheelString = */         "-1",                    
        /* actionString = */        "TO_BACKWARD",      
        /* saveToConfigFile = */    false               
    );

	key_mapping_manager->addAction(    
        /* context = */             "FPSCamera",       
        /* keyString = */           "Key_D",           
        /* modifiersString = */     "NoModifiers",           
        /* buttonString = */        "-1",                    
        /* wheelString = */         "-1",                    
        /* actionString = */        "TO_RIGHT",      
        /* saveToConfigFile = */    false               
    );

	key_mapping_manager->addAction(    
        /* context = */             "FPSCamera",       
        /* keyString = */           "Key_Q",           
        /* modifiersString = */     "NoModifiers",           
        /* buttonString = */        "-1",                    
        /* wheelString = */         "-1",                    
        /* actionString = */        "TO_LEFT",      
        /* saveToConfigFile = */    false               
    );

	key_mapping_manager->addAction(    
        /* context = */             "FPSCamera",       
        /* keyString = */           "Key_SPACE",           
        /* modifiersString = */     "NoModifiers",           
        /* buttonString = */        "-1",                    
        /* wheelString = */         "-1",                    
        /* actionString = */        "JUMP",      
        /* saveToConfigFile = */    false               
    );


	KeyMapping::setContext(KeyMappingManager::getInstance()->getContext("FPSCamera"));
  
	if(KeyMapping::getContext().isInvalid())
	{
  		LOG( Ra::Core::Utils::logINFO ) << "CameraContext not defined (maybe the configuration file do not contains it)";
  		LOG( Ra::Core::Utils::logERROR ) << "CameraContext all keymapping invalid !";
  		return;
	}
 
	//#define KMA_VALUE( XX ) XX = key_mapping_manager->getActionIndex( KeyMapping::getContext(), #XX );
  	//KeyMappingCameraManipulatorFPS
 	//#undef KMA_VALUE
	
	TO_FORWARD = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "TO_FORWARD");
	TO_BACKWARD = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "TO_BACKWARD");
	TO_LEFT = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "TO_LEFT");
	TO_RIGHT = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "TO_RIGHT");
	JUMP = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "JUMP");
	ROTATE = key_mapping_manager->getActionIndex(KeyMapping::getContext(), "ROTATE");

}

KeyMappingManager::Context CameraManipulatorFPS::mappingContext()
{
	return CameraManipulatorFPS::getContext();
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
	last_x = event->pos().x();
	last_y = event->pos().y();

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

	if(first_mouse)
    {
        last_x = event->pos().x();
        last_y = event->pos().y();
        first_mouse = false;
    }
  
    float xoffset = event->pos().x() - last_x;
    float yoffset = last_y - event->pos().y(); 
    last_x = event->pos().x();
    last_y = event->pos().y();

	Core::Vector3 vec_proj = Ra::Core::Math::projectOnPlane(    
        /* planePos = */ m_camera->getPosition(),    
        /* planeNormal = */ m_camera->getUpVector(),    
        /* point = */ m_camera->getPosition() + m_camera->getDirection());	

	Scalar pitch = Ra::Core::Math::angle(
		/* v1 = */ vec_proj,
		/* v2 = */ m_camera->getDirection());

    float sensitivity = 0.1f;
    xoffset *= m_cameraSensitivity;
    yoffset *= m_cameraSensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

	Core::Vector3 new_direction;
    new_direction.x() = cos(Ra::Core::Math::toRadians(yaw)) * cos(Ra::Core::Math::toRadians(pitch));
    new_direction.y() = sin(Ra::Core::Math::toRadians(pitch));
    new_direction.z() = sin(Ra::Core::Math::toRadians(yaw)) * cos(Ra::Core::Math::toRadians(pitch));
    //new_direction = glm::normalize(new_direction);

	m_camera->setPosition(new_direction);

	return m_currentAction.isValid();

}


bool CameraManipulatorFPS::handleWheelEvent(
	QWheelEvent *event,                                                                     
    const Qt::MouseButtons &buttons, 
    const Qt::KeyboardModifiers &modifiers,                                                 
    int key)
{
                                                       
    m_currentAction = KeyMappingManager::KeyMappingAction::Invalid();                                    	return true;                                    
                                                       
}


bool CameraManipulatorFPS::handleKeyPressEvent( 
	QKeyEvent *event, 
	const KeyMappingManager::KeyMappingAction &action)
{

	if(action == TO_FORWARD)
	{
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

	return m_currentAction.isValid();

}


bool CameraManipulatorFPS::handleKeyReleaseEvent(
	QKeyEvent *event, 
	const KeyMappingManager::KeyMappingAction &action)
{

	m_currentAction = KeyMappingManager::KeyMappingAction::Invalid();
	return true;

}


void CameraManipulatorFPS::updateCamera()
{

	//m_referenceFrame = m_camera->getFrame();

}


void CameraManipulatorFPS::fitScene(const Core::Aabb &aabb){} 


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

















