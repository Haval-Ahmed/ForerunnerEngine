/// @file D3D11Renderer.h
/// @brief Defines a D3D11 renderer object for creating and modifying a renderer object
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef FRD3D11RENDERER_H
#define FRD3D11RENDERER_H

//////////////////////////////////////////////////////////////////////////
/// Local Libraries
//////////////////////////////////////////////////////////////////////////
#include "BaseRenderer.h"

//////////////////////////////////////////////////////////////////////////
/// DirectX Library Files
//////////////////////////////////////////////////////////////////////////
#include <d3dcommon.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <crtdbg.h>

namespace ForerunnerEngine
{
    namespace ForerunnerRenderer
    {
        class D3D11Renderer : public BaseRenderer
        {
        public:

            //////////////////////////////////////////////////////////////////////////
            /// Constructor
            //////////////////////////////////////////////////////////////////////////
            D3D11Renderer(uint32_t x, uint32_t y, uint32_t width, uint32_t height, ForerunnerWindow::FRWindow* windowHandle);

            //////////////////////////////////////////////////////////////////////////
            /// Virtual destructor
            //////////////////////////////////////////////////////////////////////////
            virtual ~D3D11Renderer(void);

            //////////////////////////////////////////////////////////////////////////
            /// Utilties
            //////////////////////////////////////////////////////////////////////////
            virtual void initializeRendererDevices(void);
            virtual void destroyRenderer(void);
            virtual void initializeRendererResources(void);
            virtual void configureDeviceContext(void);
            virtual void resetDeviceContext(void);
            virtual void deleteDeviceContext(void);
            virtual void enableMultisampling(uint32_t samplingLevel);
            virtual void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
            virtual void setRefreshRate(uint32_t refreshRate);

            ID3D11Device* getD3D11Device(void);
            ID3D11DeviceContext* getD3D11DeviceContext(void);
            ID3D11RenderTargetView* getD3D11RenderTargetView(void);
            ID3D11DepthStencilView* getD3D11DepthStencilView(void);
            IDXGISwapChain* getD3D11SwapChain(void);

        protected:

            //////////////////////////////////////////////////////////////////////////
            ///	Renderer Variables
            //////////////////////////////////////////////////////////////////////////
            D3D_DRIVER_TYPE     m_d3dDriverType;
            D3D_FEATURE_LEVEL   m_d3dFeatureLevel;
            uint32_t            mRefreshRate;

            //////////////////////////////////////////////////////////////////////////
            ///	IDGXI Interfaces and Direct3D Devices
            //////////////////////////////////////////////////////////////////////////
            ID3D11Device* m_direct3DDevice;
            ID3D11DeviceContext* m_direct3DDeviceContext;
            IDXGISwapChain* m_swapChain;
            ID3D11Texture2D* m_backBuffer;
            ID3D11Texture2D* m_depthStencilBuffer;
            ID3D11RenderTargetView* m_renderTargetView;
            ID3D11DepthStencilView* m_depthStencilView;

            //////////////////////////////////////////////////////////////////////////
            ///	// Device Resources and View ports
            //////////////////////////////////////////////////////////////////////////
            D3D11_TEXTURE2D_DESC    m_backBufferDesc;
            D3D11_TEXTURE2D_DESC    m_depthStencilDesc;
            D3D11_VIEWPORT          m_viewPort;

        };
    }
}

#endif	// FRD3D11RENDERER_H