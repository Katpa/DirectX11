#include "Framework.h"

GameManager::GameManager()
{
	Construction();
}

GameManager::~GameManager()
{
	Destruction();
}

void GameManager::Update()
{
}

void GameManager::Render()
{
}

void GameManager::Construction()
{
	HRESULT hr;

	hr = Device::Get()->InitDevice();
	if (FAILED(hr))
		PostQuitMessage(0);
}

void GameManager::Destruction()
{
	Device::Delete();
}
