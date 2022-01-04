//////////////////////////////////////////////////////////////////////////
/// @File:
///     D3D11Scene.h
/// @Notes:
///     D3D11 Base Scene
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     See attached license 
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

#ifndef SCENE_H
#define SCENE_H

// Class/Function:
//		Scene
//
// DESCRIPTION:
//
//
// ARGUMENTS/PARAMETERS:
// 
// 
// RETURN VALUE:
//
//
// ERRORS:
//
//
// NOTES: 
class SCENE : public DirectX_Renderer
{
public:
	SCENE();
	virtual ~SCENE();
	
	// Update and Render Function
	void Update(float deltaTime);
	void Render(float deltaTime);

	// Game Engine Loop
	HRESULT engineLoop();

	// Configure DirectX
	HRESULT initializeApplication();
	HRESULT cleanDirect3D();

	// Load and Unload Content Functions
	void loadContent();
	void unLoadContent();

	// Initial Scene Management
	void initializeScene();

private:
	// Variable To Update Vertex Shader
	CBufferValues cValues;

	// Need a buffer for the constant updating variables inside vertex shader
	ID3D11Buffer* cBuffer;

	// Input Layout for shaders
	ID3D11InputLayout* inputLayout;

	// Need to store pixel and vertex shader
	ID3D11PixelShader* pixelShader;
	ID3D11VertexShader* vertexShader;

	// Indices and Vertices's Buffers
	ID3D11Buffer* indiceBuffer;
	ID3D11Buffer* vertexBuffer;

	// Index Counter
	UINT boxIndex;
	UINT pyramidIndex;

	// World, View, Projection Matrix
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;

	// Grid World Space
	DirectX::XMMATRIX gridWorldSpace;
	DirectX::XMMATRIX boxWorldSpace;
	DirectX::XMMATRIX pyramidWorldSpace;

	// Light Direction and Color
	DirectX::XMFLOAT4 lightDirection[3];
	DirectX::XMFLOAT4 lightColor[3];

	// OffSets for objects
	UINT boxVertexOffSet;
	UINT pyramidVertexOffSet;
	UINT boxIndexOffSet;
	UINT pyramidIndexOffSet;
	UINT totalVertexOffSet;
	UINT totalIndexOffSet;


	// Shaders Initialization
	void initializeShadersAndLayouts();
	void initializeDefaultLighting();
	void initializeDefaultSceneGeometry();
	void initializeDefaultCamera();
	void initializeWorldViewProjectionMatrix();
};


#endif
