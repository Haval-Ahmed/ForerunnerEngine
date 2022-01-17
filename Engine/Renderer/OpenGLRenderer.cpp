/// @file OpenGLRenderer.cpp
/// @brief Defines a opengl renderer object
/// @author Haval Ahmed (Haval-Ahmed)

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
    #include <iostream>
#endif

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "OpenGLRenderer.h"

//////////////////////////////////////////////////////////////////////////
/// Debug Definitions
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
    static void GLAPIENTRY checkForOpenGLError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
#endif // DEBUG

namespace ForerunnerEngine
{
    OpenGLRenderer::OpenGLRenderer(uint32_t x, uint32_t y, uint32_t width, uint32_t height, GLFWwindow* window) 
        : BaseRenderer()
    {
        /// Initialize member variables
        RendererXPosition   = x;
        RendererYPosition   = y;
        RendererWidth       = width;
        RendererHeight      = height;
        this->Window        = window;

        // Set OpenGL Debug Callback
#ifdef _DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(checkForOpenGLError, window);
#endif

        // Initialize renderer
        initializeRenderer();

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
    }


    OpenGLRenderer::~OpenGLRenderer(void)
    {
        destroyRenderer();
    };


    void OpenGLRenderer::initializeRenderer(void)
    {
        /// Get OpenGL Version, Vendor, and Renderer
        glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
        glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);

        Vendor   = glGetString(GL_VENDOR);
        Renderer = glGetString(GL_RENDERER);

        // Initialize glViewport
        setViewPort(RendererXPosition, RendererYPosition, RendererWidth, RendererHeight);
    }


    void OpenGLRenderer::destroyRenderer(void)
    {
        /// Delete context and invalidate current context
        glfwMakeContextCurrent(nullptr);
    }

    void OpenGLRenderer::configureDeviceContext(void)
    {

    }

    void OpenGLRenderer::makeDeviceContextCurrent(void)
    {
        glfwMakeContextCurrent(Window);
    }


    void OpenGLRenderer::resetDeviceContext(void)
    {
        glfwMakeContextCurrent(nullptr);
        glfwMakeContextCurrent(Window);
    }


    void OpenGLRenderer::deleteDeviceContext(void)
    {

    }

    void OpenGLRenderer::enableMultisampling(uint32_t samplingLevel)
    {
        MultisamplingLevel = samplingLevel;

        glEnable(GL_MULTISAMPLE);
    }

    void OpenGLRenderer::setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        /// Update renderer view port sizes
        RendererXPosition   = x;
        RendererYPosition   = y;
        RendererWidth       = width;
        RendererHeight      = height;

        /// Size viewport to specificed dimensions. 
        glViewport(RendererXPosition, RendererYPosition, RendererWidth, RendererHeight);
    }

    void OpenGLRenderer::setSize(uint32_t width, uint32_t height)
    {
        RendererWidth   = width;
        RendererHeight  = height;

        /// Size viewport to specificed dimensions. 
        glViewport(RendererXPosition, RendererYPosition, RendererWidth, RendererHeight);
    }


    void OpenGLRenderer::setXPosition(uint32_t x)
    {
        /// update class variable
        RendererXPosition = x;

        /// Size viewport to specificed dimensions. 
        glViewport(RendererXPosition, RendererYPosition, RendererWidth, RendererHeight);
    }

    void OpenGLRenderer::setYPosition(uint32_t y)
    {
        /// update class variable
        RendererYPosition = y;

        /// Size viewport to specificed dimensions. 
        glViewport(RendererXPosition, RendererYPosition, RendererWidth, RendererHeight);
    }

    void OpenGLRenderer::setWidth(uint32_t width)
    {
        /// update class variable
        RendererWidth = width;

        /// Size viewport to specificed dimensions. 
        glViewport(RendererXPosition, RendererYPosition, RendererWidth, RendererHeight);
    }

    void OpenGLRenderer::setHeight(uint32_t height)
    {
        /// update class variable
        RendererHeight = height;

        /// Size viewport to specificed dimensions. 
        glViewport(RendererXPosition, RendererYPosition, RendererWidth, RendererHeight);
    }

    void OpenGLRenderer::enableVSync(void)
    {
        /// Enabled adaptive VSync
        glfwSwapInterval(-1);
    }

    void OpenGLRenderer::disableVSync(void)
    {
        /// Disable VSync
        glfwSwapInterval(0);
    }

    void OpenGLRenderer::presentAndSwapBuffers(void)
    {
        glfwSwapBuffers(Window);
    }

    void OpenGLRenderer::enableWireframeMode(void)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void OpenGLRenderer::disableWireframeMode(void)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void OpenGLRenderer::enableDepthTest(void)
    {
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderer::disableDepthTest(void)
    {
        glEnable(0);
    }
}

#ifdef _DEBUG
    static void GLAPIENTRY checkForOpenGLError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        (void)length;
        (void)userParam;

        std::cout << "//////////////////////////////////////////////////////////////////////////" << std::endl;
        std::cout << "OpenGL Error ID: " << id << std::endl; 
        std::cout << "OpenGL Error Message: " << message << std::endl;
        
        switch (source)
        {
            case GL_DEBUG_SOURCE_API:
                std::cout << "Source Error: GL_DEBUG_SOURCE_API" << std::endl;
                break;

            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                std::cout << "Source Error: GL_DEBUG_SOURCE_WINDOW_SYSTEM" << std::endl;
                break;

            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                std::cout << "Source Error: GL_DEBUG_SOURCE_SHADER_COMPILER" << std::endl;
                break;

            case GL_DEBUG_SOURCE_THIRD_PARTY:
                std::cout << "Source Error: GL_DEBUG_SOURCE_THIRD_PARTY" << std::endl;
                break;

            case  GL_DEBUG_SOURCE_APPLICATION:
                std::cout << "Source Error: GL_DEBUG_SOURCE_APPLICATION" << std::endl;
                break;

            case GL_DEBUG_SOURCE_OTHER:
                std::cout << "Source Error: GL_DEBUG_SOURCE_OTHER" << std::endl;
                break;

            default:
                break;
        }

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:
                std::cout << "Type Error: GL_DEBUG_TYPE_ERROR" << std::endl;
                break;

            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                std::cout << "Type Error: GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR" << std::endl;
                break;

            case  GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                std::cout << "Type Error: GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR" << std::endl;
                break;

            case GL_DEBUG_TYPE_PORTABILITY:
                std::cout << "Type Error: GL_DEBUG_TYPE_PORTABILITY" << std::endl;
                break;

            case GL_DEBUG_TYPE_PERFORMANCE:
                std::cout << "Type Error: GL_DEBUG_TYPE_PERFORMANCE" << std::endl;
                break;

            case GL_DEBUG_TYPE_MARKER:
                std::cout << "Type Error: GL_DEBUG_TYPE_MARKER" << std::endl;
                break;

            case GL_DEBUG_TYPE_PUSH_GROUP:
                std::cout << "Type Error: GL_DEBUG_TYPE_PUSH_GROUP" << std::endl;
                break;

            case GL_DEBUG_TYPE_POP_GROUP:
                std::cout << "Type Error: GL_DEBUG_TYPE_POP_GROUP" << std::endl;
                break;

            case GL_DEBUG_TYPE_OTHER:
                std::cout << "Type Error: GL_DEBUG_TYPE_OTHER" << std::endl;
                break;

            case GL_DONT_CARE:
                std::cout << "Type Error: GL_DONT_CARE" << std::endl;
                break;

            default:
                break;
        }

        switch (severity)
        {
            case GL_DEBUG_SEVERITY_LOW:
                std::cout << "Severity Level: GL_DEBUG_SEVERITY_LOW" << std::endl;
                break;

            case GL_DEBUG_SEVERITY_MEDIUM:
                std::cout << "Severity Level: GL_DEBUG_SEVERITY_MEDIUM" << std::endl;
                break;

            case GL_DEBUG_SEVERITY_HIGH:
                std::cout << "Severity Level: GL_DEBUG_SEVERITY_HIGH" << std::endl;
                break;

            case GL_DEBUG_SEVERITY_NOTIFICATION:
                std::cout << "Severity Level: GL_DEBUG_SEVERITY_NOTIFICATION" << std::endl;
                break;

            default:
                break;
        }
    }
#endif