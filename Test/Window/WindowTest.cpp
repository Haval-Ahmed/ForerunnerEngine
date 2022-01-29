/// @file WindowTest.cpp
/// @brief Test drive for window library
/// @author Haval Ahmed (Haval-Ahmed)

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstdint>

//////////////////////////////////////////////////////////////////////////
/// GLFW Libraries
//////////////////////////////////////////////////////////////////////////
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//////////////////////////////////////////////////////////////////////////
/// Unit Test Defines 
//////////////////////////////////////////////////////////////////////////
int32_t WINDOW_WIDTH    = 900;
int32_t WINDOW_HEIGHT   = 600;

//////////////////////////////////////////////////////////////////////////
/// Function Prototypes
//////////////////////////////////////////////////////////////////////////
void processKeyboardInput(GLFWwindow* window);
void windowResizingCallback(GLFWwindow* window, int32_t width, int32_t height);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // glfw window creation
    // --------------------
    GLFWwindow* forerunnerWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window Test", NULL, NULL);

    // glfw: check if valid
    // --------------------
    if (forerunnerWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // glfw: Set context current to this thread
    // --------------------
    glfwMakeContextCurrent(forerunnerWindow);

    // glfw: register callback functions
    glfwSetFramebufferSizeCallback(forerunnerWindow, windowResizingCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // opengl - get renderer info
    // ---------------------------------------
    int32_t         OpenGLVersion[2] = { 0 };
    const uint8_t*  Vendor;
    const uint8_t*  Renderer;
    
    glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);

    Vendor   = glGetString(GL_VENDOR);
    Renderer = glGetString(GL_RENDERER);

    std::cout << "GL Version: " << OpenGLVersion[0] << "." << OpenGLVersion[1] << std::endl;
    std::cout << "GL Vendor: " << Vendor << std::endl;
    std::cout << "GL Renderer: " << Renderer << std::endl;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(forerunnerWindow))
    {
        // input
        // -----
        processKeyboardInput(forerunnerWindow);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers - double buffering
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(forerunnerWindow);

        // glfw: poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    /// Always Return 0
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processKeyboardInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void windowResizingCallback(GLFWwindow* window, int32_t width, int32_t height)
{
    // Resize the glViewport
    glViewport(0, 0, width, height);
}
