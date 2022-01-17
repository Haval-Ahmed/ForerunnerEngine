/// @file PrimitiveData.h
/// @brief Defines a primitive data struct that contains vertice information
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef PRIMITIVEDATA2D_H
#define PRIMITIVEDATA2D_H

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
    struct PrimitiveData2D
    {
        std::vector<Vertices2D> Vertices;
        std::vector<uint32_t> Indices;
    };

    struct Rectangle2DPrimitiveData : public PrimitiveData2D
    {
        Rectangle2DPrimitiveData() : PrimitiveData2D()
        {
            // Size vectors and reserve necessary space
            Vertices.reserve(4);
            Indices.reserve(6);

            // Insert vertice data
            // -------------------------------------------------------------------------------

            // Top Right
            Vertices.emplace_back(glm::vec2(0.5F, 0.5F), glm::vec2(1.0F, 1.0F));

            // Bottom Right
            Vertices.emplace_back(glm::vec2(0.5F, -0.5F), glm::vec2(1.0F, 0.0F));

            // Bottom Left
            Vertices.emplace_back(glm::vec2(-0.5F, -0.5F), glm::vec2(0.0F, 0.0F));

            // Top Left
            Vertices.emplace_back(glm::vec2(-0.5F, 0.5F), glm::vec2(0.0F, 1.0F));

            // First triangle
            Indices.emplace_back(0);
            Indices.emplace_back(1);
            Indices.emplace_back(3);

            // Second triangle
            Indices.emplace_back(1);
            Indices.emplace_back(2);
            Indices.emplace_back(3);
        }
    };
}

#endif