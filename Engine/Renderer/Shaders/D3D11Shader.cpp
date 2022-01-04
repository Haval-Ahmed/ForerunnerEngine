//////////////////////////////////////////////////////////////////////////
/// @File:
///     FRD3D11Render.cpp
/// @Modification:
///     1/7/18 - Haval-Ahmed
/// @Notes:
///     Base renderer class for the Forerunner Engine. 
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// User Defined Library Files
//////////////////////////////////////////////////////////////////////////
#include "D3D11Shader.h"

namespace ForerunnerEngine
{
    D3D11Shader::D3D11Shader(ID3D11Device* direct3DDevice, ID3D11DeviceContext* direct3DDeviceContext)
        : BaseShader()
        , mDirect3DDevice(direct3DDevice)
        , mDirect3DDeviceContext(direct3DDeviceContext)
    {
        memset(mVertexShaderLog, 0,     sizeof(mVertexShaderLog));
        memset(mFragmentShaderLog, 0,   sizeof(mFragmentShaderLog));
    }

    void D3D11Shader::createVertexShader(const char* shaderString)
    {
        // Create Vertex Shader
        mDirect3DDevice->CreateVertexShader(shaderString, sizeof(shaderString), nullptr, &mVertexShader);

        // Set vertex shader
        mDirect3DDeviceContext->VSSetShader(mVertexShader, nullptr, 0);

        // Create Input Element
        D3D11_INPUT_ELEMENT_DESC vertexInput[] =
        {
            {"POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXTURE",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, }
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
    }

    void D3D11Shader::createFragmentPixelShader(const char* shaderString)
    {
        // Create Vertex Shader
        mDirect3DDevice->CreateVertexShader(shaderString, sizeof(shaderString), nullptr, &mVertexShader);

        // Create Pixel Shader
        direct3DDevice->CreatePixelShader(pixelByte, pixelLength, nullptr, &mPixelShader);

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
    }

    void D3D11Shader::loadShaderFromFile(const char* shaderPath, unsigned int shaderType)
    {

    }

    void D3D11Shader::useShader(void)
    {
        mDirect3DDeviceContext->VSSetShader(mVertexShader, nullptr, 0);
        mDirect3DDeviceContext->PSSetShader(mPixelShader, nullptr, 0);
    }

    void D3D11Shader::disableShader(void)
    {

    }

    void D3D11Shader::setUniform(const char* uniformName, bool uniformValue) const
    {

    }

    void D3D11Shader::setUniform(const char* uniformName, int uniformValue) const
    {

    }

    void D3D11Shader::setUniform(const char* uniformName, float uniformValue) const
    {

    }

    void D3D11Shader::setUniform(const char* uniformName, const FRMath::Vector2D& uniformValue) const
    {

    }

    void D3D11Shader::setUniform(const char* uniformName, float x, float y) const
    {

    }

    void D3D11Shader::setUniform(const char* uniformName, const FRMath::Vector3D& uniformValue) const
    {

    }

    void D3D11Shader::setUniform(const char* uniformName, float x, float y, float z) const
    {

    }

    void D3D11Shader::setUniform(const char* uniformName, const FRMath::Vector4D& uniformValue) const
    {

    }

    void D3D11Shader::setUniform(const char* uniformName, float x, float y, float z, float w) const
    {

    }

    void D3D11Shader::setUniform(const char* uniformName, const FRMath::Matrix4x4& uniformValue) const
    {

    }
}