//////////////////////////////////////////////////////////////////////////
/// @File:
///     D3D11Shader.h
/// @Notes:
///     D3D11 Shader class
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

#ifndef D3D11_SHADER_H
#define D3D11_SHADER_H

//////////////////////////////////////////////////////////////////////////
/// DirectX Files
//////////////////////////////////////////////////////////////////////////
#include <d3d11.h>

//////////////////////////////////////////////////////////////////////////
/// Forerunner Files
//////////////////////////////////////////////////////////////////////////
#include "BaseShader.h"

namespace ForerunnerEngine
{
    class D3D11Shader : public BaseShader
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        /// Constructor
        //////////////////////////////////////////////////////////////////////////
        D3D11Shader(ID3D11Device* direct3DDevice, ID3D11DeviceContext* direct3DDeviceContext);

        //////////////////////////////////////////////////////////////////////////
        /// Virtual Destructor
        //////////////////////////////////////////////////////////////////////////
        virtual ~D3D11Shader(void) {};

        //////////////////////////////////////////////////////////////////////////
        /// Utilitiies
        //////////////////////////////////////////////////////////////////////////
        virtual void createVertexShader(const char* shaderString);
        virtual void createFragmentPixelShader(const char* shaderString);
        virtual void loadShaderFromFile(const char* shaderPath, unsigned int shaderType);

        //////////////////////////////////////////////////////////////////////////
        /// Shader Program
        //////////////////////////////////////////////////////////////////////////
        virtual void useShader(void);
        virtual void disableShader(void);

        //////////////////////////////////////////////////////////////////////////
        /// Set Shader Uniforms
        //////////////////////////////////////////////////////////////////////////
        virtual void setUniform(const char* uniformName, bool uniformValue)                     const;
        virtual void setUniform(const char* uniformName, int uniformValue)                      const;
        virtual void setUniform(const char* uniformName, float uniformValue)                    const;
        virtual void setUniform(const char* uniformName, const FRMath::Vector2D& uniformValue)  const;
        virtual void setUniform(const char* uniformName, float x, float y)                      const;
        virtual void setUniform(const char* uniformName, const FRMath::Vector3D& uniformValue)  const;
        virtual void setUniform(const char* uniformName, float x, float y, float z)             const;
        virtual void setUniform(const char* uniformName, const FRMath::Vector4D& uniformValue)  const;
        virtual void setUniform(const char* uniformName, float x, float y, float z, float w)    const;
        virtual void setUniform(const char* uniformName, const FRMath::Matrix4x4& uniformValue) const;

        //////////////////////////////////////////////////////////////////////////
        /// Shader Utilities
        //////////////////////////////////////////////////////////////////////////
        virtual uint32_t compileShader(const char* shaderString);

    protected:

        //////////////////////////////////////////////////////////////////////////
        /// D3D11 Context Variables
        //////////////////////////////////////////////////////////////////////////
        ID3D11Device*           mDirect3DDevice;
        ID3D11DeviceContext*    mDirect3DDeviceContext;

        //////////////////////////////////////////////////////////////////////////
        /// D3D11 Shader Variables
        //////////////////////////////////////////////////////////////////////////
        // Variable To Update Vertex Shader
        CBufferValues cValues;

        // Need a buffer for the constant updating variables inside vertex shader
        ID3D11Buffer* mShaderBuffer;

        // Input Layout for shaders
        ID3D11InputLayout* mInputLayout;

        // Need to store pixel and vertex shader
        ID3D11PixelShader* mPixelShader;
        ID3D11VertexShader* mVertexShader;

        /// Shader Logs
        char mVertexShaderLog[512];
        char mFragmentShaderLog[512];
    };
}

#endif
