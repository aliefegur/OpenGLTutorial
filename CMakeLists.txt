cmake_minimum_required(VERSION 3.20)

project(OpenGLTutorial)

# External libraries
set(EXTERNAL_LIBRARIES)
add_subdirectory(libs/glfw-3.4)
list(APPEND EXTERNAL_LIBRARIES glfw)

# Link OpenGL
if (UNIX)
    find_package(OpenGL REQUIRED)
    list(APPEND EXTERNAL_LIBRARIES OpenGL::GL)
elseif (WIN32)
    list(APPEND EXTERNAL_LIBRARIES opengl32)
endif ()

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBRARIES})

message(${EXTERNAL_LIBRARIES})
