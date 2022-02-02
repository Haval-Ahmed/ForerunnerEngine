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
        virtual void createVertexShader(const char* shaderString, uint32_t shaderStringLength) override;
        virtual void createFragmentPixelShader(const char* shaderString, uint32_t shaderStringLength) override;
        virtual void loadShaderFromFile(const char* shaderPath, uint32_t shaderType) override;

        //////////////////////////////////////////////////////////////////////////
        /// Shader Program
        //////////////////////////////////////////////////////////////////////////
        virtual void        useShader(void) override;
        virtual void        disableShader(void) override;
        virtual uint32_t    getShader(void);

        //////////////////////////////////////////////////////////////////////////
        /// Set Shader Uniforms
        //////////////////////////////////////////////////////////////////////////
        void setInt(const char* uniformName, int32_t uniformValue) const override;
        void setFloat(const char* uniformName, float uniformValue) const override;
        void setVector2f(const char* uniformName, const glm::vec2& uniformValue) const override;
        void setVector2f(const char* uniformName, float x, float y) const override;
        void setVector3f(const char* uniformName, const glm::vec3& uniformValue) const override;
        void setVector3f(const char* uniformName, float x, float y, float z) const override;
        void setVector4f(const char* uniformName, const glm::vec4& uniformValue) const override;
        void setVector4f(const char* uniformName, float x, float y, float z, float w) const override;
        void setMatrix4f(const char* uniformName, const glm::mat4& uniformValue) const override;

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