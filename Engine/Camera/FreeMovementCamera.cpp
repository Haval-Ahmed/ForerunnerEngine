//////////////////////////////////////////////////////////////////////////
/// @File:
///     FreeMovementCamera.cpp
/// @Notes:
///     FreeMovement Camera Class
/// @Copyright:
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "FreeMovementCamera.h"

namespace ForerunnerEngine
{
    FreeMovementCamera::FreeMovementCamera() : Camera()
    {
        // Empty constructor
    }

    void FreeMovementCamera::updateCameraAngle(float yawOffset, float pitchOffset)
    {
        yawOffset   *= m_cameraSensitivity;
        pitchOffset *= m_cameraSensitivity;

        m_cameraYaw    += yawOffset;
        m_cameraPitch  += pitchOffset;

        if (m_cameraPitch > 89.0f)
        {
            m_cameraPitch = 89.0f;
        }

        if (m_cameraPitch < -89.0f)
        {
            m_cameraPitch = -89.0f;
        }

        this->updateViewMatrix();
    }

    void FreeMovementCamera::updateCameraZoomLevel(float yOffset)
    {
        if (m_cameraZoomLevel >= 1.0f && m_cameraZoomLevel <= 45.0f)
        {
            m_cameraZoomLevel -= yOffset;
        }

        if (m_cameraZoomLevel <= 1.0f)
        {
            m_cameraZoomLevel = 1.0f;
        }

        if (m_cameraZoomLevel >= 45.0f)
        {
            m_cameraZoomLevel = 45.0f;
        }
    }

    void FreeMovementCamera::updateCameraPosition(CAMERA_MOVEMENT direction, double deltaTime)
    {
        float cameraVelocity = m_cameraSpeed * static_cast<float>(deltaTime);

        // Check for z axis movement
        if (direction == CAMERA_MOVEMENT::FORWARD)
        {
            m_cameraPosition += m_frontVector * cameraVelocity;
        }
        else if (direction == CAMERA_MOVEMENT::BACKWARD)
        {
            m_cameraPosition -= m_frontVector * cameraVelocity;
        }

        if (direction == CAMERA_MOVEMENT::LEFT)
        {
            m_cameraPosition -= m_rightVector * cameraVelocity;
        }
        else if (direction == CAMERA_MOVEMENT::RIGHT)
        {
            m_cameraPosition += m_rightVector * cameraVelocity;
        }

        if (direction == CAMERA_MOVEMENT::UP)
        {
            m_cameraPosition += m_upVector * cameraVelocity;
        }
        else if (direction == CAMERA_MOVEMENT::DOWN)
        {
            m_cameraPosition -= m_upVector * cameraVelocity;
        }
    }
}
