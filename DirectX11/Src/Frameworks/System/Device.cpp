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

    // BGRA ����(DXGI_FORMAT_B8G8R8A8_UNORM �� DXGI_FORMAT_B8G8R8A8_UNORM_SRGB)�� ����
    // Direct3D ���ҽ����� Direct2D ��ȣ ��뼺�� �ʿ�
    UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    // ����� ������ ����
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE,     // Direct3D ����� �����ϴ� �ֻ��� ������ ���� ����̹�
                                      D3D_DRIVER_TYPE_WARP,         // ���� ����Ʈ���� �����Ͷ�����
                                      D3D_DRIVER_TYPE_REFERENCE, }; // �ӵ��� �������� ��Ȯ�� ����̹�
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
        /// ������ ID3D11Devcie �� ID3D11DevcieContext �������̽��� ���� �����͸� ��ȯ
        /// ���н� Null�� ��ȯ
        ///-------------------------------------------------------------------------------------------------------
        outputHR = D3D11CreateDevice(nullptr,               // IDXGIAdapter(���÷��� ���� �ý��� �������̽�)
                                                            // nullptr -> �⺻ �׷��� �����
                                     driverType,            // ����̽� ����̹�
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
