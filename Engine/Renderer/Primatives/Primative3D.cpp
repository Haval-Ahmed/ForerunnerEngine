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
        : vertexOffsetSize(0)
        , vertexSize(0)
        , indiceOffsetSize(0)
        , indiceSize(0)
        , texture(0)
    {
        
    }

    Primative3D::~Primative3D()
    {
        
    }

    void Primative3D::setPosition(const glm::vec3& primativePosition)
    {
        position = primativePosition;
    }

    void Primative3D::setOrientation(const glm::vec3& primativeOrientation)
    {
        orientation = primativeOrientation;
    }

    void Primative3D::setVelocity(const glm::vec3& primativeVelocity)
    {
        velocity = primativeVelocity;
    }

    glm::vec3 Primative3D::getPosition(void)
    {
        return position;
    }

    glm::vec3 Primative3D::getOrientation(void)
    {
        return orientation;
    }

    glm::vec3 Primative3D::getVelocity(void)
    {
        return velocity;
    }

    glm::mat4 Primative3D::getModelMatrix(void)
    {
        return modelMatrix;
    }

    glm::vec4 Primative3D::getAmbient(void)
    {
        return ambient;
    }

    glm::vec4 Primative3D::getDiffuse(void)
    {
        return diffuse;
    }

    glm::vec4 Primative3D::getSpecular(void)
    {
        return specular;
    }

    glm::vec4 Primative3D::getReflect(void)
    {
        return reflect;
    }

    void Primative3D::setVertexOffsetSize(uint32_t offsetSize)
    {
        vertexOffsetSize = offsetSize;
    }

    void Primative3D::setVertexSize(uint32_t size)
    {
        vertexSize = size;
    }

    void Primative3D::setIndiceOffsetSize(uint32_t offsetSize)
    {
        indiceOffsetSize = offsetSize;
    }

    void Primative3D::setIndiceSize(uint32_t size)
    {
        indiceSize = size;
    }

    void Primative3D::setTexture(uint32_t textureIndex)
    {
        texture = textureIndex;
    }

    uint32_t Primative3D::getVertexOffsetSize(void)
    {
        return vertexOffsetSize;
    }

    uint32_t Primative3D::getVertexSize(void)
    {
        return vertexSize;
    }

    uint32_t Primative3D::getIndiceOffsetSize(void)
    {
        return indiceOffsetSize;
    }

    uint32_t Primative3D::getIndiceSize(void)
    {
        return indiceSize;
    }
    uint32_t Primative3D::getTexture(void)
    {
        return texture;
    }
}
