cmake_minimum_required(VERSION 3.10)

project(Aim-Radium)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_PREFIX_PATH ./libs/Radium-Engine/Bundle-GNU/lib/cmake/Radium)
#set(Radium_Dir ./libs/Radium-Engine/Bundle-GNU/lib/cmake/Radium)

include_directories(
	./libs/Radium-Engine/Bundle-GNU/include
	./src/Gui
)


# Radium-Engine
find_package(Radium REQUIRED Core Engine Gui IO PluginBase)
set(RADIUM_LIB Radium::Core Radium::Engine Radium::IO Radium::Gui)

# Qt5


#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
set(QT5_LIB Qt5::Core Qt5::Widgets Qt5::OpenGL)
#qt5_wrap_ui(app_uis_moc ./src/Gui/MainWindow.ui)

set(GUI_SOURCE
	./src/Gui/MainWindow.hpp
	./src/Gui/MainWindow.cpp
	#./src/Gui/ui_MainWindow.hpp
)

# Executable
add_executable(${PROJECT_NAME}
	./src/main.cpp
	${GUI_SOURCE}
)

target_link_libraries(Aim-Radium ${RADIUM_LIB} ${QT5_LIB})

#project(Aim-Radium VERSION 0.1)

#if (NOT CMAKE_BUILD_TYPE)
#	set(CMAKE_BUILD_TYPE Release)
#endif ()


#find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
#set(Qt5_LIBRARIES Qt5::Core Qt5::Widgets)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)



#set(Radium_DIR ./libs/Radium-Engine/Bundle-GNU/lib/cmake/Radium)

#find_package(Radium REQUIRED Core Engine Gui PluginBase IO)

#set(app_sources
#        ./src/main.cpp
#)


#set(app_uis
#Gui/ui/MainWindow.ui)

#qt5_wrap_ui(app_uis_moc ${app_uis})


#add_executable(${PROJECT_NAME}
#${app_sources}
#${headers}
#${app_uis_moc}
#)

#target_include_directories(${PROJECT_NAME} PRIVATE
	#${RADIUM_INCLUDE_DIRS}
#${CMAKE_CURRENT_BINARY_DIR} # Moc
#${CMAKE_CURRENT_SOURCE_DIR}
#)

# Include Radium
#include_directories(./libs/Radium-Engine/Bundle-GNU/include)

# Linking
#target_link_libraries(${PROJECT_NAME}
#Radium::Core
#Radium::Engine
#Radium::Gui
#Radium::IO
#${Qt5_LIBRARIES}
#)

#configure_radium_app(
	#NAME ${PROJECT_NAME}
#USE_PLUGINS
#)
