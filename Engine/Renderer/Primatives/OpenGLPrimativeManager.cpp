//////////////////////////////////////////////////////////////////////////
/// @File:
///     OpenGLPrimativeManager.cpp
/// @Notes:
///     Basic opengl primative manager
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     See attached license 
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// 3rd Party Libraries
//////////////////////////////////////////////////////////////////////////
#include "glad/glad.h"

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "GLSLShaders.h"
#include "ImageIO.h"
#include "FilePaths.h"
#include "OpenGLPrimativeManager.h"

namespace ForerunnerEngine
{
    OpenGLPrimativeManager::OpenGLPrimativeManager()
        : vertexArrayObject(0)
        , vertexBufferObject(0)
        , normalBufferObject(0)
        , textureBufferObject(0)
        , indiceBufferObject(0)
        , initializeTexture(false)
    {
        // Clear any existing primatives
        primativeList.clear();
        vertices.clear();
        indicies.clear();

        // Create a default OpenGL shader
        auto vertexShaderLocation   = GLSL_FILE_DIRECTORY + "DefaultVertexShader.glsl";
        auto pixelShaderLocation    = GLSL_FILE_DIRECTORY + "DefaultPixelShader.glsl";

        shader.loadShaderFromFile(vertexShaderLocation.c_str(), GL_VERTEX_SHADER);
        shader.loadShaderFromFile(pixelShaderLocation.c_str(), GL_FRAGMENT_SHADER);

        initializeOpenGL();
    }

    OpenGLPrimativeManager::~OpenGLPrimativeManager()
    {
        for (auto primative : primativeList)
        {
            if (primative != nullptr)
            {
                delete primative;
            }
        }
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

    uint32_t OpenGLPrimativeManager::loadTexture(const char* filePath)
    {
        // Create a texture 
        uint32_t texture;

        /// Texture wrapping
        /// GL_REPEAT: The default behavior for textures.Repeats the texture image.
        /// GL_MIRRORED_REPEAT : Same as GL_REPEAT but mirrors the image with each repeat.
        /// GL_CLAMP_TO_EDGE : Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
        /// GL_CLAMP_TO_BORDER : Coordinates outside the range are now given a user - specified border color.
        /// Texture coordinates = s, t, r == x, y, z

        /// Texture filtering
        /// GL_NEAREST
        /// GL_LINEAR

        /// Minmaps
        /// GL_NEAREST_MIPMAP_NEAREST: takes the nearest mipmap to match the pixel sizeand uses nearest neighbor interpolation for texture sampling.
        /// GL_LINEAR_MIPMAP_NEAREST : takes the nearest mipmap leveland samples using linear interpolation.
        /// GL_NEAREST_MIPMAP_LINEAR : linearly interpolates between the two mipmaps that most closely match the size of a pixeland samples via nearest neighbor interpolation.
        /// GL_LINEAR_MIPMAP_LINEAR : linearly interpolates between the two closest mipmapsand samples the texture via linear interpolation.

        // Create a texture
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Image information
        int imageWidth, imageHeight, imageNumChannels;

        // Load image
        unsigned char* imageData = ForerunnerEngine::loadImage(filePath, &imageWidth, &imageHeight, &imageNumChannels);

        // If valid data, generate a texture and mipmaps
        if (imageData)
        {
            // Check if image contains alpha channel
            if (ForerunnerEngine::RGB_NUM_CHANNELS == imageNumChannels)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
            }
            else if (ForerunnerEngine::RGBA_NUM_CHANNELS == imageNumChannels)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
            }

            glGenerateMipmap(GL_TEXTURE_2D);
        }

        // Free image data
        ForerunnerEngine::freeImageData(imageData);

        return texture;
    }

    Primative3D* OpenGLPrimativeManager::createCube(void)
    {
        // Create a new primative 
        ForerunnerEngine::Primative3D* primative = new Primative3D();

        // Generate primative shape
        generateCube(primative);

        // Reupload the buffer to the GPU
        updateBufferData();

        // Append primative to list
        primativeList.emplace_back(primative);

        // Load a default texture
        primative->setTexture(loadTexture("C:/Projects/Forerunner_Engine/bin/container.jpg"));

        // Initialize texture
        shader.setUniform("texture1", primative->getTexture());

        return primative;
    }

    Primative3D* OpenGLPrimativeManager::createPyramid(void)
    {
        // Create a new primative 
        ForerunnerEngine::Primative3D* primative = new Primative3D();

        // Generate primative shape
        generatePyramid(primative);

        // Reupload the buffer to the GPU
        updateBufferData();

        // Append primative to list
        primativeList.emplace_back(primative);

        // Load a default texture
        primative->setTexture(loadTexture("C:/Projects/Forerunner_Engine/Support/container.jpg"));

        // Initialize texture
        shader.setUniform("texture1", primative->getTexture());

        return primative;
    }

    Primative3D* OpenGLPrimativeManager::createCylinder(void)
    {
        // Create a new primative 
        ForerunnerEngine::Primative3D* primative = new Primative3D();

        // Generate primative shape
        generateCylinder(primative);

        // Reupload the buffer to the GPU
        updateBufferData();

        // Append primative to list
        primativeList.emplace_back(primative);

        return primative;
    }

    Primative3D* OpenGLPrimativeManager::createPlane(void)
    {
        // Create a new primative 
        ForerunnerEngine::Primative3D* primative = new Primative3D();

        // Generate primative shape
        generatePlane(primative);

        // Reupload the buffer to the GPU
        updateBufferData();

        // Append primative to list
        primativeList.emplace_back(primative);

        return primative;
    }

    Primative3D* OpenGLPrimativeManager::createSphere(void)
    {
        // Create a new primative 
        ForerunnerEngine::Primative3D* primative = new Primative3D();

        // Generate primative shape
        generateSphere(primative);

        // Reupload the buffer to the GPU
        updateBufferData();

        // Append primative to list
        primativeList.emplace_back(primative);

        return primative;
    }

    Primative3D* OpenGLPrimativeManager::createTriangle(void)
    {
        // Create a new primative 
        ForerunnerEngine::Primative3D* primative = new Primative3D();

        // Generate primative shape
        generateTriangle(primative);

        // Reupload the buffer to the GPU
        updateBufferData();

        // Append primative to list
        primativeList.emplace_back(primative);

        return primative;
    }

    OpenGLShader& OpenGLPrimativeManager::getShader(void)
    {
        return shader;
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

    void OpenGLPrimativeManager::activeTexture(uint32_t texture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void OpenGLPrimativeManager::generateCube(ForerunnerEngine::Primative3D* primative)
    {
        // Will use X, Y, Z to specifiy (1, 1, 1);
        float x = 0.5f;
        float y = 0.5f;
        float z = 0.5f;

        // Primative has 24 vertices and 36 indices
        primative->setVertexSize(24);
        primative->setIndiceSize(36);

        // Front Face
        vertices.emplace_back(Vertices(glm::vec3(-x, -y, z), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
        vertices.emplace_back(Vertices(glm::vec3(-x, y, z),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, y, z),   glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, -y, z),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)));

        // Back Face
        vertices.emplace_back(Vertices(glm::vec3(-x, -y, -z),  glm::vec3(0.0f, 0.0f, -1.0f),  glm::vec2(1.0f, 0.0f)));
        vertices.emplace_back(Vertices(glm::vec3(-x, y, -z),   glm::vec3(0.0f, 0.0f, -1.0f),  glm::vec2(1.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, y, -z),    glm::vec3(0.0f, 0.0f, -1.0f),  glm::vec2(0.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, -y, -z),   glm::vec3(0.0f, 0.0f, -1.0f),  glm::vec2(0.0f, 0.0f)));

        // Top Face
        vertices.emplace_back(Vertices(glm::vec3(-x, y, -z), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(-x, y, z),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, y, z),   glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, y, -z),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)));

        // Bottom Face
        vertices.emplace_back(Vertices(glm::vec3(-x, -y, -z),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
        vertices.emplace_back(Vertices(glm::vec3(-x, -y, z),   glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, -y, z),    glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, -y, -z),   glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)));

        // Left Face
        vertices.emplace_back(Vertices(glm::vec3(-x, -y, z),   glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
        vertices.emplace_back(Vertices(glm::vec3(-x, y, z),    glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(-x, y, -z),   glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(-x, -y, -z),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)));

        // Right Face
        vertices.emplace_back(Vertices(glm::vec3(x, -y, -z), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, y, -z),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, y, z),   glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, -y, z),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)));

        // Initialize vertex offset to 0
        uint32_t vertexOffsetSize = 0;

        // Check size of indices, if first primative, offset is zero
        if (indicies.empty())
        {
            primative->setVertexOffsetSize(vertexOffsetSize);
            primative->setIndiceOffsetSize(0);
        }
        else
        {
            vertexOffsetSize = static_cast<uint32_t>(vertices.size());
            primative->setIndiceOffsetSize(static_cast<uint32_t>(indicies.size()));
        }
        
        // front face index data
        indicies.emplace_back(0 + vertexOffsetSize);
        indicies.emplace_back(1 + vertexOffsetSize);
        indicies.emplace_back(2 + vertexOffsetSize);
        indicies.emplace_back(0 + vertexOffsetSize);
        indicies.emplace_back(2 + vertexOffsetSize);
        indicies.emplace_back(3 + vertexOffsetSize);

        // back face index data
        indicies.emplace_back(4 + vertexOffsetSize);
        indicies.emplace_back(5 + vertexOffsetSize);
        indicies.emplace_back(6 + vertexOffsetSize);
        indicies.emplace_back(4 + vertexOffsetSize);
        indicies.emplace_back(6 + vertexOffsetSize);
        indicies.emplace_back(7 + vertexOffsetSize);

        // top face index data
        indicies.emplace_back(8    + vertexOffsetSize);
        indicies.emplace_back(9    + vertexOffsetSize);
        indicies.emplace_back(10   + vertexOffsetSize);
        indicies.emplace_back(8    + vertexOffsetSize);
        indicies.emplace_back(10   + vertexOffsetSize);
        indicies.emplace_back(11   + vertexOffsetSize);

        // bottom face index data
        indicies.emplace_back(12 + vertexOffsetSize);
        indicies.emplace_back(13 + vertexOffsetSize);
        indicies.emplace_back(14 + vertexOffsetSize);
        indicies.emplace_back(12 + vertexOffsetSize);
        indicies.emplace_back(14 + vertexOffsetSize);
        indicies.emplace_back(15 + vertexOffsetSize);

        // left face index data
        indicies.emplace_back(16 + vertexOffsetSize);
        indicies.emplace_back(17 + vertexOffsetSize);
        indicies.emplace_back(18 + vertexOffsetSize);
        indicies.emplace_back(16 + vertexOffsetSize);
        indicies.emplace_back(18 + vertexOffsetSize);
        indicies.emplace_back(19 + vertexOffsetSize);

        // right face index data
        indicies.emplace_back(20 + vertexOffsetSize);
        indicies.emplace_back(21 + vertexOffsetSize);
        indicies.emplace_back(22 + vertexOffsetSize);
        indicies.emplace_back(20 + vertexOffsetSize);
        indicies.emplace_back(22 + vertexOffsetSize);
        indicies.emplace_back(23 + vertexOffsetSize);
    }

    void OpenGLPrimativeManager::generatePyramid(ForerunnerEngine::Primative3D* primative)
    {
        // Will use X, Y, Z to specifiy (1, 1, 1);
        float x = 0.5f;
        float y = 0.5f;
        float z = 0.5f;

        // Primative has 5 vertices and 18 indices
        primative->setVertexSize(5);
        primative->setIndiceSize(18);

        // Bottom Face
        vertices.emplace_back(Vertices(glm::vec3(-x, 0.0f, -z), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
        vertices.emplace_back(Vertices(glm::vec3(-x, 0.0f, z),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, 0.0f, z),   glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
        vertices.emplace_back(Vertices(glm::vec3(x, 0.0f, -z),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)));

        // Main/Side Face
        vertices.emplace_back(Vertices(glm::vec3(0.0f, y, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)));

        // Initialize vertex offset to 0
        uint32_t vertexOffsetSize = 0;

        // Check size of indices, if first primative, offset is zero
        if (indicies.empty())
        {
            primative->setVertexOffsetSize(vertexOffsetSize);
            primative->setIndiceOffsetSize(0);
        }
        else
        {
            vertexOffsetSize = static_cast<uint32_t>(vertices.size());
            primative->setIndiceOffsetSize(static_cast<uint32_t>(indicies.size()));
        }

        // Bottom Base
        indicies.emplace_back(0 + vertexOffsetSize);
        indicies.emplace_back(1 + vertexOffsetSize);
        indicies.emplace_back(2 + vertexOffsetSize);

        indicies.emplace_back(0 + vertexOffsetSize);
        indicies.emplace_back(2 + vertexOffsetSize);
        indicies.emplace_back(3 + vertexOffsetSize);

        // Front Side
        indicies.emplace_back(1 + vertexOffsetSize);
        indicies.emplace_back(4 + vertexOffsetSize);
        indicies.emplace_back(2 + vertexOffsetSize);

        // Back Side
        indicies.emplace_back(0 + vertexOffsetSize);
        indicies.emplace_back(4 + vertexOffsetSize);
        indicies.emplace_back(3 + vertexOffsetSize);

        // Left side
        indicies.emplace_back(1 + vertexOffsetSize);
        indicies.emplace_back(4 + vertexOffsetSize);
        indicies.emplace_back(0 + vertexOffsetSize);

        // Right Side
        indicies.emplace_back(3 + vertexOffsetSize);
        indicies.emplace_back(4 + vertexOffsetSize);
        indicies.emplace_back(2 + vertexOffsetSize);
    }

    void OpenGLPrimativeManager::generateCylinder(ForerunnerEngine::Primative3D* primative)
    {

    }

    void OpenGLPrimativeManager::generatePlane(ForerunnerEngine::Primative3D* primative)
    {

    }

    void OpenGLPrimativeManager::generateSphere(ForerunnerEngine::Primative3D* primative)
    {

    }

    void OpenGLPrimativeManager::generateTriangle(ForerunnerEngine::Primative3D* primative)
    {

    }
}
