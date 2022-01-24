/// @file BaseShader.h
/// @brief Abstract base class for shader creation and management for all systems. 
/// @Author Haval Ahmed

#ifndef BASESHADER_H
#define BASESHADER_H

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <cstdint>

//////////////////////////////////////////////////////////////////////////
/// External Libraries
//////////////////////////////////////////////////////////////////////////
#include "FRMath.h"

namespace ForerunnerEngine
{
    class BaseShader
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        /// Constructor
        //////////////////////////////////////////////////////////////////////////
        BaseShader() {}

        //////////////////////////////////////////////////////////////////////////
        /// Virtual Destructor
        //////////////////////////////////////////////////////////////////////////
        virtual ~BaseShader(void) {};

        //////////////////////////////////////////////////////////////////////////
        /// Utilitiies
        //////////////////////////////////////////////////////////////////////////
        virtual void createVertexShader(const char* shaderString, uint32_t shaderStringLength)          = 0;
        virtual void createFragmentPixelShader(const char* shaderString, uint32_t shaderStringLength)   = 0;
        virtual void loadShaderFromFile(const char* shaderPath, uint32_t shaderType)                    = 0;

        //////////////////////////////////////////////////////////////////////////
        /// Shader Program
        //////////////////////////////////////////////////////////////////////////
        virtual void useShader(void)        = 0;
        virtual void disableShader(void)    = 0;

        //////////////////////////////////////////////////////////////////////////
        /// Set Shader Uniforms
        //////////////////////////////////////////////////////////////////////////
        virtual void setInt(const char* uniformName, int32_t uniformValue)                      const = 0;
        virtual void setFloat(const char* uniformName, float uniformValue)                      const = 0;
        virtual void setVector2f(const char* uniformName, const glm::vec2& uniformValue)        const = 0;
        virtual void setVector2f(const char* uniformName, float x, float y)                     const = 0;
        virtual void setVector3f(const char* uniformName, const glm::vec3& uniformValue)        const = 0;
        virtual void setVector3f(const char* uniformName, float x, float y, float z)            const = 0;
        virtual void setVector4f(const char* uniformName, const glm::vec4& uniformValue)        const = 0;
        virtual void setVector4f(const char* uniformName, float x, float y, float z, float w)   const = 0;
        virtual void setMatrix4f(const char* uniformName, const glm::mat4& uniformValue)        const = 0;
    };
}

#endif
