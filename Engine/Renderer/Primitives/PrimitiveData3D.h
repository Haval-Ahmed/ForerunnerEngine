/// @file PrimitiveData3D.h
/// @brief Defines a primitive 3d data
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef PRIMITIVEDATA3D_H
#define PRIMITIVEDATA3D_H

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <vector>

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "Vertices.h"

namespace ForerunnerEngine
{
    namespace ForerunnerRenderer
    {
        struct PrimitiveData3D
        {
            std::vector<Vertices3D> Vertices;
            std::vector<uint32_t> Indices;
        };

        struct CubePrimitiveData : public PrimitiveData3D
        {
            CubePrimitiveData() : PrimitiveData3D()
            {
                // Will use X, Y, Z to specifiy (1, 1, 1);
                float x = 0.5F;
                float y = 0.5F;
                float z = 0.5F;

                // Primative has 24 vertices and 36 indices
                Vertices.reserve(24);
                Indices.reserve(36);

                // Front Face
                Vertices.emplace_back(glm::vec3(-x, -y, z), glm::vec3(0.0F, 0.0F, 1.0F), glm::vec2(0.0F, 0.0F));
                Vertices.emplace_back(glm::vec3(-x, y, z),  glm::vec3(0.0F, 0.0F, 1.0F), glm::vec2(0.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(x, y, z),   glm::vec3(0.0F, 0.0F, 1.0F), glm::vec2(1.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(x, -y, z),  glm::vec3(0.0F, 0.0F, 1.0F), glm::vec2(1.0F, 0.0F));

                // Back Face
                Vertices.emplace_back(glm::vec3(-x, -y, -z),  glm::vec3(0.0F, 0.0F, -1.0F),  glm::vec2(1.0F, 0.0F));
                Vertices.emplace_back(glm::vec3(-x, y, -z),   glm::vec3(0.0F, 0.0F, -1.0F),  glm::vec2(1.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(x, y, -z),    glm::vec3(0.0F, 0.0F, -1.0F),  glm::vec2(0.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(x, -y, -z),   glm::vec3(0.0F, 0.0F, -1.0F),  glm::vec2(0.0F, 0.0F));

                // Top Face
                Vertices.emplace_back(glm::vec3(-x, y, -z), glm::vec3(0.0F, 1.0F, 0.0F), glm::vec2(0.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(-x, y, z),  glm::vec3(0.0F, 1.0F, 0.0F), glm::vec2(0.0F, 0.0F));
                Vertices.emplace_back(glm::vec3(x, y, z),   glm::vec3(0.0F, 1.0F, 0.0F), glm::vec2(1.0F, 0.0F));
                Vertices.emplace_back(glm::vec3(x, y, -z),  glm::vec3(0.0F, 1.0F, 0.0F), glm::vec2(1.0F, 1.0F));

                // Bottom Face
                Vertices.emplace_back(glm::vec3(-x, -y, -z),  glm::vec3(0.0F, -1.0F, 0.0F), glm::vec2(0.0F, 0.0F));
                Vertices.emplace_back(glm::vec3(-x, -y, z),   glm::vec3(0.0F, -1.0F, 0.0F), glm::vec2(0.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(x, -y, z),    glm::vec3(0.0F, -1.0F, 0.0F), glm::vec2(1.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(x, -y, -z),   glm::vec3(0.0F, -1.0F, 0.0F), glm::vec2(1.0F, 0.0F));

                // Left Face
                Vertices.emplace_back(glm::vec3(-x, -y, z),   glm::vec3(-1.0F, 0.0F, 0.0F), glm::vec2(1.0F, 0.0F));
                Vertices.emplace_back(glm::vec3(-x, y, z),    glm::vec3(-1.0F, 0.0F, 0.0F), glm::vec2(1.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(-x, y, -z),   glm::vec3(-1.0F, 0.0F, 0.0F), glm::vec2(0.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(-x, -y, -z),  glm::vec3(-1.0F, 0.0F, 0.0F), glm::vec2(0.0F, 0.0F));

                // Right Face
                Vertices.emplace_back(glm::vec3(x, -y, -z), glm::vec3(1.0F, 0.0F, 0.0F), glm::vec2(1.0F, 0.0F));
                Vertices.emplace_back(glm::vec3(x, y, -z),  glm::vec3(1.0F, 0.0F, 0.0F), glm::vec2(1.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(x, y, z),   glm::vec3(1.0F, 0.0F, 0.0F), glm::vec2(0.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(x, -y, z),  glm::vec3(1.0F, 0.0F, 0.0F), glm::vec2(0.0F, 0.0F));
                
                // front face index data
                Indices.emplace_back(0);
                Indices.emplace_back(1);
                Indices.emplace_back(2);
                Indices.emplace_back(0);
                Indices.emplace_back(2);
                Indices.emplace_back(3);

                // back face index data
                Indices.emplace_back(4);
                Indices.emplace_back(5);
                Indices.emplace_back(6);
                Indices.emplace_back(4);
                Indices.emplace_back(6);
                Indices.emplace_back(7);

                // top face index data
                Indices.emplace_back(8);
                Indices.emplace_back(9);
                Indices.emplace_back(10);
                Indices.emplace_back(8);
                Indices.emplace_back(10);
                Indices.emplace_back(11);

                // bottom face index data
                Indices.emplace_back(12);
                Indices.emplace_back(13);
                Indices.emplace_back(14);
                Indices.emplace_back(12);
                Indices.emplace_back(14);
                Indices.emplace_back(15);

                // left face index data
                Indices.emplace_back(16);
                Indices.emplace_back(17);
                Indices.emplace_back(18);
                Indices.emplace_back(16);
                Indices.emplace_back(18);
                Indices.emplace_back(19);

                // right face index data
                Indices.emplace_back(20);
                Indices.emplace_back(21);
                Indices.emplace_back(22);
                Indices.emplace_back(20);
                Indices.emplace_back(22);
                Indices.emplace_back(23);
            }
        };

        struct PyramidPrimitiveData : public PrimitiveData3D
        {
            PyramidPrimitiveData() : PrimitiveData3D()
            {
                // Will use X, Y, Z to specifiy (1, 1, 1);
                float x = 0.5F;
                float y = 0.5F;
                float z = 0.5F;

                // Primative has 5 vertices and 18 indices
                Vertices.reserve(5);
                Indices.reserve(18);

                // Bottom Face
                Vertices.emplace_back(glm::vec3(-x, 0.0F, -z), glm::vec3(0.0F, -1.0F, 0.0F), glm::vec2(0.0F, 1.0F));
                Vertices.emplace_back(glm::vec3(-x, 0.0F, z), glm::vec3(0.0F, -1.0F, 0.0F), glm::vec2(0.0F, 0.0F));
                Vertices.emplace_back(glm::vec3(x, 0.0F, z), glm::vec3(0.0F, -1.0F, 0.0F), glm::vec2(1.0F, 0.0F));
                Vertices.emplace_back(glm::vec3(x, 0.0F, -z), glm::vec3(0.0F, -1.0F, 0.0F), glm::vec2(1.0F, 1.0F));

                // Main/Side Face
                Vertices.emplace_back(glm::vec3(0.0F, y, 0.0F), glm::vec3(0.0F, 0.0F, 1.0F), glm::vec2(0.5F, 1.0F));

                // Bottom Base
                Indices.emplace_back(0);
                Indices.emplace_back(1);
                Indices.emplace_back(2);

                Indices.emplace_back(0);
                Indices.emplace_back(2);
                Indices.emplace_back(3);

                // Front Side
                Indices.emplace_back(1);
                Indices.emplace_back(4);
                Indices.emplace_back(2);

                // Back Side
                Indices.emplace_back(0);
                Indices.emplace_back(4);
                Indices.emplace_back(3);

                // Left side
                Indices.emplace_back(1);
                Indices.emplace_back(4);
                Indices.emplace_back(0);

                // Right Side
                Indices.emplace_back(3);
                Indices.emplace_back(4);
                Indices.emplace_back(2);
            }
        };
    }
}

#endif