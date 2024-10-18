#include "InputLayout.h"

InputLayout::InputLayout()
{
}

InputLayout::InputLayout(ID3D11Device* device, ID3D10Blob* VSByteCode, D3D11_INPUT_ELEMENT_DESC* inputArray, int inputCount)
{
	addInputLayout(device, VSByteCode, inputArray, inputCount);
}

InputLayout::InputLayout(InputLayout&& other)
{
	inputLayout = other.inputLayout;
}

InputLayout::~InputLayout()
{
}

void InputLayout::addInputLayout(ID3D11Device* device, ID3D10Blob* VSByteCode, D3D11_INPUT_ELEMENT_DESC* inputArray, int inputCount)
{

	device->CreateInputLayout(inputArray, inputCount, VSByteCode->GetBufferPointer(), VSByteCode->GetBufferSize(), &inputLayout);
}

void InputLayout::useInputLayout(ID3D11DeviceContext* deviceContext)
{
	deviceContext->IASetInputLayout(inputLayout.Get());
}


