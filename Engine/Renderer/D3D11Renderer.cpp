//////////////////////////////////////////////////////////////////////////
/// @File:
///     D3D11Renderer.cpp
/// @Modification:
///     1/7/18 - Haval-Ahmed
/// @Notes:
///     D3D11 renderer class for the Forerunner Engine. 
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// User Defined Library Files
//////////////////////////////////////////////////////////////////////////
#include "D3D11Renderer.h"

namespace ForerunnerEngine
{
    namespace ForerunnerRenderer
    {

        D3D11Renderer::D3D11Renderer(uint32_t x, uint32_t y, uint32_t width, uint32_t height, ForerunnerWindow::FRWindow* windowHandle) 
            : BaseRenderer()
        {
            /// Initialize everything to nullptr to ensure proper initialization
            mRefreshRate = 60;
            m_direct3DDevice = nullptr;
            m_direct3DDeviceContext = nullptr;
            m_swapChain = nullptr;
            m_backBuffer = nullptr;
            m_depthStencilBuffer = nullptr;
            m_renderTargetView = nullptr;
            m_depthStencilView = nullptr;

            initializeRendererDevices();
            initializeRendererResources();
        }

        D3D11Renderer::~D3D11Renderer(void)
        {

        }

        void D3D11Renderer::initializeRendererDevices(void)
        {
            /// Initialize to unsuccessfull
            int functionReturnStatus = 0;

            /// Select feature level
            m_d3dFeatureLevel = D3D_FEATURE_LEVEL_11_1;

            /// Set device flags for creating Direct3D Device
            uint32_t deviceFlags = 0;

            /// Define Debug Environment
#if defined(DEBUG) | defined(_DEBUG)
            deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

            /// Parameters for D3D11CreateDevice
            /// 1. pAdapter: 
            ///			Adapter
            /// 2. DriverType:
            ///			D3D_DRIVER_TYPE_REFERENCE
            ///			D3D_DRIVER_TYPE_HARDWARE
            ///			D3D_DRIVER_TYPE_SOFTWARE
            ///			D3D_DRIVER_TYPE_WARP
            /// 3. Software:
            /// 4. Flags:
            ///			D3D11_CREATE_DEVICE_DEBUG
            /// 5. pFeatureLevels: 
            ///			Array of D3D_FEATURE_LEVEL
            /// 6. featureLevels: 
            ///			Number of elements inside array of D3D_FEATURE_LEVEL
            /// 7. SDK_VERSION
            /// 8. ppDevice: 
            ///			Returns created device
            /// 9. pFeatureLevel: 
            ///			Returns the first supported feature level inside D3D_FEATURE_LEVEL array
            /// 10. ppImmediateContext: 
            ///			Returns created device context
            HRESULT createDeviceResult = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlags, 0, 0, D3D11_SDK_VERSION, &m_direct3DDevice, &m_d3dFeatureLevel, &m_direct3DDeviceContext);

            /// If device creation failed, create warp device to allow user to run engine with hardware
            if (createDeviceResult != S_OK)
            {
                /// Create WRAP device
                createDeviceResult = D3D11CreateDevice(0, D3D_DRIVER_TYPE_WARP, nullptr, deviceFlags, 0, 0, D3D11_SDK_VERSION, &m_direct3DDevice, &m_d3dFeatureLevel, &m_direct3DDeviceContext);

                /// Check result
                if (createDeviceResult != S_OK)
                {
                    functionReturnStatus = 0;
                }
            }
            else
            {
                functionReturnStatus = 1;
            }
        }

        void D3D11Renderer::destroyRenderer(void)
        {

        }

        void D3D11Renderer::initializeRendererResources(void)
        {
            /// Initialize to unsuccessfull
            int functionReturnStatus = 0;

            /// Create a swap chain desc
            DXGI_SWAP_CHAIN_DESC* swapChainDesc = new DXGI_SWAP_CHAIN_DESC();

            /// Set parameters
            swapChainDesc->BufferDesc.Width						= RendererWidth;
            swapChainDesc->BufferDesc.Height					= RendererHeight;
            swapChainDesc->BufferDesc.RefreshRate.Numerator		= RefreshRate;
            swapChainDesc->BufferDesc.RefreshRate.Denominator	= 1;
            swapChainDesc->BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
            swapChainDesc->BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
            swapChainDesc->BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

            /// Check for MSAA
            if (MultisamplingEnabled)
            {
                /// Get multisampling levels
                getMultisamplingLevels();

                // Can change count and quality higher if wanted
                swapChainDesc->SampleDesc.Count = 1;
                swapChainDesc->SampleDesc.Quality = MultisamplingLevel;
            }
            else
            {
                swapChainDesc->SampleDesc.Count = 1;
                swapChainDesc->SampleDesc.Quality = 0;
            }

            swapChainDesc->BufferUsage	= DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc->BufferCount	= 1;
            swapChainDesc->OutputWindow = WindowPtr->WindowHandle;
            swapChainDesc->Windowed		= 0;
            swapChainDesc->SwapEffect	= DXGI_SWAP_EFFECT_DISCARD;
            swapChainDesc->Flags		= 0;

            // Before creating swap chain of IDXGISwapChain we need a device, adapter, and factory all types of IDGXI
            IDXGIDevice* dxgiDevice		= 0;
            IDXGIAdapter* dxgiAdapter	= 0;
            IDXGIFactory* dxgiFactory	= 0;

            /// Query Objects for swap chain
            m_direct3DDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));

            /// Grab parent of dxgi device
            HRESULT result = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter));

            /// Check result
            if (SUCCEEDED(result))
            {
                dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory));
                dxgiFactory->CreateSwapChain(m_direct3DDevice, swapChainDesc, &m_swapChain);
                functionReturnStatus = 1;
            }

            configureDeviceContext();

        }

        void D3D11Renderer::configureDeviceContext()
        {
            /// Get Buffer for swap chain to back buffer
            HRESULT result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_backBuffer));

            /// Create a render target view
            result = m_direct3DDevice->CreateRenderTargetView(m_backBuffer, 0, &m_renderTargetView);

            /// Get back buffer desc
            m_backBuffer->GetDesc(&m_backBufferDesc);

            /// Define depth stencil properties
            m_depthStencilDesc.Width = m_backBufferDesc.Width;
            m_depthStencilDesc.Height = m_backBufferDesc.Height;
            m_depthStencilDesc.MipLevels = 1;
            m_depthStencilDesc.ArraySize = 1;
            m_depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
            m_depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
            m_depthStencilDesc.CPUAccessFlags = 0;
            m_depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
            m_depthStencilDesc.MiscFlags = 0;

            // Check for sampling enabled
            if (MultisamplingEnabled)
            {
                m_depthStencilDesc.SampleDesc.Count		= MultisamplingLevel;
                m_depthStencilDesc.SampleDesc.Quality	= MultisamplingLevel - 1;
            }
            m_depthStencilDesc.SampleDesc.Count = 1;
            m_depthStencilDesc.SampleDesc.Quality = 0;

            // Create a texture and view for the depth stencil
            m_direct3DDevice->CreateTexture2D(&m_depthStencilDesc, nullptr, &m_depthStencilBuffer);
            m_direct3DDevice->CreateDepthStencilView(m_depthStencilBuffer, 0, &m_depthStencilView);

            // Set Output Merger Stage Render Targets
            m_direct3DDeviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

            // Clear viewport
            memset((void*)&m_viewPort, 0, sizeof(D3D11_VIEWPORT));

            // Define view port
            m_viewPort.TopLeftX = static_cast<float>(getXPosition());
            m_viewPort.TopLeftY = static_cast<float>(getYPosition());
            m_viewPort.Width = static_cast<float>(getWidth());
            m_viewPort.Height = static_cast<float>(getHeight());
            m_viewPort.MinDepth = 0.0f;
            m_viewPort.MaxDepth = 1.0f;

            // Set Rasteration stage view ports
            m_direct3DDeviceContext->RSSetViewports(1, &m_viewPort);
        }

        void D3D11Renderer::resetDeviceContext()
        {

        }

        void D3D11Renderer::deleteDeviceContext()
        {

        }

        void D3D11Renderer::enableMultisampling(uint32_t samplingLevel)
        {
            MultisamplingLevel = samplingLevel;

            configureDeviceContext();
        }

        // void D3D11Renderer::getMultisamplingLevels()
        // {
        // 	// Check with created devices sample level
        // 	m_direct3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_multisamplingLevel);
        // }

        void D3D11Renderer::setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            // Update renderer view port sizes
            setXPosition(x);
            setYPosition(y);
            setWidth(width);
            setHeight(height);

            // Clear viewport
            memset((void*)&m_viewPort, 0, sizeof(D3D11_VIEWPORT));

            // Define view port
            m_viewPort.TopLeftX = static_cast<float>(getXPosition());
            m_viewPort.TopLeftY = static_cast<float>(getYPosition());
            m_viewPort.Width = static_cast<float>(getWidth());
            m_viewPort.Height = static_cast<float>(getHeight());
            m_viewPort.MinDepth = 0.0f;
            m_viewPort.MaxDepth = 1.0f;

            // Set Rasteration stage view ports
            m_direct3DDeviceContext->RSSetViewports(1, &m_viewPort);
        }

        void D3D11Renderer::setRefreshRate(uint32_t refreshRate)
        {
            mRefreshRate = refreshRate;
        }

        ID3D11Device* D3D11Renderer::getD3D11Device(void)
        {
            return m_direct3DDevice;
        }

        ID3D11DeviceContext* D3D11Renderer::getD3D11DeviceContext(void)
        {
            return m_direct3DDeviceContext;
        }

        ID3D11RenderTargetView* D3D11Renderer::getD3D11RenderTargetView(void)
        {
            return m_renderTargetView;
        }

        ID3D11DepthStencilView* D3D11Renderer::getD3D11DepthStencilView(void)
        {
            return m_depthStencilView;
        }

        IDXGISwapChain* D3D11Renderer::getD3D11SwapChain(void)
        {
            return m_swapChain;
        }
    }
}