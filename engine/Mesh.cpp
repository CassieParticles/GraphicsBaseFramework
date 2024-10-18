#include "Mesh.h"

#include <iostream>

Mesh::Mesh() :vertexCount{ 0 } 	//Default constructor
{

}

Mesh::Mesh(ID3D11Device* device, MeshVertex* meshVertices, int vertexCount, int* indices, int indexCount, bool dynamic)
{
	addVertices(device, meshVertices, vertexCount, indices, indexCount, dynamic);
}

Mesh::Mesh(Mesh&& other) noexcept
{
	vertexCount = other.vertexCount;
	vertexBuffer = std::move(other.vertexBuffer);
	indexBuffer = std::move(other.indexBuffer);

	//TODO: When cbuffers are added, move these
}

Mesh::~Mesh()
{

}

void Mesh::addVertices(ID3D11Device* device, MeshVertex* meshVertices, int vertexCount, int* indices, int indexCount, bool dynamic)
{
	//Mesh has already been created, cancel
	if (vertexBuffer)
	{
		std::cerr << "Error: mesh has already been created\n";
		return;
	}
	//Create vertex buffer
	D3D11_BUFFER_DESC vertexDesc{};
	vertexDesc.ByteWidth = sizeof(MeshVertex) * vertexCount;
	vertexDesc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData{};
	vertexData.pSysMem = meshVertices;

	device->CreateBuffer(&vertexDesc, &vertexData, &vertexBuffer);

	//Create index buffer
	D3D11_BUFFER_DESC indexDesc{};
	indexDesc.ByteWidth = sizeof(int) * indexCount;
	indexDesc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDesc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
	indexDesc.MiscFlags = 0;
	indexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData{};
	indexData.pSysMem = indices;

	device->CreateBuffer(&indexDesc, &indexData, &indexBuffer);
}

void Mesh::useMesh(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(MeshVertex);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
}
