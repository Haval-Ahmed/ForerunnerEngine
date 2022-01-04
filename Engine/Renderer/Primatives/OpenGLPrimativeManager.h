/// @file OpenGLPrimativeManager.h
/// @brief OpenGL primative manager class
/// @author Haval Ahmed

#ifndef OPENGL_PRIMATIVE_MANAGER_H
#define OPENGL_PRIMATIVE_MANAGER_H

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <vector>

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "FRMath.h"
#include "PrimativeManager.h"
#include "OpenGLShader.h"

namespace ForerunnerEngine
{
    class OpenGLPrimativeManager : public PrimativeManager
    {
    public:

        //////////////////////////////////////////////////////////////////////////
        /// Constructor
        //////////////////////////////////////////////////////////////////////////
        OpenGLPrimativeManager();

        //////////////////////////////////////////////////////////////////////////
        /// Virtual Destructor
        //////////////////////////////////////////////////////////////////////////
        virtual ~OpenGLPrimativeManager();

        //////////////////////////////////////////////////////////////////////////
        /// Utilities
        //////////////////////////////////////////////////////////////////////////
        virtual void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
        virtual uint32_t loadTexture(const char* filePath);

        //////////////////////////////////////////////////////////////////////////
        /// Object Creation
        //////////////////////////////////////////////////////////////////////////
        virtual Primative3D* createCube(void);
        virtual Primative3D* createPyramid(void);
        virtual Primative3D* createCylinder(void);
        virtual Primative3D* createPlane(void);
        virtual Primative3D* createSphere(void);
        virtual Primative3D* createTriangle(void);

        //////////////////////////////////////////////////////////////////////////
        /// Getters
        //////////////////////////////////////////////////////////////////////////
        virtual OpenGLShader& getShader(void);

    protected:

        //////////////////////////////////////////////////////////////////////////
        /// OpenGL functions
        //////////////////////////////////////////////////////////////////////////
        void initializeOpenGL(void);
        void cleanOpenGL(void);
        void updateBufferData(void);
        void activeTexture(uint32_t texture);

        //////////////////////////////////////////////////////////////////////////
        /// Functions which contain vertice and indice 
        /// information for each primative type
        //////////////////////////////////////////////////////////////////////////
        void generateCube(ForerunnerEngine::Primative3D* primative);
        void generatePyramid(ForerunnerEngine::Primative3D* primative);
        void generateCylinder(ForerunnerEngine::Primative3D* primative);
        void generatePlane(ForerunnerEngine::Primative3D* primative);
        void generateSphere(ForerunnerEngine::Primative3D* primative);
        void generateTriangle(ForerunnerEngine::Primative3D* primative);

        //////////////////////////////////////////////////////////////////////////
        /// OpenGL Specific Variables
        //////////////////////////////////////////////////////////////////////////
        std::vector<Primative3D*> primativeList;
        ForerunnerEngine::OpenGLShader shader;

        //////////////////////////////////////////////////////////////////////////
        /// Parent vertice and indice information
        //////////////////////////////////////////////////////////////////////////
        std::vector<Vertices> vertices;
        std::vector<uint32_t> indicies;

        //////////////////////////////////////////////////////////////////////////
        /// OpenGL Vertex Attribute Specification
        //////////////////////////////////////////////////////////////////////////
        uint32_t    vertexArrayObject;
        uint32_t    vertexBufferObject;
        uint32_t    normalBufferObject;
        uint32_t    textureBufferObject;
        uint32_t    indiceBufferObject;
        bool        initializeTexture;
    };
}

#endif