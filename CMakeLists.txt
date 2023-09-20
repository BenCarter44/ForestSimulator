# CMakeList.txt : CMake project for PrettyConsole, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("GraphicsOpenGL")

# Add source to this project's executable.
add_executable (GraphicsOpenGL "src/main.cpp" "src/DisplayObject.cpp" "src/Window.cpp" "src/WindowManager.cpp")
target_include_directories(GraphicsOpenGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_sources(GraphicsOpenGL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(GraphicsOpenGL PUBLIC -lglut -lGLU -lGL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# TODO: Add tests and install targets if needed.
