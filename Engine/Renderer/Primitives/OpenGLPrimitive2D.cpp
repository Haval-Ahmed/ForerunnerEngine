/// @file OpenGLPrimitive2D.cpp
/// @brief Primitive Renderer Object 2D class that contains necessary Renderer specific information to render an object
/// @author Haval Ahmed

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "OpenGLPrimitive2D.h"

//////////////////////////////////////////////////////////////////////////
/// External Libraries
//////////////////////////////////////////////////////////////////////////
#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"

namespace ForerunnerEngine
{
    OpenGLPrimitive2D::OpenGLPrimitive2D()
        : VAO(0)
        , VBO(0)
        , IBO(0)
    {
        // Create a basic 2D shader
        Shader2D.createVertexShader(BASIC_2D_VERTEX_SHADER, strlen(BASIC_2D_VERTEX_SHADER));
        Shader2D.createFragmentPixelShader(BASIC_2D_PIXEL_SHADER, strlen(BASIC_2D_PIXEL_SHADER));
    }
    
    void OpenGLPrimitive2D::setPosition(const glm::vec3& position)
    {
        ModelTransform.Position = position;
        ModelTransform.ModelMatrix = glm::translate(ModelTransform.ModelMatrix, position);
    }
    
    void OpenGLPrimitive2D::setOrientation(const glm::vec3& orientation)
    {
        ModelTransform.Rotation = orientation;
    }
    
    void OpenGLPrimitive2D::setScale(const glm::vec3& scale)
    {
        ModelTransform.Scale = scale;
        ModelTransform.ModelMatrix = glm::scale(ModelTransform.ModelMatrix, scale);
    }
    
    void OpenGLPrimitive2D::setColor(const glm::vec4& color)
    {
        Shader2D.setUniform("Color", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    }
    
    glm::vec3 OpenGLPrimitive2D::getPosition(void)
    {
        return glm::vec3();
    }
    
    glm::vec3 OpenGLPrimitive2D::getOrientation(void)
    {
        return glm::vec3();
    }
    
    glm::vec3 OpenGLPrimitive2D::getScale(void)
    {
        return glm::vec3();
    }

    Rectangle2DPrimitive::Rectangle2DPrimitive() : OpenGLPrimitive2D()
    {
        // Generate the necessary buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO);
        glBindVertexArray(0);

        // Initialize primitive
        this->init();
    }

    Rectangle2DPrimitive::~Rectangle2DPrimitive()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &IBO);
    }

    void Rectangle2DPrimitive::init(void)
    {
        float vertices[] = {
            // positions          // colors           // texture coords
             0.5f,  0.5f, 1.0f, 1.0f, // top right
             0.5f, -0.5f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f, 1.0f  // top left 
        };
        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        // Bind the buffer objects to the vertex array object
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, PrimData.Vertices.size() * PrimData.Vertices.size() * sizeof(float), PrimData.Vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, PrimData.Indices.size() * sizeof(uint32_t), PrimData.Indices.data(), GL_STATIC_DRAW);

        // Vertice Attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, PrimData.Vertices.size() * sizeof(float), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // UV/Texture attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, PrimData.Vertices.size() * sizeof(float), (void*)offsetof(Vertices2D, Vertices2D::TextureCoordinates));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void Rectangle2DPrimitive::draw(float deltaTime, const glm::mat4& projectionMatrix)
    {
        Shader2D.useShader();

        glBindVertexArray(VAO);

        Shader2D.setUniform("ProjMtx", projectionMatrix);
        Shader2D.setUniform("ModelMtx", ModelTransform.ModelMatrix);
        Shader2D.setUniform("Color", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

        // Activate and bind texture
        Texture.useTexture();

        // Draw rectangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Unbind VAO
        glBindVertexArray(0);

        Shader2D.disableShader();
    }
}