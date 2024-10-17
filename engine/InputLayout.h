#pragma once

#include <wrl.h>
#include <d3d11.h>

class InputLayout
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	InputLayout();
	InputLayout(ID3D11Device* device,ID3D10Blob* VSByteCode, D3D11_INPUT_ELEMENT_DESC* inputArray, int inputCount);
	InputLayout(InputLayout& other) = delete;	//Copy constructor disabled, cannot copy gpu data without deviceContext
	InputLayout(InputLayout&& other);
	~InputLayout();

	void addInputLayout(ID3D11Device* device, ID3D10Blob* VSByteCode, D3D11_INPUT_ELEMENT_DESC* inputArray, int inputCount);

	void useInputLayout(ID3D11DeviceContext* deviceContext);
protected:
	ComPtr<ID3D11InputLayout> inputLayout;
};