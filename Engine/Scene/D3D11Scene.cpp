#include "Scene.h"


SCENE::SCENE()
{
	lightDirection[0] = DirectX::XMFLOAT4(-0.577f, 0.577f, -0.577f, 1.0f);
	lightDirection[1] = DirectX::XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f);
	lightDirection[2] = DirectX::XMFLOAT4(0.577f, 0.577f, -0.55f, 1.0f);

	lightColor[0] = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	lightColor[1] = DirectX::XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
	lightColor[2] = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

	// Set World Space
	boxWorldSpace = DirectX::XMMatrixTranslation(-3.0f, 1.0f, 1.0f);
	pyramidWorldSpace = DirectX::XMMatrixTranslation(3.0f, 1.0f, 1.0f);
}

SCENE::~SCENE()
{

}

/************************************************************************/
/*
Method: engineLoop
Note:
Inputs:
Outputs:
Parameters
Return Value:
Notes:
Errors:
*/
/************************************************************************/
HRESULT SCENE::engineLoop()
{
	// Game/Main Message Loop
	// Initialize Message As 0
	MSG currentMessage = { 0 };

	// Reset Timer
	engineTimer.reset();

	// Loop Until We Get A Quit Message
	while (WM_QUIT != currentMessage.message)
	{
		// Peek To See the Next Message. If An Event Happens, Translate and Dispatch Message else we will call our Update and Render Functions
		if (PeekMessage(&currentMessage, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&currentMessage);
			DispatchMessage(&currentMessage);
		}
		else
		{
			// Start Counting
			engineTimer.count();

			// Check if Paused
			if (!enginePaused)
			{
				// Display FPS
				fpsCounter();
				// Update and Render
				Update(engineTimer.getDeltaTime());
				Render(engineTimer.getDeltaTime());
			}
			else
			{
				// Put To Sleep
				Sleep(100);
			}
		}
	}

	// Clean up Direct3D Devices when completed
	cleanDirect3D();

	return (int)currentMessage.wParam;
}


/************************************************************************/
/*
Method: Update
Inputs:
Outputs:
Parameters
Return Value:
Notes:
Errors:
*/
/************************************************************************/
void SCENE::Update(float deltaTime)
{
	// Update World, View, Projection Matrix
	/*cValues.world = DirectX::XMMatrixTranspose(worldMatrix);
	cValues.view = DirectX::XMMatrixTranspose(viewMatrix);
	cValues.projection = DirectX::XMMatrixTranspose(projectionMatrix);
	// Update Sub Resource
	direct3DDeviceContext->UpdateSubresource(cBuffer, 0, nullptr, &cValues, 0, 0);*/
}

/************************************************************************/
/*
Method: Render
Inputs:
Outputs:
Parameters
Return Value:
Notes:
Errors:
*/
/************************************************************************/
void SCENE::Render(float deltaTime)
{
	// Clear Render and Target View
	direct3DDeviceContext->ClearRenderTargetView(renderTargetView, DirectX::Colors::Blue);
	direct3DDeviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

	// Set input assembler input layout
	direct3DDeviceContext->IASetInputLayout(inputLayout);

	// Set Topology
	direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Draw Box
	// Update World, View, Projection Matrix
	cValues.world = DirectX::XMMatrixTranspose(boxWorldSpace);
	cValues.view = DirectX::XMMatrixTranspose(viewMatrix);
	cValues.projection = DirectX::XMMatrixTranspose(projectionMatrix);
	cValues.lightDirection[0] = lightDirection[0];
	cValues.lightDirection[1] = lightDirection[1];
	cValues.lightDirection[2] = lightDirection[2];
	cValues.lightColor[0] = lightColor[0];
	cValues.lightColor[1] = lightColor[1];
	cValues.lightColor[2] = lightColor[2];
	// Update Sub Resource
	direct3DDeviceContext->UpdateSubresource(cBuffer, 0, nullptr, &cValues, 0, 0);
	direct3DDeviceContext->VSSetConstantBuffers(0, 1, &cBuffer);
	direct3DDeviceContext->PSSetConstantBuffers(0, 1, &cBuffer);
	direct3DDeviceContext->DrawIndexed(boxIndex, boxIndexOffSet, boxVertexOffSet);

	// Draw Pyramid
	// Update World, View, Projection Matrix
	cValues.world = DirectX::XMMatrixTranspose(pyramidWorldSpace);
	cValues.view = DirectX::XMMatrixTranspose(viewMatrix);
	cValues.projection = DirectX::XMMatrixTranspose(projectionMatrix);
	cValues.lightDirection[0] = lightDirection[0];
	cValues.lightDirection[1] = lightDirection[1];
	cValues.lightDirection[2] = lightDirection[2];
	cValues.lightColor[0] = lightColor[0];
	cValues.lightColor[1] = lightColor[1];
	cValues.lightColor[2] = lightColor[2];
	// Update Sub Resource
	direct3DDeviceContext->UpdateSubresource(cBuffer, 0, nullptr, &cValues, 0, 0);
	direct3DDeviceContext->VSSetConstantBuffers(0, 1, &cBuffer);
	direct3DDeviceContext->PSSetConstantBuffers(0, 1, &cBuffer);
	direct3DDeviceContext->DrawIndexed(pyramidIndex, pyramidIndexOffSet, pyramidVertexOffSet);
	
	// Swap The Buffers
	swapChain->Present(0, 0);
}


/************************************************************************/
/*
Method: Load Content
Inputs:
Outputs:
Parameters
Return Value:
Notes:
Errors:
*/
/************************************************************************/
HRESULT SCENE::initializeApplication()
{
	// Initialize Window, Device and Device Context, Swap Chain, and Render Target Views
	DirectX_Renderer::createApplicationWindow();
	DirectX_Renderer::initializeDirect3DDevices();
	DirectX_Renderer::initializeDirect3DResources();
	DirectX_Renderer::direct3DConfiguration();

	return S_OK;
}

/************************************************************************/
/*
Method: cleanDirect3D
Inputs:
Outputs:
Parameters
Return Value:
Notes:
Errors:
*/
/************************************************************************/
HRESULT SCENE::cleanDirect3D()
{
	vertexShader->Release();
	pixelShader->Release();
	depthStencilBuffer->Release();
	renderTargetView->Release();
	swapChain->Release();
	direct3DDeviceContext->Release();
	direct3DDevice->Release();

	return S_OK;
}

/************************************************************************/
/*
Method: Load Content
Inputs:
Outputs:
Parameters
Return Value:
Notes:
Errors:
*/
/************************************************************************/
void SCENE::loadContent()
{

}

/************************************************************************/
/*
Method: Unload Content
Inputs:
Outputs:
Parameters
Return Value:
Notes:
Errors:
*/
/************************************************************************/
void SCENE::unLoadContent()
{

}


/************************************************************************/
/*
Method: createSceneDevices
Inputs:
Outputs:
Parameters
Return Value:
Notes:
Errors:
*/
/************************************************************************/
void SCENE::initializeScene()
{
	// 1. Need to build the geometry
	// 2. Read in complied shaders and set input vertex data
	// 3. Create the view and perspective matrix
	initializeDefaultSceneGeometry();
	initializeShadersAndLayouts();
	initializeWorldViewProjectionMatrix();
}

/************************************************************************/
/*
Method: initializeDefaultShaders
Inputs:
Outputs:
Parameters
Return Value:
Notes:
Errors:
*/
/************************************************************************/
void SCENE::initializeShadersAndLayouts()
{
	// Open shader files
	std::ifstream vertexFile;
	std::ifstream pixelFile;

	// Open Files
	vertexFile.open(".\\x64\\Debug\\defaultVertexShader.cso", std::ios::binary);
	pixelFile.open(".\\x64\\Debug\\defaultPixelShader.cso", std::ios::binary);

	// Get Length of both files
	vertexFile.seekg(0, vertexFile.end);
	size_t vertexLength = vertexFile.tellg();
	vertexFile.seekg(0, vertexFile.beg);
	pixelFile.seekg(0, pixelFile.end);
	size_t pixelLength = pixelFile.tellg();
	pixelFile.seekg(0, pixelFile.beg);

	// Create a BYTE Array for both the vertex and pixel shader
	char* vertexByte = new char[vertexLength];
	char* pixelByte = new char[pixelLength];

	// Read byteCode from Vertex Shader and Pixel Shader
	vertexFile.read(vertexByte, vertexLength);
	pixelFile.read(pixelByte, pixelLength);

	// Create Vertex Shader
	direct3DDevice->CreateVertexShader(vertexByte, vertexLength, nullptr, &vertexShader);
	// Create Pixel Shader
	direct3DDevice->CreatePixelShader(pixelByte, pixelLength, nullptr, &pixelShader);

	// Set Vertex and Pixel Shader
	direct3DDeviceContext->VSSetShader(vertexShader, nullptr, 0);
	direct3DDeviceContext->PSSetShader(pixelShader, nullptr, 0);

	// Create Input Element
	D3D11_INPUT_ELEMENT_DESC vertexInput[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	// Input length
	UINT inputLength = ARRAYSIZE(vertexInput);

	// Create input layer
	direct3DDevice->CreateInputLayout(vertexInput, inputLength, vertexByte, vertexLength, &inputLayout);
	

	// Create cBuffer Desc
	D3D11_BUFFER_DESC cBufferDesc;
	cBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	cBufferDesc.ByteWidth = sizeof(CBufferValues);
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = 0;
	cBufferDesc.MiscFlags = 0;
	// Create Buffer
	direct3DDevice->CreateBuffer(&cBufferDesc, nullptr, &cBuffer);

	// Set constant buffer
	direct3DDeviceContext->VSSetConstantBuffers(0, 1, &cBuffer);

	// Delete vertexByte and pixelByte arrays
	// delete vertexByte;
	// delete pixelByte;

	// Close files
	vertexFile.close();
	pixelFile.close();
}

/************************************************************************/
/*
Method: initializeDefaultLighting
Inputs:
Outputs:
Parameters
Return Value:
Notes:
Errors:
*/
/************************************************************************/
void SCENE::initializeDefaultLighting()
{
	
}

/************************************************************************/
/*
Method: initializeDefaultSceneGeometry
Inputs:
Outputs:
Parameters
Return Value:
Notes: Each geometric object requires indexCount, vertexOffSet, and indexOffSet
		Then need to total all the indices and vertex for buffers
Errors:
*/
/************************************************************************/
void SCENE::initializeDefaultSceneGeometry()
{
	HRESULT result;

	/*
	Default Scene Geometry. Generate Objects and Bind to vertex and index buffers
	*/

	// Create Box
	geometricMesh boxMesh;
	// Create Pyramid
	geometricMesh pyramidMesh;
	// Function Calls
	generateGeometricBox(1, boxMesh);
	generateGeometricPyramid(1, pyramidMesh);
	// Grab index count for each object
	boxIndex = boxMesh.indiceInformation.size();
	pyramidIndex = pyramidMesh.indiceInformation.size();
	// Calculate Vertex Offsets for each object
	boxVertexOffSet = 0;
	pyramidVertexOffSet = boxMesh.verticeInformation.size();
	// Calculate Index Offsets
	boxIndexOffSet = 0;
	pyramidIndexOffSet = boxMesh.indiceInformation.size();
	// Total Vertex Offset
	totalVertexOffSet = boxMesh.verticeInformation.size() + pyramidMesh.verticeInformation.size();
	// Total Index Offset
	totalIndexOffSet = boxMesh.indiceInformation.size() + pyramidMesh.indiceInformation.size();
	// Create one large mesh for objects
	std::vector<ShapesVertex> allVertices;
	std::vector<UINT> allIndices;
	// Store All meshes inside
	allVertices.insert(allVertices.end(), boxMesh.verticeInformation.begin(), boxMesh.verticeInformation.end());
	allVertices.insert(allVertices.end(), pyramidMesh.verticeInformation.begin(), pyramidMesh.verticeInformation.end());
	allIndices.insert(allIndices.end(), boxMesh.indiceInformation.begin(), boxMesh.indiceInformation.end());
	allIndices.insert(allIndices.end(), pyramidMesh.indiceInformation.begin(), pyramidMesh.indiceInformation.end());

	// Create Vertex and Index Buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(ShapesVertex) * allVertices.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	// Create Subsystem Resource
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = &allVertices[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Create Buffer
	result = direct3DDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

	// Update the IA Stage with the input and layout
	UINT stride = sizeof(ShapesVertex);
	UINT offset = 0;

	// Set Vertex Buffer
	direct3DDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// Create Buffer for Indices
	D3D11_BUFFER_DESC indiceBufferDesc;
	indiceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indiceBufferDesc.ByteWidth = sizeof(UINT) * allIndices.size(); // Might need size of vertex again
	indiceBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indiceBufferDesc.CPUAccessFlags = 0;
	indiceBufferDesc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = &allIndices[0];
	// Create Buffer
	result = direct3DDevice->CreateBuffer(&indiceBufferDesc, &indexData, &indiceBuffer);

	// Set Index Buffer
	direct3DDeviceContext->IASetIndexBuffer(indiceBuffer, DXGI_FORMAT_R32_UINT, 0);
}

/************************************************************************/
/*
Method: initializeDefaultCamera
Inputs:
Outputs:
Parameters
Return Value:
Notes:
Errors:
*/
/************************************************************************/
void SCENE::initializeDefaultCamera()
{
	
}

void SCENE::initializeWorldViewProjectionMatrix()
{
	// Create World View
	worldMatrix = DirectX::XMMatrixIdentity();

	// Create view matrix
	DirectX::XMVECTOR eyePosition = DirectX::XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	DirectX::XMVECTOR targetPosition = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR upDirection = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Store View Matrix
	viewMatrix = DirectX::XMMatrixLookAtLH(eyePosition, targetPosition, upDirection);

	// Create Projection Matrix
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, windowAspectRatio(), 0.01f, 100.0f);
}