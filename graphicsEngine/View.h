#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>

class View
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	View();
	View(View& other) = delete;	//cannot have copy constructor, needs device to create new buffer
	View(View&& other);
	~View() = default;

	void setProjectionMatrixPespective(float FOV, float aspectRatio, float nearZ, float farZ);
	void setProjectionMatrixOrthographic(float viewWidth, float viewHeight, float nearZ, float farZ);
	
	DirectX::XMMATRIX getProjectionMatrix();

protected:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;

	DirectX::XMFLOAT4X4 projectionMatrix;
};