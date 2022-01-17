/// @file WindowTest.cpp
/// @brief Test drive for window library
/// @author Haval Ahmed (Haval-Ahmed)

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstdint>

//////////////////////////////////////////////////////////////////////////
/// IMGUI Libraries
//////////////////////////////////////////////////////////////////////////
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//////////////////////////////////////////////////////////////////////////
/// GLFW Libraries
//////////////////////////////////////////////////////////////////////////
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//////////////////////////////////////////////////////////////////////////
/// GLM Libraries
//////////////////////////////////////////////////////////////////////////
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "OpenGLPrimitive2D.h"

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
void processMouseMovement(GLFWwindow* window, double xPosition, double yPosition);
void processMouseScroll(GLFWwindow* window, double xOffset, double yOffset);

int main()
{
    // glfw: initialize and configure
    // -------------------------------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // -------------------------------------------------------------------------------
    GLFWwindow* forerunnerWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window Test", NULL, NULL);

    // glfw: check if valid
    // -------------------------------------------------------------------------------
    if (forerunnerWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // glfw: Set context current to this thread
    // -------------------------------------------------------------------------------
    glfwMakeContextCurrent(forerunnerWindow);

    // glfw: register callback functions
    // -------------------------------------------------------------------------------
    glfwSetFramebufferSizeCallback(forerunnerWindow, windowResizingCallback);

    // glfw: register mouse callback
    // -------------------------------------------------------------------------------
    glfwSetCursorPosCallback(forerunnerWindow, processMouseMovement);

    // glfw: register mouse scroll callback
    // -------------------------------------------------------------------------------
    glfwSetScrollCallback(forerunnerWindow, processMouseScroll);

    // glfw: tell GLFW to capture our mouse
    // -------------------------------------------------------------------------------
    // glfwSetInputMode(forerunnerWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // -------------------------------------------------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // imgui: create the context
    // -------------------------------------------------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // imgui: grab the io context
    // -------------------------------------------------------------------------------
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // imgui: Setup Dear ImGui style
    // -------------------------------------------------------------------------------
    ImGui::StyleColorsDark();

    // opengl: identify glsl version
    // -------------------------------------------------------------------------------
    const char* glslVersion = "#version 430";

    // Setup Platform/Renderer backends
    // -------------------------------------------------------------------------------
    ImGui_ImplGlfw_InitForOpenGL(forerunnerWindow, true);
    ImGui_ImplOpenGL3_Init(glslVersion);

    // Create primitives
    // -------------------------------------------------------------------------------
    ForerunnerEngine::Rectangle2DPrimitive Rect2D;

    Rect2D.setColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
    Rect2D.setPosition(glm::vec3(100.0f, 100.0f, 0.0f));
    Rect2D.setScale(glm::vec3(50.0f, 50.0f, 0.0f));

    // Create projection matrix
    // -------------------------------------------------------------------------------
    glm::mat4 Ortho2DMatrix = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), 0.0f, static_cast<float>(WINDOW_HEIGHT), -1.0f, 1.0f);

    // render loop
    // -------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(forerunnerWindow))
    {
        // glfw: poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwPollEvents();

        // Poll and handle events (input, window resizing, etc...)
        // -------------------------------------------------------------------------------
        processKeyboardInput(forerunnerWindow);

        // imgui: create new frame for opengl3 and glfw 
        // -------------------------------------------------------------------------------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // imgui: render each frame
        // -------------------------------------------------------------------------------
        ImGui::Render();

        // opengl: render
        // -------------------------------------------------------------------------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // opengl: render
        // -------------------------------------------------------------------------------
        Rect2D.draw(0.0f, Ortho2DMatrix);

        // imgui: Backend rendering for OpenGL
        // -------------------------------------------------------------------------------
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // glfw: swap buffers - double buffering
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(forerunnerWindow);
    }

    // imgui: cleanup
    // ------------------------------------------------------------------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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

// glfw: whenever the mouse moves call our callback function
// ---------------------------------------------------------------------------------------------
void processMouseMovement(GLFWwindow* window, double xPosition, double yPosition)
{

}

void processMouseScroll(GLFWwindow* window, double xOffset, double yOffset)
{

}