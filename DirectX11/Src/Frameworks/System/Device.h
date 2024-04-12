#pragma once

class Device : public Singleton<Device>
{
public:
	Device();
	~Device();

	HRESULT InitDevice();

private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	IDXGISwapChain* swapChain;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;
};