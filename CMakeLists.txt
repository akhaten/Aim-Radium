cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0042 NEW)

# project(AimRadium VERSION 1.0.0)

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
#set(CMAKE_PREFIX_PATH ../Radium-Engine/Bundle-GNU/lib/cmake/Radium)

if(NOT IN_RADIUM_BUILD_TREE)
    find_package(Radium REQUIRED Core Engine Gui)
endif()

find_qt_package(COMPONENTS Core Widgets REQUIRED)
set(Qt_LIBRARIES Qt::Core Qt::Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# ------------------------------------------------------------------------------




include_directories(src)
# add_subdirectory(examples/StaticTrainer)
# add_subdirectory(examples/AnimationTrainer)

set(app_sources 

    src/AimRadium.cpp
    src/AimRadium.hpp

    src/AimTrainer.cpp
    src/AimTrainer.hpp

    src/Target.cpp
    src/Target.hpp

    src/Spot.cpp
    src/Spot.hpp

    src/Animation/AnimationDatas.cpp
    src/Animation/AnimationDatas.hpp

    src/Animation/Animation.cpp
    src/Animation/Animation.hpp

    src/Animation/AnimationSystem.cpp
    src/Animation/AnimationSystem.hpp

    src/Map.cpp
    src/Map.hpp

    src/Crosshair.cpp
    src/Crosshair.hpp

    src/ShooterFPS.cpp
	src/ShooterFPS.hpp

)

# to install the app as a redistribuable bundle on macos, add MACOSX_BUNDLE when calling

# add_executable(${PROJECT_NAME} ${app_sources})

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

set(animation examples/AnimationTrainer/main.cpp ${app_sources})
add_executable(AnimationTrainer ${animation})
target_link_libraries(
    AnimationTrainer PUBLIC Radium::Core Radium::Engine Radium::Gui ${Qt_LIBRARIES}
)
target_compile_options(AnimationTrainer PRIVATE PUBLIC ${DEFAULT_COMPILE_OPTIONS} INTERFACE)
configure_radium_app(NAME AnimationTrainer)

set(static examples/StaticTrainer/main.cpp ${app_sources})
add_executable(StaticTrainer ${static})
target_link_libraries(
    StaticTrainer PUBLIC Radium::Core Radium::Engine Radium::Gui ${Qt_LIBRARIES}
)
target_compile_options(StaticTrainer PRIVATE PUBLIC ${DEFAULT_COMPILE_OPTIONS} INTERFACE)
configure_radium_app(NAME StaticTrainer)


