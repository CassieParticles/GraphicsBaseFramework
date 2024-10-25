#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <string>
#include <iostream>


//Can be represented as char (leading 2 bits unused)
enum ShaderTypes
{
	VERTEX_SHADER = 1,
	HULL_SHADER = 2,
	DOMAIN_SHADER = 4,
	GEOMETRY_SHADER = 8,
	PIXEL_SHADER = 16,
	COMPUTE_SHADER = 32
};

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

class Shader
{

public:
	Shader() = default;
	~Shader() = default;
	Shader(Shader& other) = delete;	//Copy constructor disabled, no way to copy shader
	Shader(Shader&& other) = delete;
	
	virtual void bindShader(ID3D11DeviceContext* deviceContext) = 0;

	//Return a temporary pointer to the byte code for the shader
	ID3D10Blob* getByteCode() { return byteCode.Get(); }
protected:
	virtual void CompileShader(ID3D11Device* device, const std::wstring& filePath) = 0;

	ComPtr<ID3D10Blob> byteCode;
};

class VertexShader :public Shader
{
public:
	VertexShader(ID3D11Device* device, const std::wstring& filePath);
	~VertexShader() = default;
	
	//Bind shader to pipeline
	void bindShader(ID3D11DeviceContext* deviceContext) override final;


protected:
	ComPtr<ID3D11VertexShader> vertexShader;

	void CompileShader(ID3D11Device* device, const std::wstring& filePath) override final;
};

class PixelShader : public Shader
{
public:
	PixelShader(ID3D11Device* device, const std::wstring& filePath);
	~PixelShader() = default;

	void bindShader(ID3D11DeviceContext* deviceContext) override final;

protected:
	ComPtr<ID3D11PixelShader> pixelShader;

	void CompileShader(ID3D11Device* device, const std::wstring& filePath) override final;
};