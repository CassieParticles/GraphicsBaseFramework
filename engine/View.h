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

	DirectX::XMFLOAT3 setPosition(DirectX::XMFLOAT3 position) { return this->position = position; }
	DirectX::XMFLOAT3 setPosition(float x, float y, float z) { return this->position = DirectX::XMFLOAT3(x, y, z); }
	DirectX::XMFLOAT3 setPosition(DirectX::XMVECTOR position) { DirectX::XMStoreFloat3(&this->position, position); return this->position; }
	DirectX::XMFLOAT3 getPosition() { return position; }
	DirectX::XMVECTOR loadPosition() { return DirectX::XMLoadFloat3(&position); }

	DirectX::XMFLOAT3 setRotation(DirectX::XMFLOAT3 rotation) { return this->rotation = rotation; }
	DirectX::XMFLOAT3 setRotation(float x, float y, float z) { return this->rotation = DirectX::XMFLOAT3(x, y, z); }
	DirectX::XMFLOAT3 setRotation(DirectX::XMVECTOR rotation) { DirectX::XMStoreFloat3(&this->rotation, rotation); return this->rotation; }
	DirectX::XMFLOAT3 getRotation() { return rotation; }
	DirectX::XMVECTOR loadRotation() { return DirectX::XMLoadFloat3(&rotation);}


	DirectX::XMMATRIX calcViewMatrix();

	void updateView(ID3D11DeviceContext* deviceContext);

	ID3D11Buffer* getCameraBuffer() { return cameraMatrix.Get(); }

protected:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;

	DirectX::XMFLOAT4X4 projectionMatrix;

	ComPtr<ID3D11Buffer> cameraMatrix;
};