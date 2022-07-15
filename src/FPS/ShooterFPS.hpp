
#ifndef CAMERA_MANIPULATOR_FPS_HPP
#define CAMERA_MANIPULATOR_FPS_HPP

#pragma once
#include <Gui/RaGui.hpp>
  
#include <Core/Asset/Camera.hpp>
#include <Engine/Scene/CameraComponent.hpp>
#include <Gui/Viewer/CameraManipulator.hpp>

#include <QCursor>

namespace Ra {
namespace Gui {

class RA_GUI_API ShooterFPS :
	public Ra::Gui::CameraManipulator,
	public KeyMappingManageable<ShooterFPS>
{

	Q_OBJECT
	friend class KeyMappingManageable<ShooterFPS>;
	
	public:
		
		using KeyMapping = KeyMappingManageable<ShooterFPS>;

		ShooterFPS();
		ShooterFPS(const Ra::Gui::CameraManipulator& other); 
		~ShooterFPS();

		bool handleMousePressEvent(
				QMouseEvent *event, 
				const Qt::MouseButtons &buttons, 
				const Qt::KeyboardModifiers &modifiers, 
				int key) override;
		
		bool handleMouseReleaseEvent(QMouseEvent *event) override;

		bool handleMouseMoveEvent(
				QMouseEvent *event, 
				const Qt::MouseButtons &buttons, 
				const Qt::KeyboardModifiers &modifiers, 
				int key) override;

		bool handleWheelEvent(
				QWheelEvent *event, 
				const Qt::MouseButtons &buttons, 
				const Qt::KeyboardModifiers &modifiers, 
				int key) override;

		bool handleKeyPressEvent(
				QKeyEvent *event, 
				const KeyMappingManager::KeyMappingAction &action) override;

		bool handleKeyReleaseEvent(
				QKeyEvent *event, 
				const KeyMappingManager::KeyMappingAction &action) override;

		void updateCamera() override;
		
		KeyMappingManager::Context mappingContext() override;

	public slots:
		void fitScene(const Core::Aabb &aabb) override;
		void setCameraPosition(const Core::Vector3 &position) override;
		void setCameraTarget(const Core::Vector3 &target) override;
		void resetCamera() override;


	protected:
	
 	#define KeyMappingFPSManipulator	\
     	KMA_VALUE( TO_FORWARD )		\
     	KMA_VALUE( TO_BACKWARD )	\
     	KMA_VALUE( TO_LEFT )		\
     	KMA_VALUE( TO_RIGHT )    	\
     	KMA_VALUE( JUMP )			\
		KMA_VALUE( ROTATE )			\
		KMA_VALUE( SHOOT )
  
 	#define KMA_VALUE( XX ) static KeyMappingManager::KeyMappingAction XX;
     	KeyMappingFPSManipulator
 	#undef KMA_VALUE
	
		// inline static KeyMappingManager::KeyMappingAction TO_FORWARD;
		// inline static KeyMappingManager::KeyMappingAction TO_BACKWARD;
		// inline static KeyMappingManager::KeyMappingAction TO_LEFT;
		// inline static KeyMappingManager::KeyMappingAction TO_RIGHT;
		// inline static KeyMappingManager::KeyMappingAction JUMP;
		// inline static KeyMappingManager::KeyMappingAction ROTATE;
	
	private:
		QCursor cursor;
		Scalar theta;
		Core::Vector3 vector_up;
		KeyMappingManager::Context current_context;
		void configureKeyMapping_impl();
};
}
}
#endif // CAMERA_MA error: expected nested-name-specifier beforeNIPULATOR_FPS_HPP
