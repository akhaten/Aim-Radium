#include "ShooterFPS.hpp"

#include <Gui/Utils/KeyMappingManager.hpp>
#include <Core/Math/LinearAlgebra.hpp>
#include <Core/Math/Math.hpp>
#include <glm/glm.hpp>



namespace Ra {
namespace Gui {

// using KeyMappingShooterFPS = Ra::Gui::KeyMappingManageable<ShooterFPS>;
  
using ShooterFPSKeyMapping = Ra::Gui::KeyMappingManageable<ShooterFPS>;
// #define KMA_VALUE( XX ) static KeyMappingManager::KeyMappingAction XX;
// KeyMappingShooterFPS
// #undef KMA_VALUE

#define KMA_VALUE( XX ) Gui::KeyMappingManager::KeyMappingAction Gui::ShooterFPS::XX;
KeyMappingFPSManipulator
#undef KMA_VALUE

/**
 * Allow configure action
 */
void ShooterFPS::configureKeyMapping_impl()
{

	// Create key mapping manager
	

	ShooterFPSKeyMapping::setContext(Gui::KeyMappingManager::getInstance()->getContext( "FPSManipulatorContext" ));
	
	if ( ShooterFPSKeyMapping::getContext().isInvalid() ) {
        LOG( Ra::Core::Utils::logWARNING ) << "KeyMappingShooterFPS not defined (maybe the "
                                               "configuration file do not contains it). Adding "
                                               "default configuration for KeyMappingShooterFPS.";
		

    }


}

KeyMappingManager::Context ShooterFPS::mappingContext()
{
	return ShooterFPSKeyMapping::getContext();
}

ShooterFPS::ShooterFPS():
	CameraManipulator()
{

	vector_up = Ra::Core::Vector3( 0_ra, 1_ra, 0_ra );
	vector_forward = Ra::Core::Vector3( 0_ra, 0_ra, 1_ra );
	this->cursor.setPos(m_camera->getWidth() / 2, m_camera->getWidth() / 2);
	theta = 0_ra;
	Ra::Core::Transform transform_t( Ra::Core::Transform::Identity() );
    transform_t.translation() = Ra::Core::Vector3(0_ra, 3_ra, 0_ra);
	m_camera->applyTransform(transform_t);
	speed = 0.1_ra;
	// Ra::Gui::KeyMappingManager::createInstance();
	// Ra::Gui::KeyMappingManager::getInstance()->addListener(Ra::Gui::ShooterFPS::KeyMapping::configureKeyMapping);
	
}

ShooterFPS::ShooterFPS(const Ra::Gui::CameraManipulator& other):	
	Ra::Gui::CameraManipulator(other)
{
	vector_up = Ra::Core::Vector3( 0_ra, 1_ra, 0_ra );
	vector_forward = Ra::Core::Vector3( 0_ra, 0_ra, 1_ra );
	this->cursor.setPos(m_camera->getWidth() / 2, m_camera->getWidth() / 2);
	theta = 0_ra;
	Ra::Core::Transform transform_t( Ra::Core::Transform::Identity() );
    transform_t.translation() = Ra::Core::Vector3(0_ra, 3_ra, 0_ra);
	m_camera->applyTransform(transform_t);
	speed = 0.1_ra;
}

ShooterFPS::~ShooterFPS() {}



bool ShooterFPS::handleMousePressEvent(
	QMouseEvent *event,
	const Qt::MouseButtons &buttons,
	const Qt::KeyboardModifiers &modifiers,
	int key)
{
	// SHOOT !?
	// Core::Vector3 position_shoot = m_camera->getPosition();
	// Core::Vector3 direction_shoot = m_camera->getDirection();
	// Compute intersection between straight and and object of scene.
	// printf("handleMousePressEvent\n");
	m_currentAction = KeyMappingManager::getInstance()->getAction(
		KeyMapping::getContext(), buttons, modifiers, false);

	// if(m_currentAction == ROTATE)
	// {
	// 	printf("RATOTE\n");
	// }

	return m_currentAction.isValid();
	
}

bool ShooterFPS::handleMouseReleaseEvent(QMouseEvent *event)
{
	// printf("handleMouseReleaseEvent\n");
	m_currentAction = KeyMappingManager::KeyMappingAction::Invalid();
    return true;

}


bool ShooterFPS::handleMouseMoveEvent(    
	QMouseEvent *event,     
    const Qt::MouseButtons &buttons,     
    const Qt::KeyboardModifiers &modifiers,     
    int key)
{

	// printf("handleMouseMoveEvent\n");
	Scalar offset_x = cursor.pos().x() - (m_camera->getWidth() / 2);
	Scalar offset_y = cursor.pos().y() - (m_camera->getHeight() / 2);
	
	Scalar dx = offset_x / m_camera->getWidth();
    Scalar dy = offset_y / m_camera->getHeight();

	
    m_quickCameraModifier = 5.0_ra;

	Scalar dphi   = dx * m_cameraSensitivity * m_quickCameraModifier;
    Scalar dtheta = -dy * m_cameraSensitivity * m_quickCameraModifier;

	
	if (Ra::Core::Math::PiDiv2 < theta+dtheta){
		auto limit = theta+dtheta-Ra::Core::Math::PiDiv2;
		// dtheta = dtheta-limit;
		m_camera->setDirection(vector_up);
		theta = Ra::Core::Math::PiDiv2;
		Core::Transform R( Core::Transform::Identity() );
		m_camera->applyTransform(R);
		// theta += dtheta;
	}else if (theta+dtheta < -Ra::Core::Math::PiDiv2){
		auto limit = theta+dtheta+Ra::Core::Math::PiDiv2;
		m_camera->setDirection(-vector_up);
		// dtheta = dtheta-limit;
		theta = -Ra::Core::Math::PiDiv2;
		// theta += dtheta;
		Core::Transform R( Core::Transform::Identity() );
		m_camera->applyTransform(R);
	}else{
		theta += dtheta;
		Core::Transform R( Core::Transform::Identity() );
		if ( std::abs( dphi ) > std::abs( dtheta ) ) {
			R = Core::AngleAxis( -dphi, vector_up );
		}else{
			R = Core::AngleAxis( -dtheta, -m_camera->getRightVector().normalized() );
		}

		Scalar d = ( m_target - m_camera->getPosition() ).norm();
		m_target = m_camera->getPosition() + d * m_camera->getDirection();

		m_camera->applyTransform(R);
	}

	this->cursor.setPos(QPoint(m_camera->getWidth() / 2, m_camera->getHeight() / 2));
	
	return m_currentAction.isValid();

}


bool ShooterFPS::handleWheelEvent(
	QWheelEvent *event,                                                                     
    const Qt::MouseButtons &buttons, 
    const Qt::KeyboardModifiers &modifiers,                                                 
    int key)
{
                                  
    m_currentAction = KeyMappingManager::KeyMappingAction::Invalid();
	return true;                                    
                                                       
}


bool ShooterFPS::handleKeyPressEvent( 
	QKeyEvent *event, 
	const KeyMappingManager::KeyMappingAction &action)
{

	return m_currentAction.isValid();

}


bool ShooterFPS::handleKeyReleaseEvent(
	QKeyEvent *event, 
	const KeyMappingManager::KeyMappingAction &action)
{
	// printf("handleKeyReleaseEvent\n");
	m_currentAction = KeyMappingManager::KeyMappingAction::Invalid();
	return true;

}


void ShooterFPS::updateCamera()
{
	m_target = m_camera->getPosition() + m_camera->getDirection().normalized();
	// m_referenceFrame = m_camera->getFrame();

}


void ShooterFPS::fitScene(const Core::Aabb &aabb){
  
} 


void ShooterFPS::setCameraPosition(const Core::Vector3 &position)
{

	m_camera->setPosition( position );
    m_camera->setDirection( ( m_target - position ).normalized() );
}


void ShooterFPS::setCameraTarget(const Core::Vector3 &target)
{

	m_target = target;
    m_camera->setDirection( ( target - m_camera->getPosition() ).normalized() );

}


void ShooterFPS::resetCamera()
{

}




void ShooterFPS::moveToForward()
{

	Core::Vector3 point_proj = Ra::Core::Math::projectOnPlane(
		/* planePos = */ m_camera->getPosition(),
		/* planeNormal = */ vector_up,
		/* point = */ m_camera->getPosition() + m_camera->getDirection());

	Core::Vector3 vec_proj = point_proj - m_camera->getPosition();

	Ra::Core::Transform forward_t( Ra::Core::Transform::Identity() );
    forward_t.translation() = speed*vec_proj.normalized();
	// forward_t.translation() = speed*vector_forward.normalized();
	m_camera->applyTransform(forward_t);
}

void ShooterFPS::moveToBackward()
{

	Core::Vector3 point_proj = Ra::Core::Math::projectOnPlane(
		/* planePos = */ m_camera->getPosition(),
		/* planeNormal = */ vector_up,
		/* point = */ m_camera->getPosition() + m_camera->getDirection());

	Core::Vector3 vec_proj = point_proj - m_camera->getPosition();

	Ra::Core::Transform backward_t( Ra::Core::Transform::Identity() );
    backward_t.translation() = -speed*vec_proj.normalized();;
	m_camera->applyTransform(backward_t);
}

void ShooterFPS::moveToRight()
{
	Ra::Core::Transform right_t( Ra::Core::Transform::Identity() );
    right_t.translation() = speed*m_camera->getRightVector().normalized();
	m_camera->applyTransform(right_t);
}

void ShooterFPS::moveToLeft()
{
	Ra::Core::Transform left_t( Ra::Core::Transform::Identity() );
    left_t.translation() = -speed*m_camera->getRightVector().normalized();
	m_camera->applyTransform(left_t);
}

}
}