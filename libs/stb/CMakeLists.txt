cmake_minimum_required(VERSION 3.20)

project(stb)

add_library(${PROJECT_NAME} src/stb_image.c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
