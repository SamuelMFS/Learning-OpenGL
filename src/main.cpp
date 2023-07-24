#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <iostream>
#include <math.h>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "shaderClass.h"

// An array with all the 6 vertices that makes the 3 triangles
GLfloat vertices[] = {
    -0.5f,  -0.5f * float(sqrt(3)) / 3,   0.0f, 0.8f, 0.3f,  0.02f,
    0.5f,   -0.5f * float(sqrt(3)) / 3,   0.0f, 0.8f, 0.3f,  0.02f,
    0.0f,   0.5f * float(sqrt(3)) / 1.5f, 0.0f, 1.0f, 0.6f,  0.32f,
    -0.25f, 0.5f * float(sqrt(3)) / 6,    0.0f, 0.9f, 0.45f, 0.17f,
    0.25f,  0.5f * float(sqrt(3)) / 6,    0.0f, 0.9f, 0.45f, 0.17f,
    0.0f,   -0.5f * float(sqrt(3)) / 3,   0.0f, 0.8f, 0.3f,  0.2f};

// the indices that tells the app which vertices makes which triangles
GLuint indices[] = {0, 5, 4, 1, 4, 3, 2, 3, 5};

int main() {
  // Initialize GLFW
  glfwInit();

  // Tell GLFW what version of OpenGL we are using
  // In this case we are using OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Tell GLFW we are using the CORE profile
  // So that means we only have the modern functions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
  GLFWwindow *window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
  // Error check if the window fails to create
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  // Introduce the window into the current context
  glfwMakeContextCurrent(window);

  // Load GLAD so it configures OpenGL
  gladLoadGL(glfwGetProcAddress);
  // Specify the viewport of OpenGL in the Window
  // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
  glViewport(0, 0, 800, 800);

  Shader shaderProgram("./vendor/shaders/default.vert",
                       "./vendor/shaders/default.frag");

  VAO VAO1;
  VAO1.Bind();

  VBO VBO1(vertices, sizeof(vertices));
  EBO EBO1(indices, sizeof(indices));

  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float),
                  (void *)(3 * sizeof(float)));
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  // Main while loop
  while (!glfwWindowShouldClose(window)) {
    // Specify the color of the background
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // Tell OpenGL which Shader Program we want to use
    shaderProgram.Activate();
    // Bind the VAO so OpenGL knows to use it
    VAO1.Bind();
    // Draw the triangle using the GL_TRIANGLES primitive
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);
    // Take care of all GLFW events
    glfwPollEvents();
  }

  // Delete all the objects we've created
  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  shaderProgram.Delete();
  // Delete window before ending the program
  glfwDestroyWindow(window);
  // Terminate GLFW before ending the program
  glfwTerminate();
  return 0;
}
