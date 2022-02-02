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

//////////////////////////////////////////////////////////////////////////
/// Texture Rangle For OpenGL
///(0,1)-----(1, 1)
///  ^       |
///  |       |
///  |       |
///  |       |
///  |       |
///(0,0)----->(1,0)
//////////////////////////////////////////////////////////////////////////

namespace ForerunnerEngine
{
    static constexpr uint32_t STRIDE_2D         = 4;
    static constexpr uint32_t STRIDE_3D         = 8;

    // OpenGL Offset Values
    // Per Khronos: Specifies a offset of the first component of the first generic vertex attribute 
    // in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. 
    // The initial value is 0.
    static constexpr uint32_t VERTICE_2D_OFFSET_0 = 0;
    static constexpr uint32_t VERTICE_2D_OFFSET_1 = 2 * sizeof(float);

    struct Vertices2D
    {
        Vertices2D( glm::vec2 vertexPosition, glm::vec2 textureCoordinates) noexcept
        {
            this->VertexPosition        = vertexPosition;
            this->TextureCoordinates    = textureCoordinates;
        }

        glm::vec2 VertexPosition;
        glm::vec2 TextureCoordinates;
    };

    struct Vertices3D
    {
        Vertices3D( glm::vec3 vertexPosition, glm::vec3 normalPosition, glm::vec2 textureCoordinate) noexcept
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