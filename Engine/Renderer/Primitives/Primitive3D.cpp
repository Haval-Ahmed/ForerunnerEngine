//////////////////////////////////////////////////////////////////////////
/// @File:
///     Primative3D.cpp
/// @Notes:
///     Basic 3D primative class
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     See attached license 
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "Primative3D.h"

namespace ForerunnerEngine
{
    Primative3D::Primative3D()
        : vertexArrayObject(0)
        , vertexBufferObject(0)
        , normalBufferObject(0)
        , textureBufferObject(0)
        , indiceBufferObject(0)
    {
        // Create a default OpenGL shader
        auto vertexShaderLocation = GLSL_FILE_DIRECTORY + "DefaultVertexShader.glsl";
        auto pixelShaderLocation  = GLSL_FILE_DIRECTORY + "DefaultPixelShader.glsl";

        shader.loadShaderFromFile(vertexShaderLocation.c_str(), GL_VERTEX_SHADER);
        shader.loadShaderFromFile(pixelShaderLocation.c_str(), GL_FRAGMENT_SHADER);

        initializeOpenGL();
    }

    void OpenGLPrimativeManager::draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
    {
        shader.useShader();

        glBindVertexArray(vertexArrayObject);

        shader.setUniform("projection", projectionMatrix);
        shader.setUniform("view", viewMatrix);

        for (auto primative : primativeList)
        {
            // Activate and bind texture
            glActiveTexture(GL_TEXTURE0 + primative->getTexture());
            glBindTexture(GL_TEXTURE_2D, primative->getTexture());

            shader.setUniform("model", primative->getModelMatrix());

            glDrawElements(GL_TRIANGLES, primative->getIndiceSize(), GL_UNSIGNED_INT, (void*)0);
        }

        glBindVertexArray(0);

        shader.disableShader();
    }

    void OpenGLPrimativeManager::initializeOpenGL(void)
    {
        // Generate the necessary buffers
        glGenVertexArrays(1, &vertexArrayObject);
        glGenBuffers(1, &vertexBufferObject);
        glGenBuffers(1, &indiceBufferObject);
        glBindVertexArray(0);
    }

    void OpenGLPrimativeManager::cleanOpenGL(void)
    {
        glDeleteVertexArrays(1, &vertexArrayObject);
        glDeleteBuffers(1, &vertexBufferObject);
        glDeleteBuffers(1, &indiceBufferObject);
    }

    void OpenGLPrimativeManager::updateBufferData(void)
    {
        // Bind the buffer objects to the vertex array object
        glBindVertexArray(vertexArrayObject);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertices), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), &indicies[0], GL_STATIC_DRAW);

        // Vertice Attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // Normal Attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)offsetof(Vertices, Vertices::normalPosition));
        glEnableVertexAttribArray(1);

        // Texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)offsetof(Vertices, Vertices::textureCoordinate));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }
}
