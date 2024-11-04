#include "View.h"
#include "View.h"

#include <utility>

View::View() : projectionMatrix{}
{
	//Create the camera view cbuffer
}

View::View(View&& other)
{
	projectionMatrix = std::move(other.projectionMatrix);
}



void View::setProjectionMatrixPespective(float FOV, float aspectRatio, float nearZ, float farZ)
{
	DirectX::XMMATRIX mat = DirectX::XMMatrixPerspectiveFovLH(FOV, aspectRatio, nearZ, farZ);
	DirectX::XMStoreFloat4x4(&projectionMatrix, mat);
}

void View::setProjectionMatrixOrthographic(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	DirectX::XMMATRIX mat = DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);
	DirectX::XMStoreFloat4x4(&projectionMatrix, mat);
}

DirectX::XMMATRIX View::getProjectionMatrix()
{
	return DirectX::XMLoadFloat4x4(&projectionMatrix);
}

