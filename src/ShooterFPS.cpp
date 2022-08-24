#include "ShooterFPS.hpp"

#include <Core/Types.hpp>
#include <Gui/Utils/KeyMappingManager.hpp>
#include <Core/Math/LinearAlgebra.hpp>
#include <Core/Math/Math.hpp>





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
    transform_t.translation() = Ra::Core::Vector3(0_ra, 0.5_ra, 0_ra);
	m_camera->applyTransform(transform_t);
	speed = 0.1_ra;
	this->aim_trainer = nullptr;
	
}

ShooterFPS::ShooterFPS(const Ra::Gui::CameraManipulator& other):	
	Ra::Gui::CameraManipulator(other)
{

	vector_up = Ra::Core::Vector3( 0_ra, 1_ra, 0_ra );
	vector_forward = Ra::Core::Vector3( 0_ra, 0_ra, 1_ra );
	this->cursor.setPos(m_camera->getWidth() / 2, m_camera->getWidth() / 2);
	theta = 0_ra;
	Ra::Core::Transform transform_t( Ra::Core::Transform::Identity() );
    transform_t.translation() = Ra::Core::Vector3(0_ra, 0.5_ra, 0_ra);
	m_camera->applyTransform(transform_t);
	speed = 0.1_ra;
	this->aim_trainer = nullptr;
}

ShooterFPS::~ShooterFPS() {}



bool ShooterFPS::handleMousePressEvent(
	QMouseEvent *event,
	const Qt::MouseButtons &buttons,
	const Qt::KeyboardModifiers &modifiers,
	int key)
{
	// SHOOT !?
	
	
	if(this->aim_trainer != nullptr){

		Core::Vector3 position_shoot = m_camera->getPosition();
		auto ray = this->m_camera->getRayFromScreen(Ra::Core::Vector2(m_camera->getWidth() / 2, m_camera->getHeight() / 2));
		bool target_touched = this->aim_trainer->target_shooted(ray);

	}

	// m_currentAction = KeyMappingManager::getInstance()->getAction(
		// KeyMapping::getContext(), buttons, modifiers, false);



	return m_currentAction.isValid();
	
}

bool ShooterFPS::handleMouseReleaseEvent(QMouseEvent *event)
{
	
	m_currentAction = KeyMappingManager::KeyMappingAction::Invalid();
	this->updateCrosshair();
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
	this->updateCrosshair();

	if ( m_light != nullptr ) {
        m_light->setPosition( m_camera->getPosition() );
        m_light->setDirection( m_camera->getDirection() );
    }

	
	// auto near = m_camera->getZNear()
	
	// Update crosshair
	// auto vec = m_camera->unProjectFromScreen(Ra::Core::Vector3(m_camera->getWidth() / 2, m_camera->getHeight() / 2, 0));
	// Ra::Core::Transform transform;
	// transform.translation() = vec;
	// this->crosshair->update(transform);
	// Ra::Core::Transform transform;
	// transform.translation() = m_target;
	// this->crosshair->update(transform);





	
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
	if ( m_light != nullptr ) {
        m_light->setPosition( m_camera->getPosition() );
        m_light->setDirection( m_camera->getDirection() );
    }
}


void ShooterFPS::setCameraTarget(const Core::Vector3 &target)
{

	m_target = target;
    m_camera->setDirection( ( target - m_camera->getPosition() ).normalized() );

}


void ShooterFPS::resetCamera() {}


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
	this->updateCrosshair();
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

	if ( m_light != nullptr ) {
        m_light->setPosition( m_camera->getPosition() );
        m_light->setDirection( m_camera->getDirection() );
    }

	this->updateCrosshair();
}

void ShooterFPS::moveToRight()
{
	Ra::Core::Transform right_t( Ra::Core::Transform::Identity() );
    right_t.translation() = speed*m_camera->getRightVector().normalized();
	m_camera->applyTransform(right_t);

	if ( m_light != nullptr ) {
        m_light->setPosition( m_camera->getPosition() );
        m_light->setDirection( m_camera->getDirection() );
    }

	this->updateCrosshair();
}

void ShooterFPS::moveToLeft()
{
	Ra::Core::Transform left_t( Ra::Core::Transform::Identity() );
    left_t.translation() = -speed*m_camera->getRightVector().normalized();
	m_camera->applyTransform(left_t);

	if ( m_light != nullptr ) {
        m_light->setPosition( m_camera->getPosition() );
        m_light->setDirection( m_camera->getDirection() );
    }
	
	this->updateCrosshair();
}

void ShooterFPS::setAimTrainer(AimTrainer& aim_trainer)
{
	this->aim_trainer = &aim_trainer;
}


void ShooterFPS::setCrosshair(Crosshair& crosshair)
{
	this->crosshair = &crosshair;
	this->updateCrosshair();
	
	
}

void ShooterFPS::updateCrosshair()
{
	Ra::Core::Transform transform(Ra::Core::Transform::Identity());
	auto p = this->m_camera->unProjectFromScreen(Ra::Core::Vector3(m_camera->getWidth() / 2, m_camera->getHeight() / 2, 0));
	transform.translation() = p;
	this->crosshair->update(transform);
}

} // END NAMESPACE Gui
} // END NAMESPACE Ra