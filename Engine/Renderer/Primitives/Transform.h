/// @file Transform.h
/// @brief Defines a transform object
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef TRANSFORM_H
#define TRANSFORM_H

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <cstdint>

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
            this->Position                  = glm::vec3(0.0F);
            this->Scale                     = glm::vec3(0.0F);
            this->Rotation                  = glm::vec3(0.0F);
            this->RotationAngle             = 0.0F;
            this->ModelMatrix               = glm::mat4(1.0F);
            this->UpdatePositionThisFrame   = 0;
            this->UpdateScaleThisFrame      = 0;
            this->UpdateRotationThisFrame   = 0;
        }

        Transform(  glm::vec3 position,
                    glm::vec3 scale,
                    glm::vec3 rotation)
        {
            this->Position                  = position;
            this->Scale                     = scale;
            this->Rotation                  = rotation;
            this->RotationAngle             = 0.0F;
            this->ModelMatrix               = glm::mat4(1.0F);
            this->UpdatePositionThisFrame   = 0;
            this->UpdateScaleThisFrame      = 0;
            this->UpdateRotationThisFrame   = 0;
        }

        // Position, Scale, and Rotation variables
        glm::vec3   Position;
        glm::vec3   Scale;
        glm::vec3   Rotation;
        float       RotationAngle;

        // SRT = Scale -> Rotate -> Translate 
        // In OpenGL -> Translate -> Rotate -> Scale due to matrix order (Column Major vs Row Major)
        glm::mat4   ModelMatrix;

        // Variables to indicate whether we apply a translation, scale, or rotation
        uint32_t    UpdatePositionThisFrame;
        uint32_t    UpdateScaleThisFrame;
        uint32_t    UpdateRotationThisFrame;
    };
}

#endif