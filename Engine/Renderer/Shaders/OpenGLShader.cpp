//////////////////////////////////////////////////////////////////////////
/// @File:
///     OpenGLShader.cpp
/// @Notes:
///     GLSL Shader Class
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     See attached license 
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>

//////////////////////////////////////////////////////////////////////////
/// GLAD Headers 
//////////////////////////////////////////////////////////////////////////
#include "glad.h"

//////////////////////////////////////////////////////////////////////////
/// Local Libraries
//////////////////////////////////////////////////////////////////////////
#include "OpenGLShader.h"

namespace ForerunnerEngine
{
    OpenGLShader::OpenGLShader() 
        : BaseShader()
        , shaderProgram(0)
        , vertexShader(0)
        , fragmentShader(0)
    {
        memset(vertexShaderLog,    0, sizeof(vertexShaderLog));
        memset(fragmentShaderLog,  0, sizeof(fragmentShaderLog));

        /// Create shader program
        createShaderProgram();
    }

    void OpenGLShader::createShaderProgram(void)
    {
        /// Create a shader program
        shaderProgram = glCreateProgram();
    }

    uint32_t OpenGLShader::compileShader(int32_t shaderType, const char* shaderSource, uint32_t shaderStringLength, char* shaderLog)
    {
        /// Create Shader
        uint32_t shader = glCreateShader(shaderType);

        /// Pass shader source and compile shader
        GLint shaderLength = (GLint)shaderStringLength;
        glShaderSource(shader, 1, &shaderSource, &shaderLength);
        glCompileShader(shader);

        /// Check out of shader, ensure it was valid
        int32_t shaderResult;

        /// Check compile status of shader
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderResult);

        if (!shaderResult)
        {
            glGetShaderInfoLog(shader, 512, NULL, shaderLog);
        }
        
        return shader;
    }

    void OpenGLShader::createVertexShader(const char* shaderString, uint32_t shaderStringLength)
    {
        vertexShader = compileShader(GL_VERTEX_SHADER, shaderString, shaderStringLength, vertexShaderLog);
        attachToShaderProgram(vertexShader);
    }


    void OpenGLShader::createFragmentPixelShader(const char* shaderString, uint32_t shaderStringLength)
    {
        fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaderString, shaderStringLength, fragmentShaderLog);
        attachToShaderProgram(fragmentShader);
    }

    
    void OpenGLShader::loadShaderFromFile(const char* shaderPath, uint32_t shaderType)
    {
        /// Create variables for file handling
        std::ifstream shaderFile(shaderPath);
        std::string contents((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());

        if (shaderType == GL_VERTEX_SHADER)
        {
            createVertexShader(contents.c_str(), static_cast<uint32_t>(contents.size()));
        }
        else if (shaderType == GL_FRAGMENT_SHADER)
        {
            createFragmentPixelShader(contents.c_str(), static_cast<uint32_t>(contents.size()));
        }
    }

    void OpenGLShader::useShader(void)
    {
        glUseProgram(shaderProgram);
    }

    void OpenGLShader::disableShader(void)
    {
        glUseProgram(0);
    }

    unsigned int OpenGLShader::getShader(void)
    {
        return shaderProgram;
    }

    void OpenGLShader::attachToShaderProgram(uint32_t shader)
    {
        glAttachShader(shaderProgram, shader);
        glLinkProgram(shaderProgram);
    }

    void OpenGLShader::setUniform(const char* uniformName, bool uniformValue) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, uniformName), (int)uniformValue);
    }

    void OpenGLShader::setUniform(const char* uniformName, uint32_t uniformValue) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, uniformName), uniformValue);
    }

    void OpenGLShader::setUniform(const char* uniformName, float uniformValue) const
    {
        glUniform1f(glGetUniformLocation(shaderProgram, uniformName), uniformValue);
    }

    void OpenGLShader::setUniform(const char* uniformName, const glm::vec2& uniformValue) const
    {
        glUniform2f(glGetUniformLocation(shaderProgram, uniformName), uniformValue.x, uniformValue.y);
    }

    void OpenGLShader::setUniform(const char* uniformName, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(shaderProgram, uniformName), x, y);
    }

    void OpenGLShader::setUniform(const char* uniformName, const glm::vec3& uniformValue) const
    {
        glUniform3f(glGetUniformLocation(shaderProgram, uniformName), uniformValue.x, uniformValue.y, uniformValue.z);
    }

    void OpenGLShader::setUniform(const char* uniformName, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(shaderProgram, uniformName), x, y, z);
    }

    void OpenGLShader::setUniform(const char* uniformName, const glm::vec4& uniformValue) const
    {
        glUniform4f(glGetUniformLocation(shaderProgram, uniformName), uniformValue.x, uniformValue.y, uniformValue.z, uniformValue.w);
    }

    void OpenGLShader::setUniform(const char* uniformName, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(shaderProgram, uniformName), x, y, z, w);
    }

    void OpenGLShader::setUniform(const char* uniformName, const glm::mat4& uniformValue) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniformName), 1, GL_FALSE, &uniformValue[0][0]);
    }
}