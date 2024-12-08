#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>

class View
{
public:
	View();
	View(View& other);
	View(View&& other);
	~View() = default;
	View& operator=(View& other) { return other; }

	void setProjectionMatrixPespective(float FOV, float aspectRatio, float nearZ, float farZ);
	void setProjectionMatrixOrthographic(float viewWidth, float viewHeight, float nearZ, float farZ);
	void setProjectionMatrix(DirectX::XMFLOAT4X4 projectionMatrix);
	
	DirectX::XMMATRIX getProjectionMatrix();

protected:
	DirectX::XMFLOAT4X4 projectionMatrix;
};