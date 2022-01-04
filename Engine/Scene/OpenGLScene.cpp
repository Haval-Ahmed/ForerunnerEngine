//////////////////////////////////////////////////////////////////////////
/// @File:
///     OpenGLScene.cpp
/// @Notes:
///     OpenGL base scene class
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     See attached license 
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "OpenGLScene.h"

namespace ForerunnerEngine
{
	OpenGLScene::OpenGLScene(OpenGLRenderer* renderer)
		: mRenderer(renderer)
		, mIsSceneLoaded(0)
		, mIsSceneCompleted(0)
	{
		mProjectionMatrix = FRMath::getPerspectiveMatrix(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
	}

	OpenGLScene::~OpenGLScene()
	{
		
	}

	void OpenGLScene::update(double deltaTime)
	{
		/// W 
		if (::GetAsyncKeyState(0x57))
		{
			mCamera.updateCameraPosition(ForerunnerEngine::CAMERA_MOVEMENT::FORWARD, deltaTime);
		}
		/// S
		else if (::GetAsyncKeyState(0x53))
		{
			mCamera.updateCameraPosition(ForerunnerEngine::CAMERA_MOVEMENT::BACKWARD, deltaTime);
		}

		/// A
		if (::GetAsyncKeyState(0x41) || ::GetAsyncKeyState(VK_LEFT))
		{
			mCamera.updateCameraPosition(ForerunnerEngine::CAMERA_MOVEMENT::LEFT, deltaTime);
		}
		/// D
		else if (::GetAsyncKeyState(0x44) || ::GetAsyncKeyState(VK_RIGHT))
		{
			mCamera.updateCameraPosition(ForerunnerEngine::CAMERA_MOVEMENT::RIGHT, deltaTime);
		}

		// Up or down
		if (::GetAsyncKeyState(VK_UP))
		{
			mCamera.updateCameraPosition(ForerunnerEngine::CAMERA_MOVEMENT::UP, deltaTime);
		}
		else if (::GetAsyncKeyState(VK_DOWN))
		{
			mCamera.updateCameraPosition(ForerunnerEngine::CAMERA_MOVEMENT::DOWN, deltaTime);
		}

		// Left or rig
	}

	void OpenGLScene::render(double deltaTime)
	{
		/// Clear Color and depth buffer
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mPrimativeManager.draw(mProjectionMatrix, mCamera.getViewMatrix());

		// Swap buffers
		mRenderer->presentAndSwapBuffers();
	}

	void OpenGLScene::loadScene(void)
	{
		mPrimativeManager.getShader().useShader();
		mPrimativeManager.createCube();
		mPrimativeManager.getShader().disableShader();
	}

    uint32_t OpenGLScene::isSceneLoaded(void)
    {
        return mIsSceneLoaded;
    }

	uint32_t OpenGLScene::isSceneComplete(void)
	{
		return mIsSceneCompleted;
	}

	void OpenGLScene::unloadScene(void)
	{

	}

	void OpenGLScene::initializeScene(void)
	{

	}

	void OpenGLScene::initializeShadersAndLayouts(void)
	{

	}

	void OpenGLScene::initializeLighting(void)
	{

	}

	void OpenGLScene::initializeSceneGeometry(void)
	{

	}

	void OpenGLScene::initializeCamera(void)
	{

	}

	void OpenGLScene::initializeWorldViewProjectionMatrix(void)
	{

	}
}
