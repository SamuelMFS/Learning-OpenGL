cmake_minimum_required(VERSION 3.22.1)

project(test)

find_package(OpenGL REQUIRED)

set(GLFW_SRC "vendor/glfw")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_SRC} ./build/)

set(GLAD "vendor/glad/include"
         "vendor/glad/src"
  )

add_executable(${PROJECT_NAME} src/main.cpp ${GLAD}/glad.c)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw )
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS} 
  PUBLIC ${GLAD} 
  PUBLIC ${GLFW_SRC}/deps
  )

