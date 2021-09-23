#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "utils/shader.hpp"
#include "utils/logger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "utils/stb_image.h"

//Math libraries
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


//Camera
#include "utils/camera.h"

// To resize the viewport when the user resizes the window !
void framebuffer_size_callback(GLFWwindow* window,int width,int height);


//Mouse Input
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

//Scroll wheel
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


// Input process
void processInput(GLFWwindow* window,Shader shader);


const int WIDTH = 800;
const int HEIGHT = 600;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;


// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


int main()
{
    // Glfw window and context creation initiation !
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


    //Logger class !
    Logger log;




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


    glViewport(0,0,WIDTH,HEIGHT);

    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
     glfwSetScrollCallback(window, scroll_callback);

     // tell GLFW to capture our mouse
     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    //Shader
    Shader ourShader("/home/badcannon/Development/Projects/C++/LearnOpenGL/shaders/shader.vs", "/home/badcannon/Development/Projects/C++/LearnOpenGL/shaders/shader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // load and create a texture
         // -------------------------
         unsigned int texture1, texture2;
         // texture 1
         // ---------
         glGenTextures(1, &texture1);
         glBindTexture(GL_TEXTURE_2D, texture1);
         // set the texture wrapping parameters
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
         // set texture filtering parameters
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         // load image, create texture and generate mipmaps
         int width, height, nrChannels;
         stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
         unsigned char *data = stbi_load("/home/badcannon/Development/Projects/C++/LearnOpenGL/assets/images/container.jpg", &width, &height, &nrChannels, 0);
         if (data)
         {
             glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
             glGenerateMipmap(GL_TEXTURE_2D);
         }
         else
         {
             std::cout << "Failed to load texture" << std::endl;
         }
         stbi_image_free(data);
         // texture 2
         // ---------
         glGenTextures(1, &texture2);
         glBindTexture(GL_TEXTURE_2D, texture2);
         // set the texture wrapping parameters
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
         // set texture filtering parameters
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         // load image, create texture and generate mipmaps
         data = stbi_load("/home/badcannon/Development/Projects/C++/LearnOpenGL/assets/images/awesomeface.png", &width, &height, &nrChannels, 0);
         if (data)
         {
             // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
             glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
             glGenerateMipmap(GL_TEXTURE_2D);
         }
         else
         {
             std::cout << "Failed to load texture" << std::endl;
         }
         stbi_image_free(data);

         // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
         // -------------------------------------------------------------------------------------------



    //Enabling depth testing so opengl knows which fragment to discard based on the depth array mantained by glfw
         glEnable(GL_DEPTH_TEST);


    while(!glfwWindowShouldClose(window))

    {
        // per-frame time logic
             // --------------------
             float currentFrame = glfwGetTime();
             deltaTime = currentFrame - lastFrame;
             lastFrame = currentFrame;

        processInput(window,ourShader);

        glClearColor(0.8f,1.0f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture1);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, texture2);


                // get matrix's uniform location and set matrix
                ourShader.use();
                ourShader.setInt("ourTexture1", 0);
                ourShader.setInt("ourTexture2", 1);


                // pass projection matrix to shader (note that in this case it could change every frame)
                       glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
                       ourShader.setMat4("proj", projection);

                       // camera/view transformation
                       glm::mat4 view = camera.GetViewMatrix();
                       ourShader.setMat4("view", view);


                // render container
                glBindVertexArray(VAO);
                for(unsigned int i = 0; i < 10; i++)
                {
                    // calculate the model matrix for each object and pass it to shader before drawing
                               glm::mat4 model = glm::mat4(1.0f);
                               model = glm::translate(model, cubePositions[i]);

                               float angle = 20.0f * i;
                               if(i%3 == 0)
                                   angle = glfwGetTime() * 25.0f;
                               model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                               ourShader.setMat4("model", model);
                               glDrawArrays(GL_TRIANGLES, 0, 36);
                }


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
       // ------------------------------------------------------------------------
       glDeleteVertexArrays(1, &VAO);
       glDeleteBuffers(1, &VBO);
       glDeleteBuffers(1, &EBO);

   //Clean up
    glfwTerminate();
    return 0;
  }

void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
    glViewport(0,0,width,height);
}

 // Global Variable :D
float currentMixRatio = 0.0f;

void processInput(GLFWwindow* window,Shader shader)
{


    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }
    if(glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS)
        {
            glGetUniformfv(shader.ID,glGetUniformLocation(shader.ID,"mixRatio"),&currentMixRatio);
            currentMixRatio = currentMixRatio + 0.1f;
            if(currentMixRatio >= 1.0f) currentMixRatio = 1.0f;
            shader.setFloat("mixRatio", currentMixRatio );
        }
        if(glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS)
        {
            glGetUniformfv(shader.ID,glGetUniformLocation(shader.ID,"mixRatio"),&currentMixRatio);
            currentMixRatio = currentMixRatio - 0.1f;
            if(currentMixRatio <= 0.0f) currentMixRatio = 0.0f;
            shader.setFloat("mixRatio",currentMixRatio);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera.ProcessKeyboard(FORWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.ProcessKeyboard(BACKWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.ProcessKeyboard(LEFT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.ProcessKeyboard(RIGHT, deltaTime);
            if(glfwGetKey(window,GLFW_KEY_Q) == GLFW_PRESS)
                camera.ProcessKeyboard(UP,deltaTime);
            if(glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS)
                camera.ProcessKeyboard(DOWN,deltaTime);


}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

