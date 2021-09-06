#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>




// To resize the viewport when the user resizes the window !
void framebuffer_size_callback(GLFWwindow* window,int width,int height);



// Input process
void processInput(GLFWwindow* window);


const int WIDTH = 600;
const int HEIGHT = 400;



// Max vertex attribs
int nrAttributes;

// Shader Sources

//vertex shader source
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0 ) in vec3 aPos;\n"
"layout (location = 1 ) in vec3 aColor; \n"
"out vec4 fragmentColor; //Fragment color input from the vertex shader! \n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos,1.0f);\n"
//"   fragmentColor = vec4(0.5f,0.0f,0.5f,1.0f); \n"
"   fragmentColor = vec4(aColor,1.0f); \n"
"}\0";


//fragment shader source

const char* fragmentShaderSource= "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 fragmentColor;\n"
"uniform vec4 uniformFragmentColor;\n"
"void main()\n"
"{\n"
//"   FragColor = vec4(0.3f,1.0f,1.0f,1.0f);"
"   FragColor = fragmentColor;\n"
//  "FragColor = uniformFragmentColor;\n"
"}";

//fragment shader source with yellow color

const char* fragmentShaderSourceY= "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f,1.0f,0.0f,1.0f);"
"}";



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

 //Fetching the max vertex attributes

  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&nrAttributes);

  std::cout<<"Max vertexs allowed in my graphics card :"<<nrAttributes<<std::endl;



  //Vertex data

  // Triangle
  GLfloat vertexData[] = {
      -0.5f, -0.5f, 0.0f, // Left Bottom
       0.5f, -0.5f, 0.0f, // Right Bottom
       0.0f,  0.5f, 0.0f  // Top
  };

  // Rectangle
  GLfloat vertexData2[] = {
    //upper triange
    0.75f,0.75f,0.0f, //upper left
    1.0f,0.75f,0.0f, //upper right
    0.75f,0.5f,0.0f, //lower left

    //lower triangle
    0.75f,0.5f,0.0f, //lower left
    1.0f,0.5f,0.0f, //lower left
    1.0f,0.75,0.0f //upper right
  };




  //Rectangele with EBO
  GLfloat vertexData3[] = {
    //upper triange
    0.75f,0.75f,0.0f, //upper left
    1.0f,0.75f,0.0f, //upper right
    0.75f,0.5f,0.0f, //lower left
    1.0f,0.5f,0.0f, //lower right
  };

  unsigned int indices[] = {  // note that we start from 0!
      0,1,2,   // first triangle
      2,3,1    // second triangle
  };


  // Two Triangles

  GLfloat vertexData4[] = {
      //triangle 1
       -1.0f,-0.75f,0.0f, //lower left
       -0.1f,-0.75f,0.0f, //lower right
       -0.1f,0.75f,0.0f, // top

      //triangle 2
      1.0f,-0.75f,0.0f, //lower right
      0.1f,-0.75f,0.0f, //lower left
      0.1f,0.75,0.0f //top
  };

  GLfloat vertexData5[] = {
      // positions         // colors
       0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
      -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
       0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
  };


  // Vertex buffer object
  unsigned int VBO,VBO_EBO,VBO_2,VBO_3;
  glGenBuffers(1,&VBO);
  glGenBuffers(1,&VBO_EBO);
  glGenBuffers(1,&VBO_2);
  glGenBuffers(1,&VBO_3);


  //Vertex Array Object VAO
  unsigned int VAO,VAO_EBO,VAO_2,VAO_3;
  glGenVertexArrays(1,&VAO);
  glGenVertexArrays(1,&VAO_EBO);
  glGenVertexArrays(1,&VAO_2);
  glGenVertexArrays(1,&VAO_3);

  //EBO for element buffer object
  unsigned int EBO;
  glGenBuffers(1,&EBO);


  //Binding VAO before configuring VBO
  glBindVertexArray(VAO);

  // Binding with the GL_Array_buffer
  glBindBuffer(GL_ARRAY_BUFFER,VBO);

  //Copying the vertex data
  glBufferData(GL_ARRAY_BUFFER,sizeof (vertexData),vertexData,GL_STATIC_DRAW);

  //Attribute stuff

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof (GL_FLOAT),(void*)0);
  glEnableVertexAttribArray(0);

  //Unbinding VAO after the configuration
  glBindVertexArray(0);

  //Cleanup
  glBindBuffer(GL_ARRAY_BUFFER,0);

  //Binding VAO for EBO config
  glBindVertexArray(VAO_EBO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO_EBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof (vertexData3),vertexData3,GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof (indices),indices,GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3* sizeof(GL_FLOAT),(void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  //Cleanup
  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  glBindBuffer(GL_ARRAY_BUFFER,0);

  //Excecise 1 Config

  glBindVertexArray(VAO_2);

  glBindBuffer(GL_ARRAY_BUFFER,VBO_2);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData4),vertexData4,GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GL_FLOAT),(void*)0);
  glEnableVertexAttribArray(0);

  //Cleanup
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,0);

  // Vertex Data 5
  glBindVertexArray(VAO_3);

  glBindBuffer(GL_ARRAY_BUFFER,VBO_3);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData5),vertexData5,GL_STATIC_DRAW);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(GL_FLOAT),(void*)0);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(GL_FLOAT),(void*)(3 * sizeof(GL_FLOAT)) );

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  //Cleanup

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,0);





  //Vertex Shader

    // Assinging the vertexShader or creating it
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Compiling

  glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
  glCompileShader(vertexShader);

   //Error handling

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);

  if(!success)
  {
      glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
      std::cout<<"ERROR::VERTEX::SHADER::COMPILATION_FAILED"<<std::endl;
      std::cout<<infoLog;

  }


  //Fragment Shader

    //Creating the fragment Shader
  unsigned int FragmentShader;
  FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  //Yellow Fragment shader
  unsigned int fragmentShaderY;
  fragmentShaderY = glCreateShader(GL_FRAGMENT_SHADER);


    //Compiling the Fragment Shader
  glShaderSource(FragmentShader,1,&fragmentShaderSource,NULL);
  glCompileShader(FragmentShader);

  //Compiling The yellow Fragment Shader
  glShaderSource(fragmentShaderY,1,&fragmentShaderSourceY,NULL);
  glCompileShader(fragmentShaderY);

    //Error Handling
  glGetShaderiv(FragmentShader,GL_COMPILE_STATUS,&success);

  //Error Handling Yellow fragment Shader
  glGetShaderiv(fragmentShaderY,GL_COMPILE_STATUS,&success);

  if(!success)
  {
      glGetShaderInfoLog(FragmentShader,512,NULL,infoLog);
      //yellow shader(fragment)
      glGetShaderInfoLog(fragmentShaderY,512,NULL,infoLog);
      std::cout<<"ERROR::Fragment::SHADER::COMPILATION_FAILED"<<std::endl;
      std::cout<<infoLog;

  }


 //Shader program

  unsigned int ShaderProgram;
  ShaderProgram = glCreateProgram();

  //Attaching shaders and Linking with right order
  glAttachShader(ShaderProgram,vertexShader);
  glAttachShader(ShaderProgram,FragmentShader);
//  glAttachShader(ShaderProgram,fragmentShaderY);
  glLinkProgram(ShaderProgram);

  //Error Handling for Shader linking
  glGetProgramiv(ShaderProgram,GL_LINK_STATUS,&success);
  if(!success)
  {
      glGetProgramInfoLog(ShaderProgram ,512,NULL,infoLog);
      std::cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED"<<std::endl;
      std::cout<<infoLog;
  }



  glDeleteShader(vertexShader);
  glDeleteShader(FragmentShader);
  glDeleteShader(fragmentShaderY);

  // Get uniform declared in fragment Shader

  int fragmentColorLocation = glGetUniformLocation(ShaderProgram,"uniformFragmentColor");





  while(!glfwWindowShouldClose(window))

  {

      processInput(window);

      glClearColor(0.8f,1.0f,1.0f,1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      //Triangle Drawing
      glUseProgram(ShaderProgram);
      // Assign Uniform Value
      float timeValue = glfwGetTime();
      float greenValue = (sin(timeValue) / 2.0f ) + 0.5f ;
      glUniform4f(fragmentColorLocation,0.0f,greenValue,0.0f,1.0f);


      // Simple Triangle !
//      glBindVertexArray(VAO);
//      glDrawArrays(GL_TRIANGLES,0,3);
//      glBindVertexArray(0);

      //EBO Rectangle
//      glBindVertexArray(VAO_EBO);
//      glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
//      glBindVertexArray(0);

      //Excercise 1
//       glBindVertexArray(VAO_2);
//       glDrawArrays(GL_TRIANGLES,0,6);
//       glBindVertexArray(0);


      //Triangle with edge color with color in vertex data

      glBindVertexArray(VAO_3);
      glDrawArrays(GL_TRIANGLES,0,3);
      glBindVertexArray(0);


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
