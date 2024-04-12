#include "Framework.h"

Device::Device()
    :device(nullptr), deviceContext(nullptr), driverType(D3D_DRIVER_TYPE_UNKNOWN), featureLevel(D3D_FEATURE_LEVEL_11_0)
{
    if (FAILED(InitDevice()))
    {
        PostQuitMessage(0);
    }
}

Device::~Device()
{
    device->Release();
}

HRESULT Device::InitDevice()
{
    HRESULT outputHR;

    // BGRA 형식(DXGI_FORMAT_B8G8R8A8_UNORM 및 DXGI_FORMAT_B8G8R8A8_UNORM_SRGB)을 지원
    // Direct3D 리소스와의 Direct2D 상호 운용성에 필요
    UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    // 디버그 계층을 지원
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE,     // Direct3D 기능을 구현하는 최상의 성능을 내는 드라이버
                                      D3D_DRIVER_TYPE_WARP,         // 고성능 소프트웨어 래스터라이저
                                      D3D_DRIVER_TYPE_REFERENCE, }; // 속도가 느리지만 정확한 드라이버
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1,
                                          D3D_FEATURE_LEVEL_11_0,
                                          D3D_FEATURE_LEVEL_10_1,
                                          D3D_FEATURE_LEVEL_10_0, };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        driverType = driverTypes[driverTypeIndex];
        
        ///-------------------------------------------------------------------------------------------------------
        /// Func: D3D11CreateDevcie()
        /// 성공시 ID3D11Devcie 및 ID3D11DevcieContext 인터페이스에 대한 포인터를 반환
        /// 실패시 Null을 반환
        ///-------------------------------------------------------------------------------------------------------
        outputHR = D3D11CreateDevice(nullptr,               // IDXGIAdapter(디스플레이 하위 시스템 인터페이스)
                                                            // nullptr -> 기본 그래픽 어댑터
                                     driverType,            // 디바이스 드라이버
                                     nullptr,               // HInstance == HMODULE
                                     createDeviceFlags,     //
                                     featureLevels,         //
                                     numFeatureLevels,      //
                                     D3D11_SDK_VERSION,     // D3D_SDK_VERSION
                                     &device,               //
                                     &featureLevel,         //
                                     &deviceContext);       //

        UINT width = WIN_WIDTH;
        UINT height = WIN_HEIGHT;

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChainDesc.BufferCount = 1;
        swapChainDesc.BufferDesc.Width = width;
        swapChainDesc.BufferDesc.Height = height;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = hWnd;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.Windowed = true;

        outputHR = D3D11CreateDeviceAndSwapChain(nullptr,
                                                 driverType,
                                                 nullptr,
                                                 createDeviceFlags,
                                                 featureLevels,
                                                 numFeatureLevels,
                                                 D3D11_SDK_VERSION,
                                                 &swapChainDesc,
                                                 &swapChain,
                                                 &device,
                                                 &featureLevel,
                                                 &deviceContext);
        
        if (outputHR == E_INVALIDARG)
        {

        }

        //ID3D11Texture2D* backBuffer;
        //
        //swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
        //device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
        //backBuffer->Release();
    }

    return E_NOTIMPL;
}
