cmake_minimum_required(VERSION 3.0.1)
project(Chess)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("vendor/glfw" ./build/)

set(GLAD "vendor/glad/include")

add_executable(cheese 
               ./src/main.cpp
               ./vendor/glad/src/gl.c
               ./src/EBO.cpp
               ./src/VAO.cpp
               ./src/VBO.cpp
               ./src/shaderClass.cpp
               )

target_link_libraries(cheese ${OPENGL_LIBRARIES} glfw)

target_include_directories(cheese PUBLIC ${GLAD}
                                  PUBLIC vendor/glfw/include
                                  PUBLIC vendor/glfw/deps 
                                  PUBLIC ${OPENGL_INCLUDE_DIRS}
                                  PUBLIC include/
  )
