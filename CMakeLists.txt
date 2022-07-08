cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0042 NEW)

project(HelloRadium VERSION 1.0.0)

# ------------------------------------------------------------------------------
# set wanted application defaults for cmake settings
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
# Set default install location to installed-<Compiler_ID> folder in build dir we do not want to
# install to /usr by default
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX
        "${CMAKE_CURRENT_BINARY_DIR}/installed-${CMAKE_CXX_COMPILER_ID}-${CMAKE_BUILD_TYPE}"
        CACHE PATH "Install path prefix, prepended onto install directories." FORCE
    )
    message("Set install prefix to ${CMAKE_INSTALL_PREFIX}")
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# ------------------------------------------------------------------------------
set(CMAKE_PREFIX_PATH ../Radium-Engine/Bundle-GNU/lib/cmake/Radium)

if(NOT IN_RADIUM_BUILD_TREE)
    find_package(Radium REQUIRED Core Engine Gui)
endif()

find_qt_package(COMPONENTS Core Widgets REQUIRED)
set(Qt_LIBRARIES Qt::Core Qt::Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# ------------------------------------------------------------------------------



set(app_sources 
	src/main.cpp
	src/FPS/CameraManipulatorFPS.cpp
	src/FPS/CameraManipulatorFPS.hpp
	)

# to install the app as a redistribuable bundle on macos, add MACOSX_BUNDLE when calling
# add_executable
add_executable(${PROJECT_NAME} ${app_sources})

# if("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
#     target_compile_options(
#         ${PROJECT_NAME}
#         PRIVATE /MP
#                 /W4
#                 /wd4251
#                 /wd4592
#                 /wd4127
#                 /Zm200
#                 $<$<CONFIG:Release>:
#                 /Gw
#                 /GS-
#                 /GL
#                 /GF
#                 >
#         PUBLIC
#     )
# endif()

target_link_libraries(
    ${PROJECT_NAME} PUBLIC Radium::Core Radium::Engine Radium::Gui ${Qt_LIBRARIES}
)

target_compile_options(${PROJECT_NAME} PRIVATE PUBLIC ${DEFAULT_COMPILE_OPTIONS} INTERFACE)

configure_radium_app(NAME ${PROJECT_NAME})


# cmake_minimum_required(VERSION 3.10)

# project(Aim-Radium)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_BUILD_TYPE Release)

# set(CMAKE_PREFIX_PATH ../Radium-Engine/Bundle-GNU/lib/cmake/Radium)
# #set(Radium_Dir ./libs/Radium-Engine/Bundle-GNU/lib/cmake/Radium)

# include_directories(
# 	./libs/Radium-Engine/Bundle-GNU/include
# 	./src/Gui
# )


# # Radium-Engine
# find_package(Radium REQUIRED Core Engine Gui IO PluginBase)
# set(RADIUM_LIB Radium::Core Radium::Engine Radium::IO Radium::Gui)

# # Qt5


# #set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# #set(CMAKE_AUTORCC ON)

# find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
# set(QT5_LIB Qt5::Core Qt5::Widgets Qt5::OpenGL)
# #qt5_wrap_ui(app_uis_moc ./src/Gui/MainWindow.ui)

# #set(GUI_SOURCE
# #	./src/Gui/MainWindow.hpp
# #	./src/Gui/MainWindow.cpp
# #	#./src/Gui/ui_MainWindow.hpp
# #)

# set(FPS_SOURCE
# 	./src/FPS/CameraManipulatorFPS.hpp
# 	./src/FPS/CameraManipulatorFPS.cpp
# )
# # Executable
# add_executable(${PROJECT_NAME}
# 	./src/main.cpp
# 	#${GUI_SOURCE}
# 	#${FPS_SOURCE}
# )

# target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
# target_include_directories(
#     ${PROJECT_NAME} PRIVATE ${RADIUM_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} # Moc
#                             ${CMAKE_CURRENT_SOURCE_DIR}
# )

# target_link_libraries(Aim-Radium ${RADIUM_LIB} ${QT5_LIB})

# configure_radium_app(NAME ${PROJECT_NAME})

#####################################################################################################
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
