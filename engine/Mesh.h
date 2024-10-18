#pragma once

#include <DirectXMath.h>
#include <wrl.h>
#include <d3d11.h>

#include <vector>



class Mesh
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	//Publically accessible, but within the Mesh namespace
	struct MeshVertex	//
	{
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 normal;
		DirectX::XMFLOAT2 uv;
	};

	Mesh();
	Mesh(ID3D11Device* device,MeshVertex* meshVertices, int vertexCount, int* indices, int indexCount, bool dynamic);
	Mesh(Mesh& other) = delete;	//Copy constructor disabled, cannot copy gpu data without deviceContext
	Mesh(Mesh&& other) noexcept;
	~Mesh();

	void addVertices(ID3D11Device* device, MeshVertex* meshVertices, int vertexCount,int* indices, int indexCount, bool dynamic);

	//Bind Mesh to pipeline
	void useMesh(ID3D11DeviceContext* deviceContext);
	int getVertexCount() { return vertexCount; }
protected:

	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> indexBuffer;

	//Amount of vertices in mesh, not size of vertex buffer
	int vertexCount;	
	//TODO: Add cBuffer for mesh transformation into world space
	//TODO: Add cBuffer for material data 
	//TODO: Add texture for mesh
};