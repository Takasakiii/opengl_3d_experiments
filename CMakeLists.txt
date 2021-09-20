cmake_minimum_required(VERSION 3.10)
project(objetos_3d_and_you)
add_executable(
    objetos_3d_and_you 
    main.c
    extras/fps.c
    extras/colors.c
    extras/forms.c
    extras/vector.c
    extras/camera.c
)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(objetos_3d_and_you glfw)
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
target_link_libraries(objetos_3d_and_you OpenGL::GL OpenGL::GLU)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CollectionC IMPORTED_TARGET collectionc)
target_link_libraries(objetos_3d_and_you PkgConfig::CollectionC)