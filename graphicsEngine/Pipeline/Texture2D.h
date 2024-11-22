#pragma once

#include <d3d11.h>
#include <wrl.h>

class Texture2D
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Texture2D(ID3D11Device* device, D3D11_TEXTURE2D_DESC desc, void* initialData, int typeWidth);
	Texture2D(Texture2D& other) = delete;
	Texture2D(Texture2D&& other);

	//Create a texture2D, takes the description, and the size of each pixel in bytes (r32g32b32a32float is 16 bytes)
	void addTexture2D(ID3D11Device* device, D3D11_TEXTURE2D_DESC desc, void* initialData, int typeWidth);

	void addSRV(ID3D11Device* device);
	void addRTV(ID3D11Device* device);
	void addDSV(ID3D11Device* device);
protected:
	ComPtr<ID3D11Texture2D> texture2D;
	int width;
	int height;
	DXGI_FORMAT format;

	ComPtr<ID3D11ShaderResourceView> srv;
	ComPtr<ID3D11RenderTargetView> rtv;
	ComPtr<ID3D11DepthStencilView> dsv;
}