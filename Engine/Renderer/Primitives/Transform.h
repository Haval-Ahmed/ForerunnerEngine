/// @file Transform.h
/// @brief Defines a transform object
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef TRANSFORM_H
#define TRANSFORM_H

//////////////////////////////////////////////////////////////////////////
/// Math Libraries
//////////////////////////////////////////////////////////////////////////
#include "FRMath.h"

namespace ForerunnerEngine
{
    struct Transform
    {
        Transform()
        {
            this->Position  = glm::vec3(0.0f);
            this->Scale     = glm::vec3(0.0f);
            this->Rotation  = glm::vec3(0.0f);

            // Set model matrix to identity matrix
            this->ModelMatrix = glm::mat4(1.0f);
        }

        Transform(  glm::vec3 position,
                    glm::vec3 scale,
                    glm::vec3 rotation)
        {
            this->Position  = position;
            this->Scale     = scale;
            this->Rotation  = rotation;

            // Set model matrix to identity matrix
            this->ModelMatrix = glm::mat4(1.0f);
        }

        glm::vec3 Position;
        glm::vec3 Scale;
        glm::vec3 Rotation;
        glm::mat4 ModelMatrix;
    };
}

#endif