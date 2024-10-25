#include "View.h"

#include <utility>

View::View(ID3D11Device* device, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation) :position{ position }, rotation{ rotation }, projectionMatrix{}
{
	//Create the camera view cbuffer
	D3D11_BUFFER_DESC desc{};

	desc.ByteWidth = sizeof(DirectX::XMMATRIX);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	device->CreateBuffer(&desc, 0, &cameraMatrix);
}

View::View(View&& other)
{
	position = std::move(other.position); 
	rotation = std::move(other.rotation);

	projectionMatrix = std::move(other.projectionMatrix);

	cameraMatrix = std::move(other.cameraMatrix);
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

DirectX::XMMATRIX View::calcViewMatrix()
{
	//DirectX::XMVECTOR viewDirection = { cos(rotation.x) * sin(rotation.y), sin(rotation.x),cos(rotation.x) * cos(rotation.y) };
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	DirectX::XMVECTOR viewDirection = DirectX::XMVector3TransformCoord(DirectX::XMVECTOR{0,0,1,1},rotationMatrix);
	DirectX::XMVECTOR upDirection = DirectX::XMVector3TransformCoord(DirectX::XMVECTOR{0, 1, 0, 1}, rotationMatrix);
	return DirectX::XMMatrixLookToLH(DirectX::XMLoadFloat3(&position), viewDirection, upDirection);
}

void View::updateView(ID3D11DeviceContext* deviceContext)
{
	DirectX::XMMATRIX projMat = DirectX::XMLoadFloat4x4(&projectionMatrix);
	DirectX::XMMATRIX cameraMat= calcViewMatrix() * projMat;

	D3D11_MAPPED_SUBRESOURCE dat{};

	deviceContext->Map(cameraMatrix.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &dat);
	memcpy(dat.pData, &cameraMat, sizeof(cameraMat));
	deviceContext->Unmap(cameraMatrix.Get(), 0);

}
