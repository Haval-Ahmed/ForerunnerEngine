//////////////////////////////////////////////////////////////////////////
/// @File:
///     Camera.cpp
/// @Notes:
///     Base Camera Class
/// @Copyright:
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "Camera.h"

namespace ForerunnerEngine
{
    Camera::Camera() 
        : m_cameraYaw(YAW_DEFAULT)
        , m_cameraPitch(PITCH_DEFAULT)
        , m_cameraSpeed(SPEED_DEFAULT)
        , m_cameraSensitivity(SENSITIVITY_DEFAULT)
        , m_cameraZoomLevel(ZOOM_DEFAULT)
    {
        // Set the vectors y component to 1.0f
        m_worldUpDirection.setY(1.0f);

        // Update view matrix after initial configuration
        this->updateViewMatrix();
    }

    FRMath::Matrix4x4 Camera::getViewMatrix()
    {
        return FRMath::getLookAtRightHandMatrix(m_cameraPosition, m_cameraPosition + m_frontVector, m_upVector);
    }

    void Camera::setCameraSpeed(float cameraSpeed)
    {
        m_cameraSpeed = cameraSpeed;
    }

    void Camera::setCameraSensitivity(float cameraSensitivity)
    {
        m_cameraSensitivity = cameraSensitivity;
    }

    float Camera::getCameraSpeed(void)
    {
        return m_cameraSpeed;
    }

    float Camera::getCameraSensitivity(void)
    {
        return m_cameraSensitivity;
    }

    void Camera::updateViewMatrix(void)
    {
        // Calculate the front, right, and up vectors for a view matrix
        FRMath::Vector3D frontVector;

        // Specify rotation angles
        frontVector.setX(cosf(FRMath::DegreesToRadians(m_cameraYaw)) * cosf(FRMath::DegreesToRadians(m_cameraPitch)));
        frontVector.setY(sinf(FRMath::DegreesToRadians(m_cameraPitch)));
        frontVector.setZ(sinf(FRMath::DegreesToRadians(m_cameraYaw)) * cosf(FRMath::DegreesToRadians(m_cameraPitch)));

        // Normalize 
        frontVector.normalize();

        // Set calculated vector to class front vector
        m_frontVector = frontVector;

        // Recalculate right and up vectors
        m_rightVector  = FRMath::cross(m_frontVector, m_worldUpDirection);
        m_upVector     = FRMath::cross(m_rightVector, m_frontVector);

        // Normalize vectors
        m_rightVector.normalize();
        m_upVector.normalize();
    }
}