#include "Shader.h"
#include <d3dcompiler.h>
#include <iostream>

//Internal function used by all shader types to compile bytecode, not used elsewhere in engine
void compileByteCode(ID3D11Device* device, const std::wstring& filePath, const std::string& profile, Microsoft::WRL::ComPtr<ID3D10Blob>& bytecodeOut)
{
	Microsoft::WRL::ComPtr<ID3D10Blob> tempShaderByteCode;
	Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage;

	//Compiles the shader into bytecode, returns error if compilation fails
	HRESULT errorCode = D3DCompileFromFile(filePath.data(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "Main", profile.data(), D3DCOMPILE_ENABLE_STRICTNESS, 0, &tempShaderByteCode, &errorMessage);
	if (FAILED(errorCode))
	{
		//Check if file not found error
		if (errorCode == 0x80070002)
		{
			std::cerr << "Failed to find shader at path specified\n";
		}
		if (errorMessage != nullptr)
		{
			std::cerr << "Compilation message" << static_cast<const char*>(errorMessage->GetBufferPointer()) << "\n";
		}
		throw;
	}
	//Compiled successfully, move compiled bytecode to output
	bytecodeOut = std::move(tempShaderByteCode);
}

VertexShader::VertexShader(ID3D11Device* device, const std::wstring& filePath)
{
	CompileShader(device, filePath);
}

void VertexShader::bindShader(ID3D11DeviceContext* deviceContext)
{
	deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
}

void VertexShader::CompileShader(ID3D11Device* device, const std::wstring& filePath)
{
	//Compile shader into bytecode
	compileByteCode(device, filePath, "vs_5_0", byteCode);
	HRESULT errorCode = device->CreateVertexShader(byteCode->GetBufferPointer(), byteCode->GetBufferSize(), nullptr, &vertexShader);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create vertex shader\n";
		throw;
	}
}

PixelShader::PixelShader(ID3D11Device* device, const std::wstring& filePath)
{
	CompileShader(device, filePath);
}

void PixelShader::bindShader(ID3D11DeviceContext* deviceContext)
{
	deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);
}

void PixelShader::CompileShader(ID3D11Device* device, const std::wstring& filePath)
{
	//Compile shader into bytecode
	compileByteCode(device, filePath, "ps_5_0", byteCode);
	HRESULT errorCode = device->CreatePixelShader(byteCode->GetBufferPointer(), byteCode->GetBufferSize(), nullptr, &pixelShader);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create pixel shader\n";
		throw;
	}
}