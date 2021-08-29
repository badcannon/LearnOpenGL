#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>




// To resize the viewport when the user resizes the window !
void framebuffer_size_callback(GLFWwindow* window,int width,int height);



// Input process
void processInput(GLFWwindow* window);


const int WIDTH = 600;
const int HEIGHT = 400;


int main(void)
{

  // Glfw window and context creation initiation !
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


  GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"Learning OpenGL",NULL,NULL);
  if(window == NULL)
  {
      std::cout<<"Failed to create GLFW window"<<std::endl;
      glfwTerminate();
      return -1;
  }

  glfwMakeContextCurrent(window);


  //Initializing GLAD for function pointers platform specific !

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {

      std::cout<<"Glad failed to initialize !"<<std::endl;
      return -1;
  }


  glViewport(0,0,400,600);

  glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

  while(!glfwWindowShouldClose(window))

  {

      processInput(window);

      glClearColor(0.8f,1.0f,1.0f,1.0f);
      glClear(GL_COLOR_BUFFER_BIT);


      glfwSwapBuffers(window);
      glfwPollEvents();

  }

 //Clean up
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
    glViewport(0,0,width,height);
}


void processInput(GLFWwindow* window)
{

    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }

}
