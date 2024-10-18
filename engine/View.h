#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>

class View
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	View(ID3D11Device* device, DirectX::XMFLOAT3 position = { 0,0,0 }, DirectX::XMFLOAT3 rotation = {0,0,0});
	View(View& other) = delete;	//cannot have copy constructor, needs device to create new buffer
	View(View&& other);
	~View() = default;

	void setProjectionMatrixPespective(float FOV, float aspectRatio, float nearZ, float farZ);
	void setProjectionMatrixOrthographic(float viewWidth, float viewHeight, float nearZ, float farZ);

	DirectX::XMMATRIX calcViewMatrix();

	void updateView(ID3D11DeviceContext* deviceContext);

	ID3D11Buffer* getCameraBuffer() { return cameraMatrix.Get(); }

protected:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;

	DirectX::XMFLOAT4X4 projectionMatrix;

	ComPtr<ID3D11Buffer> cameraMatrix;
};