/// @file OpenGLShader.h
/// @brief GLSL Shader Class
/// @Author Haval Ahmed

#ifndef OPENGLSHADER_H
#define OPENGLSHADER_H

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "BaseShader.h"
#include "GLSLShaders.h"

namespace ForerunnerEngine
{
    class OpenGLShader : public BaseShader
    {

    public:
        //////////////////////////////////////////////////////////////////////////
        /// Constructor
        //////////////////////////////////////////////////////////////////////////
        OpenGLShader();

        //////////////////////////////////////////////////////////////////////////
        /// Virtual Destructor
        //////////////////////////////////////////////////////////////////////////
        virtual ~OpenGLShader(void) {};

        //////////////////////////////////////////////////////////////////////////
        /// Utilitiies
        //////////////////////////////////////////////////////////////////////////
        virtual void createVertexShader(const char* shaderString, uint32_t shaderStringLength);
        virtual void createFragmentPixelShader(const char* shaderString, uint32_t shaderStringLength);
        virtual void loadShaderFromFile(const char* shaderPath, uint32_t shaderType);

        //////////////////////////////////////////////////////////////////////////
        /// Shader Program
        //////////////////////////////////////////////////////////////////////////
        virtual void        useShader(void) override;
        virtual void        disableShader(void) override;
        virtual uint32_t    getShader(void);

        //////////////////////////////////////////////////////////////////////////
        /// Set Shader Uniforms
        //////////////////////////////////////////////////////////////////////////
        void setUniform(const char* uniformName, bool uniformValue) const;
        void setUniform(const char* uniformName, uint32_t uniformValue) const;
        void setUniform(const char* uniformName, float uniformValue) const;
        void setUniform(const char* uniformName, const glm::vec2& uniformValue) const;
        void setUniform(const char* uniformName, float x, float y) const;
        void setUniform(const char* uniformName, const glm::vec3& uniformValue) const;
        void setUniform(const char* uniformName, float x, float y, float z) const;
        void setUniform(const char* uniformName, const glm::vec4& uniformValue) const;
        void setUniform(const char* uniformName, float x, float y, float z, float w) const;
        void setUniform(const char* uniformName, const glm::mat4& uniformValue) const;

    protected:

        //////////////////////////////////////////////////////////////////////////
        /// Shader Managment
        //////////////////////////////////////////////////////////////////////////
        virtual void        createShaderProgram(void);
        virtual uint32_t    compileShader(int32_t shaderType, const char* shaderSource, uint32_t shaderStringLength, char* shaderLog);
        virtual void        attachToShaderProgram(uint32_t shader);

        /// Shader program
        uint32_t shaderProgram;
        uint32_t vertexShader;
        uint32_t fragmentShader;

        /// Shader Logs
        char vertexShaderLog[512];
        char fragmentShaderLog[512];
    };
}

#endif