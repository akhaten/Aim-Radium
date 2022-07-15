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
	printf("configureKeyMapping_impl\n");
	// Create key mapping manager
	//Gui::KeyMappingManager* key_mapping_manager = Gui::KeyMappingManager::getInstance();
	ShooterFPSKeyMapping::setContext(Gui::KeyMappingManager::getInstance()->getContext( "FPSManipulatorContext" ));
	
	if ( ShooterFPSKeyMapping::getContext().isInvalid() ) {
        LOG( Ra::Core::Utils::logWARNING ) << "KeyMappingShooterFPS not defined (maybe the "
                                               "configuration file do not contains it). Adding "
                                               "default configuration for KeyMappingShooterFPS.";

		Gui::KeyMappingManager* key_mapping_manager = Gui::KeyMappingManager::getInstance();

		// Add actions

		key_mapping_manager->addAction(
			/* context = */ 			"FPSManipulatorContext",
			/* keyString = */ 			"Key_Z",
			/* modifiersString = */ 	"NoModifier",
			/* buttonString = */ 		"",
			/* wheelString = */ 		"",
			/* actionString = */ 		"TO_FORDWARD"
		);

		key_mapping_manager->addAction(    
			/* context = */             "FPSManipulatorContext",       
			/* keyString = */           "Key_S",           
			/* modifiersString = */     "NoModifier",           
			/* buttonString = */        "",                    
			/* wheelString = */         "",                    
			/* actionString = */        "TO_BACKWARD"   
		);

		key_mapping_manager->addAction(    
			/* context = */             "FPSManipulatorContext",       
			/* keyString = */           "Key_D",           
			/* modifiersString = */     "NoModifier",           
			/* buttonString = */        "",                    
			/* wheelString = */         "",                    
			/* actionString = */        "TO_RIGHT"         
		);
		
		key_mapping_manager->addAction(    
			/* context = */             "FPSManipulatorContext",       
			/* keyString = */           "Key_Q",           
			/* modifiersString = */     "NoModifier",           
			/* buttonString = */        "",                    
			/* wheelString = */         "",                    
			/* actionString = */        "TO_LEFT"       
		);

		key_mapping_manager->addAction(    
			/* context = */             "FPSManipulatorContext",       
			/* keyString = */           "",           
			/* modifiersString = */     "NoModifier", 
			/* buttonString = */        "LeftButton",                    
			/* wheelString = */         "",                    
			/* actionString = */        "SHOOT"       
		);

		// Gui::KeyMappingManager::getInstance()->addAction( "FPSManipulatorContext",
        //                                                    "",
        //                                                    "ControlModifier",
        //                                                    "LeftButton",
        //                                                    "",
        //                                                    "TO_FORWARD" );

     }

	#define KMA_VALUE( XX )                                         \
     XX = Gui::KeyMappingManager::getInstance()->getActionIndex( \
         ShooterFPSKeyMapping::getContext(), #XX );
     KeyMappingFPSManipulator
 	#undef KMA_VALUE

}

KeyMappingManager::Context ShooterFPS::mappingContext()
{
	return ShooterFPSKeyMapping::getContext();
}

ShooterFPS::ShooterFPS():
	CameraManipulator()
{

	vector_up = Ra::Core::Vector3( 0_ra, 1_ra, 0_ra );
	this->cursor.setPos(m_camera->getWidth() / 2, m_camera->getWidth() / 2);
	theta = 0_ra;
	Ra::Core::Transform transform_t( Ra::Core::Transform::Identity() );
    transform_t.translation() = Ra::Core::Vector3(0_ra, 3_ra, 0_ra);
	m_camera->applyTransform(transform_t);
}

ShooterFPS::ShooterFPS(const Ra::Gui::CameraManipulator& other):	
	Ra::Gui::CameraManipulator(other)
{
	vector_up = Ra::Core::Vector3( 0_ra, 1_ra, 0_ra );;
	this->cursor.setPos(m_camera->getWidth() / 2, m_camera->getWidth() / 2);
	theta = 0_ra;
	Ra::Core::Transform transform_t( Ra::Core::Transform::Identity() );
    transform_t.translation() = Ra::Core::Vector3(0_ra, 3_ra, 0_ra);
	m_camera->applyTransform(transform_t);

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

	m_currentAction = KeyMappingManager::getInstance()->getAction(
		KeyMapping::getContext(), buttons, modifiers, false);

	return m_currentAction.isValid();
	
}

bool ShooterFPS::handleMouseReleaseEvent(QMouseEvent *event)
{

	m_currentAction = KeyMappingManager::KeyMappingAction::Invalid();
    return true;

}


bool ShooterFPS::handleMouseMoveEvent(    
	QMouseEvent *event,     
    const Qt::MouseButtons &buttons,     
    const Qt::KeyboardModifiers &modifiers,     
    int key)
{

	//printf("cursor : (%f, %f)\n", cursor.pos().x(), cursor.pos().y());
	Scalar offset_x = cursor.pos().x() - (m_camera->getWidth() / 2);
	Scalar offset_y = cursor.pos().y() - (m_camera->getHeight() / 2);
	
	Scalar dx = offset_x / m_camera->getWidth();
    Scalar dy = offset_y / m_camera->getHeight();

	
    m_quickCameraModifier = 5.0_ra;

	Scalar dphi   = dx * m_cameraSensitivity * m_quickCameraModifier;
    Scalar dtheta = -dy * m_cameraSensitivity * m_quickCameraModifier;

	// Procéder en utilisant l'angle entre le vec direction et le support (projection)
	// glm::vec3 da=glm::normalize(a-origin);
 	// glm::vec3 db=glm::normalize(b-origin);
 	// return glm::acos(glm::dot(da, db));

	Core::Vector3 proj = Ra::Core::Math::projectOnPlane(
        /* planePos = */ m_camera->getPosition(),
        /* planeNormal = */ vector_up,
        /* point = */ m_target);

	
	// auto forward_vec = proj-m_camera->getPosition();
	// auto angle_dir_for = Ra::Core::Math::angle(m_camera->getDirection().normalized(), forward_vec.normalized());
	// printf("(direction, forward) : %f rad = %f°\n", angle_dir_for, glm::degrees(angle_dir_for));


	




	// auto backward_vec = -forward_vec;
	// auto angle_dir_bac = Ra::Core::Math::angle(m_camera->getDirection().normalized(), backward_vec.normalized());
	// printf("(direction, backward) : %f rad = %f°\n", angle_dir_bac, glm::degrees(angle_dir_bac));

	// auto angle_up_for = Ra::Core::Math::angle(vector_up.normalized(), forward_vec.normalized());
	// printf("(vector_up, forward) : %f rad = %f°\n", angle_up_for, glm::degrees(angle_up_for));
	

	auto angle_dir_up = Ra::Core::Math::angle(m_camera->getDirection().normalized(), vector_up.normalized());
	auto deg = - (Ra::Core::Math::toDegrees(angle_dir_up) - 90_ra);
	auto rad = - (angle_dir_up - Ra::Core::Math::PiDiv2);
	printf("(direction, vector_up) : %f rad = %f°\n", rad, deg);

	// printf("(direction, vector_up) : %f rad = %f°\n", angle_dir_up, Ra::Core::Math::toDegrees(angle_dir_up));



	// auto v2 = backward_vec.normalized();
	// auto v1 = m_camera->getDirection().normalized();
	
	// double angle=atan2(v1.x()*v2.x()+v1.y()*v2.y(),v1.x()*v2.y()-v1.y()*v2.x());
	// printf("(direction, bforward) : %f rad = %f°\n", -angle, -glm::degrees(angle));





	// printf("angle : %f\n", angle);
	
	// if (glm::radians(89.0f) <= theta+dtheta){
	// 	dtheta = glm::radians(89.0f) - theta;
	// 	theta = glm::radians(89.0f);
	// }else if (theta+dtheta <= -glm::radians(89.0f)){
	// 	dtheta = glm::radians(89.0f) + theta;
	// 	theta = -glm::radians(89.0f);
	// }else{
	// 	theta += dtheta;
	// }
	
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

  
    // theta += dtheta;

	

	// Core::Transform R( Core::Transform::Identity() );
	// if ( std::abs( dphi ) > std::abs( dtheta ) ) {
	// 	R = Core::AngleAxis( -dphi, vector_up );
	// }else{
	// 	R = Core::AngleAxis( -dtheta, -m_camera->getRightVector().normalized() );
	// }

	// Scalar d = ( m_target - m_camera->getPosition() ).norm();
	// m_target = m_camera->getPosition() + d * m_camera->getDirection();

	// m_camera->applyTransform(R);
	


	this->cursor.setPos(QPoint(m_camera->getWidth() / 2, m_camera->getHeight() / 2));
	// glm::degrees()
	// printf("to rad : %f\n", glm::radians(89.0f));
	
	printf("theta : %f, %f\n", theta, Ra::Core::Math::toDegrees(theta));
	// printf("dtheta : %f, %f\n", dtheta, glm::degrees(dtheta));
	// printf("camera size : (%f, %f)\n", m_camera->getWidth(), m_camera->getHeight());
	// printf("cursor : (%f, %f)\n", cursor.pos().x(), cursor.pos().y());
	
  
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

	if(event->key()==Qt::Key_Q){
		printf("Q pressed\n");
	}
	

	printf("handleKeyPressEvent\n");
	if(action == TO_FORWARD)
	{
		// printf("forward\n");
		// Core::Vector3 point_proj = Ra::Core::Math::projectOnPlane(
        //     /* planePos = */ m_camera->getPosition(),
        //     /* planeNormal = */ m_camera->getUpVector(),
        //     /* point = */ m_camera->getPosition() + m_camera->getDirection());
        // Core::Vector3 new_position = point_proj; 
        // m_camera->setPosition(new_position);
		Ra::Core::Transform forward_t( Ra::Core::Transform::Identity() );
    	forward_t.translation() = Ra::Core::Vector3(0_ra, 0.0_ra, -0.1_ra);
		m_camera->applyTransform(forward_t);
	}

	if(action == TO_BACKWARD)
	{
		// Core::Vector3 point_proj = Ra::Core::Math::projectOnPlane(
		// 	/* planePos = */ m_camera->getPosition(),
		// 	/* planeNormal = */ m_camera->getUpVector(),
		// 	/* point = */ m_camera->getPosition() + m_camera->getDirection());
		// Core::Vector3 vec_proj = point_proj - m_camera->getPosition();
		// Core::Vector3 new_position = m_camera->getPosition() - vec_proj;
		// m_camera->setPosition(new_position);

		Ra::Core::Transform backward_t( Ra::Core::Transform::Identity() );
    	backward_t.translation() = Ra::Core::Vector3(0_ra, 0_ra, 0.1_ra);
		m_camera->applyTransform(backward_t);
	}

	if(action == TO_RIGHT)
	{
		// Core::Vector3 new_position = m_camera->getPosition() + m_camera->getRightVector();
		// m_camera->setPosition(new_position);

		Ra::Core::Transform right_t( Ra::Core::Transform::Identity() );
    	right_t.translation() = Ra::Core::Vector3(0.1_ra, 0_ra, 0_ra);
		m_camera->applyTransform(right_t);
	}

	if(action == TO_LEFT)
	{
		// Core::Vector3 new_position = m_camera->getPosition() - m_camera->getRightVector();
		// m_camera->setPosition(new_position);

		Ra::Core::Transform left_t( Ra::Core::Transform::Identity() );
    	left_t.translation() = Ra::Core::Vector3(-0.1_ra, 0_ra, 0_ra);
		m_camera->applyTransform(left_t);
	}

	if(action == JUMP)
	{
	}


	return m_currentAction.isValid();

}


bool ShooterFPS::handleKeyReleaseEvent(
	QKeyEvent *event, 
	const KeyMappingManager::KeyMappingAction &action)
{
	printf("handleKeyReleaseEvent\n");
	m_currentAction = KeyMappingManager::KeyMappingAction::Invalid();
	return true;

}


void ShooterFPS::updateCamera()
{

	// m_referenceFrame = m_camera->getFrame();

}


void ShooterFPS::fitScene(const Core::Aabb &aabb){
  
} 


void ShooterFPS::setCameraPosition(const Core::Vector3 &position)
{

}


void ShooterFPS::setCameraTarget(const Core::Vector3 &target)
{

	//m_referenceFrame.translation() = target;

}


void ShooterFPS::resetCamera(){}

}
}

















