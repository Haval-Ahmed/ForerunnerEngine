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
#include <memory>

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "Vertices.h"

namespace ForerunnerEngine
{
    static constexpr uint32_t DEFAULT_CIRCLE_2D_SEGEMENTS = 360;

    class Rectangle2DPrimitiveData
    {
    public:

        static std::shared_ptr<Rectangle2DPrimitiveData> getInstance()
        {
            // Guaranteed to be destroyed and instantiated on first use.
            static std::shared_ptr<Rectangle2DPrimitiveData> instance { new Rectangle2DPrimitiveData };
            return instance;
        }

    private:

        Rectangle2DPrimitiveData()
        {
            // Size vectors and reserve necessary space
            Vertices.reserve(6);

            // Insert vertice data
            // -------------------------------------------------------------------------------

            // First Triangle
            Vertices.emplace_back(glm::vec2(1.0F, -1.0F),  glm::vec2(1.0F, 0.0F));
            Vertices.emplace_back(glm::vec2(-1.0F, -1.0F), glm::vec2(0.0F, 0.0F));
            Vertices.emplace_back(glm::vec2(-1.0F, 1.0F),  glm::vec2(0.0F, 1.0F));
            
            // Second triangle
            Vertices.emplace_back(glm::vec2(1.0F, -1.0F), glm::vec2(1.0F, 0.0F));
            Vertices.emplace_back(glm::vec2(-1.0F, 1.0F), glm::vec2(0.0F, 1.0F));
            Vertices.emplace_back(glm::vec2(1.0F, 1.0F),  glm::vec2(1.0F, 1.0F));
        }

    public:

        // C++ 11
        // =======
        // Delete copy constructor
        Rectangle2DPrimitiveData(Rectangle2DPrimitiveData const&) = delete;
        void operator=(Rectangle2DPrimitiveData const&) = delete;

    public:
        
        // Vertice data for rectangle
        std::vector<Vertices2D> Vertices;
    };

    class Triangle2DPrimitiveData
    {
    public:

        static std::shared_ptr<Triangle2DPrimitiveData> getInstance()
        {
            static std::shared_ptr<Triangle2DPrimitiveData> instance {new Triangle2DPrimitiveData };
            return instance;
        }

    private:

        Triangle2DPrimitiveData()
        {
            // Size vectors and reserve necessary space
            Vertices.reserve(3);

            // Insert vertice data
            // -------------------------------------------------------------------------------
            // Right
            Vertices.emplace_back(glm::vec2(1.0F, -1.0F), glm::vec2(1.0F, 0.0F));

            // Left
            Vertices.emplace_back(glm::vec2(-1.0F, -1.0F), glm::vec2(0.0F, 0.0F));

            // Top
            Vertices.emplace_back(glm::vec2(0.0F, 1.0F), glm::vec2(0.0F, 1.0F));
        }

    public:

        // C++ 11
        // =======
        // Delete copy constructor
        Triangle2DPrimitiveData(Triangle2DPrimitiveData const&) = delete;
        void operator=(Triangle2DPrimitiveData const&) = delete;

    public:

        // Vertice data
        std::vector<Vertices2D> Vertices;
    };

    class Pentagon2DPrimitiveData
    {

    public:

        static std::shared_ptr<Pentagon2DPrimitiveData> getInstance()
        {
            static std::shared_ptr<Pentagon2DPrimitiveData> instance { new Pentagon2DPrimitiveData };
            return instance;
        }

    private:
        Pentagon2DPrimitiveData()
        {
            // Size vectors and reserve necessary space
            Vertices.reserve(9);

            // Insert vertice data
            // -------------------------------------------------------------------------------

            // First triangle
            // 
            // Bottom Right
            Vertices.emplace_back(glm::vec2(0.5F, -1.0F), glm::vec2(0.75F, 0.0F));
            
            // Bottom Left
            Vertices.emplace_back(glm::vec2(-0.5F, -1.0F), glm::vec2(0.25F, 0.0F));

            // Top Left
            Vertices.emplace_back(glm::vec2(-1.0F, 0.0F), glm::vec2(0.0F, 0.5F));

            // Second Triangle
            // Bottom Right
            Vertices.emplace_back(glm::vec2(0.5F,-1.0F), glm::vec2(0.75F, 0.0F));

            // Top Left
            Vertices.emplace_back(glm::vec2(-1.0F, 0.0F), glm::vec2(0.0F, 0.5F));

            // Top Right
            Vertices.emplace_back(glm::vec2(1.0F, 0.0F), glm::vec2(1.0F, 0.5F));

            // Third Triangle
            // Top Right
            Vertices.emplace_back(glm::vec2(1.0F, 0.0F), glm::vec2(1.0F, 0.5F));

            // Top Left
            Vertices.emplace_back(glm::vec2(-1.0F, 0.0F), glm::vec2(0.0F, 0.5F));

            // Top Center
            Vertices.emplace_back(glm::vec2(0.0F, 1.0F), glm::vec2(0.5F, 1.0F));
        }

    public:

        // C++ 11
        // =======
        // Delete copy constructor
        Pentagon2DPrimitiveData(Pentagon2DPrimitiveData const&) = delete;
        void operator=(Pentagon2DPrimitiveData const&) = delete;

    public:

        // Vertice data
        std::vector<Vertices2D> Vertices;
    };

    class Circle2DPrimitiveData
    {

    public:

        static std::shared_ptr<Circle2DPrimitiveData> getInstance()
        {
            static std::shared_ptr<Circle2DPrimitiveData> instance { new Circle2DPrimitiveData };
            return instance;
        }

    private:
        Circle2DPrimitiveData()
        {
            // Size vectors and reserve necessary space
            Vertices.reserve(DEFAULT_CIRCLE_2D_SEGEMENTS);

            // Insert vertice data
            // -------------------------------------------------------------------------------
            for (size_t i = 0; i < 360; i++)
            {
                // Get x and y values (we want to be relative in upper range of (0, 0) -> (1, 1) for the circle)
                // This will allow easy uv mapping for the circle
                float x = cosf(glm::radians(static_cast<float>(i)));
                float y = sinf(glm::radians(static_cast<float>(i)));
                
                // Calculate the normal/uv for each vertice (get length of the vector and then divide by length if not 0)
                float uvX = x;
                float uvY = y;

                // Length of normal
                float uvLength = sqrt(x * x + y * y);

                // Check to ensure length is not zero
                if (glm::epsilonNotEqual(uvLength, 0.0F, glm::epsilon<float>()))
                {
                    uvX /= uvLength;
                    uvY /= uvLength;
                }

                Vertices.emplace_back(glm::vec2(x, y), glm::vec2(uvX, uvY));
            }
        }

    public:

        // C++ 11
        // =======
        // Delete copy constructor
        Circle2DPrimitiveData(Circle2DPrimitiveData const&) = delete;
        void operator=(Circle2DPrimitiveData const&) = delete;

    public:

        // Vertice data
        std::vector<Vertices2D> Vertices;
    };

    class HorizontalLine2DPrimitiveData
    {

    public:

        static std::shared_ptr<HorizontalLine2DPrimitiveData> getInstance()
        {
            static std::shared_ptr<HorizontalLine2DPrimitiveData> instance{ new HorizontalLine2DPrimitiveData };
            return instance;
        }

    private:

        HorizontalLine2DPrimitiveData()
        {
            // Size vectors and reserve necessary space
            Vertices.reserve(6);

            // Insert vertice data
            // -------------------------------------------------------------------------------

            // Bottom Right
            Vertices.emplace_back(glm::vec2(1.0F, -0.1F), glm::vec2(1.0F, 0.0F));

            // Bottom Left
            Vertices.emplace_back(glm::vec2(-1.0F, -0.1F), glm::vec2(0.0F, 0.0F));

            // Top Left
            Vertices.emplace_back(glm::vec2(-1.0F, 0.1F), glm::vec2(0.0F, 1.0F));

            // Bottom Right
            Vertices.emplace_back(glm::vec2(1.0F, -0.1F), glm::vec2(1.0F, 0.0F));

            // Top Left
            Vertices.emplace_back(glm::vec2(-1.0F, 0.1F), glm::vec2(0.0F, 1.0F));

            // Top Right
            Vertices.emplace_back(glm::vec2(1.0F, 0.1F), glm::vec2(1.0F, 1.0F));

        }

    public:

        // C++ 11
        // =======
        // Delete copy constructor
        HorizontalLine2DPrimitiveData(HorizontalLine2DPrimitiveData const&) = delete;
        void operator=(HorizontalLine2DPrimitiveData const&) = delete;

    public:

        // Vertice data
        std::vector<Vertices2D> Vertices;
    };

    class VerticalLine2DPrimitiveData
    {

    public:

        static std::shared_ptr<VerticalLine2DPrimitiveData> getInstance()
        {
            static std::shared_ptr<VerticalLine2DPrimitiveData> instance{ new VerticalLine2DPrimitiveData };
            return instance;
        }

    private:

        VerticalLine2DPrimitiveData()
        {
            // Size vectors and reserve necessary space
            Vertices.reserve(6);

            // Insert vertice data
            // -------------------------------------------------------------------------------

            // Bottom Right
            Vertices.emplace_back(glm::vec2(0.1F, -1.0F), glm::vec2(1.0F, 0.0F));

            // Bottom Left
            Vertices.emplace_back(glm::vec2(-0.1F, -1.0F), glm::vec2(0.0F, 0.0F));

            // Top Left
            Vertices.emplace_back(glm::vec2(-0.1F, 1.0F), glm::vec2(0.0F, 1.0F));

            // Bottom Right
            Vertices.emplace_back(glm::vec2(0.1F, -1.0F), glm::vec2(1.0F, 0.0F));

            // Top Left
            Vertices.emplace_back(glm::vec2(-0.1F, 1.0F), glm::vec2(0.0F, 1.0F));

            // Top Right
            Vertices.emplace_back(glm::vec2(0.1F, 1.0F), glm::vec2(1.0F, 1.0F));

        }

    public:

        // C++ 11
        // =======
        // Delete copy constructor
        VerticalLine2DPrimitiveData(VerticalLine2DPrimitiveData const&) = delete;
        void operator=(VerticalLine2DPrimitiveData const&) = delete;

    public:

        // Vertice data
        std::vector<Vertices2D> Vertices;
    };

    class Oval2DPrimitiveData
    {

    public:

        static std::shared_ptr<Oval2DPrimitiveData> getInstance()
        {
            static std::shared_ptr<Oval2DPrimitiveData> instance{ new Oval2DPrimitiveData };
            return instance;
        }

    private:

        Oval2DPrimitiveData()
        {
            // Size vectors and reserve necessary space
            Vertices.reserve(360);

            // Insert vertice data
            // -------------------------------------------------------------------------------
            for (int i = 0; i < 360; i++)
            {
                float x = 0.5F * cosf(glm::radians(static_cast<float>(i)));
                float y = sinf(glm::radians(static_cast<float>(i)));

                // Calculate the normal/uv for each vertice (get length of the vector and then divide by length if not 0)
                float uvX = x;
                float uvY = y;

                // Length of normal
                float uvLength = sqrt(x * x + y * y);

                // Check to ensure length is not zero
                if (glm::epsilonNotEqual(uvLength, 0.0F, glm::epsilon<float>()))
                {
                    uvX /= uvLength;
                    uvY /= uvLength;
                }

                Vertices.emplace_back(glm::vec2(x, y), glm::vec2(uvX, uvY));
            }
        }

    public:

        // C++ 11
        // =======
        // Delete copy constructor
        Oval2DPrimitiveData(Oval2DPrimitiveData const&) = delete;
        void operator=(Oval2DPrimitiveData const&) = delete;

    public:

        // Vertice data
        std::vector<Vertices2D> Vertices;
    };

    class Star2DPrimitiveData
    {

    public:

        static std::shared_ptr<Star2DPrimitiveData> getInstance()
        {
            static std::shared_ptr<Star2DPrimitiveData> instance{ new Star2DPrimitiveData };
            return instance;
        }

    private:

        Star2DPrimitiveData()
        {
            // Size vectors and reserve necessary space
            Vertices.reserve(4);

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
        }

    public:

        // C++ 11
        // =======
        // Delete copy constructor
        Star2DPrimitiveData(Star2DPrimitiveData const&) = delete;
        void operator=(Star2DPrimitiveData const&) = delete;

    public:

        // Vertice data
        std::vector<Vertices2D> Vertices;
    };
}

#endif