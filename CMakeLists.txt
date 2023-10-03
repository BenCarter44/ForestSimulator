
cmake_minimum_required(VERSION 3.12)

# set the project name and version
project(OpenGLTest VERSION 1.0)

# Find Package

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
find_package(GLU REQUIRED)
include_directories(${GLU_LIBRARY_DIR})
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})

#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
#find_package(GLU REQUIRED)
#include_directories(${OPENGL_INCLUDE_DIRS})
#include_directories(${GLUT_INCLUDE_DIRS})
#include_directories(${GLU_INCLUDE_DIRS})

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE HEADERS2 "${CMAKE_SOURCE_DIR}/include/*.hpp")

add_executable(OpenGLTest ${SOURCES} ${HEADERS} ${HEADERS2})
#target_compile_options(OpenGLTest PUBLIC -lglut -lGLU -lGL)
# https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake


target_link_libraries(OpenGLTest ${GLUT_LIBRARIES} ${GLU_LIBRARIES} ${OPENGL_LIBRARIES})

target_include_directories(OpenGLTest PRIVATE "${CMAKE_SOURCE_DIR}/include")
