# Main cmake file 
# Multi Texture example
# Rafael Radkowski, rafael@iastate.edu
# Iowa State University
# ME/CS/CprE 557 Computer Graphics, Fall 2015

cmake_minimum_required(VERSION 2.6)

# Main project name is ARMaker
project(cs557_hw2_p1)


set(CFILE_PATH  "${CMAKE_SOURCE_DIR}/../SDK/cmake/")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../SDK/cmake/")

message(STATUS "Source directory ${CMAKE_SOURCE_DIR}")
message(STATUS "SDK directory ${CMAKE_SOURCE_DIR}/../SDK")


# Find packages
FIND_PACKAGE(glew REQUIRED)
FIND_PACKAGE(glm REQUIRED)
FIND_PACKAGE(glfw3 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)


# Include dirs
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW3_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../gl_common_p1/)

# Add all files to the configuration
file(GLOB HCI557_Multi_Texture_SRC
	main_multi_texture.cpp
    ../gl_common_p1/HCI557Common.cpp
    ../gl_common_p1/HCI557Common.h
    ../gl_common_p1/controls.cpp
    ../gl_common_p1/controls.h
    ../gl_common_p1/CoordSystem.cpp
    ../gl_common_p1/CoordSystem.h
    ../gl_common_p1/GLObject.h
    ../gl_common_p1/GLObject.cpp
    ../gl_common_p1/GLSphere.cpp
    ../gl_common_p1/GLSphere.h
    ../gl_common_p1/Shaders.h
    ../gl_common_p1/Shaders.cpp
    ../gl_common_p1/Plane3d.h
    ../gl_common_p1/Plane3d.cpp
    ../gl_common_p1/Texture.h
    ../gl_common_p1/Texture.cpp
    ../gl_common_p1/HCI557Datatypes.h
    ../gl_common_p1/GLAppearanceBase.h
    ../gl_common_p1/GLAppearance.h
    ../gl_common_p1/GLAppearance.cpp
    ../gl_common_p1/camera.h
    ../gl_common_p1/camera.cpp
    ../gl_common_p1/GLObjects3D.h
)

set(HCI557_RES
	../data/shaders/hw4_p1.fs
    ../data/shaders/hw4_p1.vs
)


#----
# SRC Groups
source_group(Resources FILES ${HCI557_RES})


# Create an executable
add_executable(HCI557_Multi_Texture ${HCI557_Multi_Texture_SRC})


# Add link directories
# Note required for this project
IF(WIN32)
	link_directories(${CMAKE_SOURCE_DIR}/../SDK/lib)
ELSE(WIN32)
	link_directories(${CMAKE_SOURCE_DIR}/../SDK/lib)
	link_directories(/usr/local/lib)
	link_directories(/usr/local/Cellar/glfw3/3.0.4/lib)
	link_directories(/usr/local/Cellar/glew/1.11.0/lib)
ENDIF(WIN32)


# Add libraries
target_link_libraries(HCI557_Multi_Texture ${GLEW_LIBRARY} ${GLFW3_LIBRARY} ${OPENGL_LIBRARIES} ${OPENGL_LIBRARIES} )
