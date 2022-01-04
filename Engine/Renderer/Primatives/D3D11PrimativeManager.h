//////////////////////////////////////////////////////////////////////////
/// @File:
///     D3D11PrimativeManager.h
/// @Notes:
///     D3D11PrimativeManager.h
/// @Author:
///     Haval Ahmed
/// @Copyright:
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

#ifndef D3D11_PRIMATIVE_MANAGER_H
#define D3D11_PRIMATIVE_MANAGER_H

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <vector>

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "PrimativeManager.h"
#include "D3D11Primative3D.h"
#include "D3D11Shader.h"

namespace ForerunnerEngine
{
    class D3D11PrimativeManager : public PrimativeManager
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        /// Constructor
        //////////////////////////////////////////////////////////////////////////
        D3D11PrimativeManager();

        //////////////////////////////////////////////////////////////////////////
        /// Virtual Destructor
        //////////////////////////////////////////////////////////////////////////
        virtual ~D3D11PrimativeManager();

        //////////////////////////////////////////////////////////////////////////
        /// Utilities
        //////////////////////////////////////////////////////////////////////////
        virtual void draw(void) = 0;

        //////////////////////////////////////////////////////////////////////////
        /// Object Creation
        //////////////////////////////////////////////////////////////////////////
        virtual void createCube(void) = 0;
        virtual void createPyramid(void) = 0;
        virtual void createCylinder(void) = 0;
        virtual void createPlane(void) = 0;
        virtual void createSphere(void) = 0;
        virtual void createTriangle(void) = 0;

    protected:

        //////////////////////////////////////////////////////////////////////////
        /// D3D11 Primative Initialization
        //////////////////////////////////////////////////////////////////////////
        void initializePrimatives(void);
        void cleanUpPrimativeManager(void);
        void updateBufferData(void);

        //////////////////////////////////////////////////////////////////////////
        /// Functions which contain vertice and indice 
        /// information for each primative type
        //////////////////////////////////////////////////////////////////////////
        void generateCube(ForerunnerEngine::D3D11Primative3D* primative);
        void generatePyramid(ForerunnerEngine::D3D11Primative3D* primative);
        void generateCylinder(ForerunnerEngine::D3D11Primative3D* primative);
        void generatePlane(ForerunnerEngine::D3D11Primative3D* primative);
        void generateSphere(ForerunnerEngine::D3D11Primative3D* primative);
        void generateTriangle(ForerunnerEngine::D3D11Primative3D* primative);

        //////////////////////////////////////////////////////////////////////////
        /// OpenGL Specific Variables
        //////////////////////////////////////////////////////////////////////////
        std::vector<D3D11Primative3D*> mPrimativeList;
        ForerunnerEngine::D3D11Shader mShader;

        //////////////////////////////////////////////////////////////////////////
        /// Parent vertice and indice information
        //////////////////////////////////////////////////////////////////////////
        std::vector<Vertices> mVertices;
        std::vector<uint32_t> mIndicies;

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
    };
}

#endif