/// @file Vertices.h
/// @brief Defines a vertices object
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef VERTICES_H
#define VERTICES_H

//////////////////////////////////////////////////////////////////////////
/// Math Libraries
//////////////////////////////////////////////////////////////////////////
#include "FRMath.h"

namespace ForerunnerEngine
{
    struct Vertices
    {
        Vertices(   glm::vec3 vertexPosition,
                    glm::vec3 normalPosition,
                    glm::vec2 textureCoordinate)
        {
            this->vertexPosition    = vertexPosition;
            this->normalPosition    = normalPosition;
            this->textureCoordinate = textureCoordinate;
        }

        glm::vec3 vertexPosition;
        glm::vec3 normalPosition;
        glm::vec2 textureCoordinate;
    };
}

#endif