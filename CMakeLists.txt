cmake_minimum_required(VERSION 3.10)
project(objetos_3d_and_you)
add_executable(objetos_3d_and_you main.cpp forms.cpp)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(objetos_3d_and_you glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(objetos_3d_and_you OpenGL::GL OpenGL::GLU)