/// @file Vertices.h
/// @brief Defines a vertices object
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef VERTICES_H
#define VERTICES_H

//////////////////////////////////////////////////////////////////////////
/// Math Libraries
//////////////////////////////////////////////////////////////////////////
#include "FRMath.h"

//////////////////////////////////////////////////////////////////////////
/// NDC For OpenGL (-1, 1)
///             (0,1)
///               ^
///               |
///               |
///               |
///               |
/// (-1,0)<-----(0,0)----->(1,0)
///               |
///               |
///               |
///               |
///               v
///             (0,-1)
//////////////////////////////////////////////////////////////////////////
namespace ForerunnerEngine
{
    struct Vertices2D
    {
        Vertices2D( glm::vec2 vertexPosition,
                    glm::vec2 textureCoordinates)
        {
            this->VertexPosition        = vertexPosition;
            this->TextureCoordinates    = textureCoordinates;
        }

        glm::vec2 VertexPosition;
        glm::vec2 TextureCoordinates;
    };

    struct Vertices3D
    {
        Vertices3D( glm::vec3 vertexPosition,
                    glm::vec3 normalPosition,
                    glm::vec2 textureCoordinate)
        {
            this->VertexPosition    = vertexPosition;
            this->NormalPosition    = normalPosition;
            this->TextureCoordinate = textureCoordinate;
        }

        glm::vec3 VertexPosition;
        glm::vec3 NormalPosition;
        glm::vec2 TextureCoordinate;
    };
}

#endif