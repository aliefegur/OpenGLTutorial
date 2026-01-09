cmake_minimum_required(VERSION 3.20)

project(OpenGLTutorial)

add_subdirectory(libs/glfw-3.4)
add_subdirectory(libs/glad)

add_executable(${PROJECT_NAME} src/main.cpp
        src/Utils/File.h
        src/Utils/File.cpp
        src/Core/Vertex.h
        src/Core/ShaderProgram.cpp
        src/Core/ShaderProgram.h)
target_link_libraries(${PROJECT_NAME} glfw glad)

if (UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} OpenGL::GL)
elseif (WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif ()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets/ ${CMAKE_BINARY_DIR})
