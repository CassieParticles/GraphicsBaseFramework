#include "Texture2D.h"
#include <utility>

Texture2D::Texture2D(ID3D11Device* device, D3D11_TEXTURE2D_DESC desc, void* initialData, int typeWidth):width{width},height{height},format{desc.Format}
{
	addTexture2D(device, desc, initialData, typeWidth);
}

Texture2D::Texture2D(Texture2D&& other)
{
	texture2D = std::move(other.texture2D);
	width = other.width;
	height = other.height;
	format = other.format;
}

void Texture2D::addTexture2D(ID3D11Device* device, D3D11_TEXTURE2D_DESC desc, void* initialData, int typeWidth)
{
	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = initialData;
	data.SysMemPitch = typeWidth * desc.Width;

	device->CreateTexture2D(&desc, &data, &texture2D);
}

void Texture2D::addSRV(ID3D11Device* device)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc{};
	desc.Format = format;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels = -1;
	desc.Texture2D.MostDetailedMip = 0;

	device->CreateShaderResourceView(texture2D.Get(), &desc, &srv);
}

void Texture2D::addRTV(ID3D11Device* device)
{
	device->CreateRenderTargetView(texture2D.Get(), 0, &rtv);
}

void Texture2D::addDSV(ID3D11Device* device)
{
	device->CreateDepthStencilView(texture2D.Get(), 0, &dsv);
}