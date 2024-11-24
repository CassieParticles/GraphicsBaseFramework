#include "Window.h"
#include "Window.h"

#include <GLFW/glfw3.h>
#include <d3dcompiler.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <iostream>

#include <graphicsEngine/Input.h>

void checkError(HRESULT errorCode, const std::string& errorMessage)
{
	if (FAILED(errorCode))
	{
		std::cerr << errorMessage;
		throw;
	}
}

Window::Window(const std::string& windowTitle, int windowWidth, int windowHeight) :width{ windowWidth },height{windowHeight}
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize glfw\n";
		throw;
	}

	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);

	if (!window)
	{
		std::cerr << "Failed to create GLFW window\n";
		throw;
	}

	//Set the user pointer for the glfwwindow to this
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, Window::handleResize);

	//Create DXGI factory
	checkError(CreateDXGIFactory1(IID_PPV_ARGS(&factory)), "Failed to create DXGIFactory\n");

	//Debug mode enables the debug layer
#ifdef DEBUG
	constexpr D3D11_CREATE_DEVICE_FLAG debugFlag = D3D11_CREATE_DEVICE_DEBUG;
#else 
	constexpr D3D11_CREATE_DEVICE_FLAG debugFlag = (D3D11_CREATE_DEVICE_FLAG)0;
#endif

	//Set up the D3D device and device context
	constexpr D3D_FEATURE_LEVEL deviceFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	checkError(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, debugFlag, &deviceFeatureLevel, 1, D3D11_SDK_VERSION, &device, nullptr, &deviceContext), "Failed to create device/device context\n");

	//Create swapchain
	//TODO: Allow user to change these
	//TODO: Allow user to resize swapchain when screen is resized
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc
	{
		width,
		height,
		DXGI_FORMAT_B8G8R8A8_UNORM,
		false,
		{1,0},
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		2,
		DXGI_SCALING_STRETCH,
		DXGI_SWAP_EFFECT_FLIP_DISCARD,
		DXGI_ALPHA_MODE_IGNORE,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING
	};

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullScreenDesc{};
	fullScreenDesc.Windowed = true;

	checkError(factory->CreateSwapChainForHwnd(device.Get(), glfwGetWin32Window(window), &swapChainDesc, &fullScreenDesc, nullptr, &swapChain),"Failed to create swapchain\n");
	checkError(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer), "Get back buffer\n");

	//Create depth texture
	D3D11_TEXTURE2D_DESC depthTexDesc
	{
		width,
		height,
		1,
		1,
		DXGI_FORMAT_D32_FLOAT,	//TODO: Change to allow stencil buffer
		{1,0},
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_DEPTH_STENCIL,
		0,
		0
	};

	checkError(device->CreateTexture2D(&depthTexDesc, 0, &depthBuffer),"Failed to create depth texture\n");

	//Create RTV and DSV
	checkError(device->CreateRenderTargetView(backBuffer.Get(), 0, &backBufferRTV),"Failed to create RTV\n");
	checkError(device->CreateDepthStencilView(depthBuffer.Get(), 0, &backBufferDSV),"Failed to create DSV\n");

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	input = std::make_unique<InputHandler>(this);
}

Window::Window(Window&& other)
{
	//Copy over basic data
	window = other.window;
	width = other.width;
	height = other.height;

	factory = std::move(other.factory);
	swapChain = std::move(other.swapChain);

	backBuffer = std::move(other.backBuffer);
	depthBuffer = std::move(other.depthBuffer);

	device = std::move(other.device);
	deviceContext = std::move(other.deviceContext);

	backBufferRTV = std::move(other.backBufferRTV);
	backBufferDSV = std::move(other.backBufferDSV);
	depthStencilState = std::move(other.depthStencilState);
	viewport = std::move(other.viewport);

	input = std::move(other.input);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	window = nullptr;
}

bool Window::getWindowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::clearBackBuffer()
{
	//clear the render target view, (cast colour to float array for function)
	deviceContext->ClearRenderTargetView(backBufferRTV.Get(), (float*) &clearColour);
	deviceContext->ClearDepthStencilView(backBufferDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	UpdateF(*input);
}

void Window::presentBackBuffer()
{
	//TODO: allow user to choose if they want vsync enabled
	swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
}

void Window::bindRenderTarget()
{
	deviceContext->OMSetRenderTargets(1, backBufferRTV.GetAddressOf(), backBufferDSV.Get());
	deviceContext->RSSetViewports(1, &viewport);
}

HWND Window::getHWND()
{
	return glfwGetWin32Window(window);
}

void Window::UpdateF(InputHandler& input)
{
	input.Update();
}

void Window::setSize(int width, int height)
{
	this->width = width;
	this->height = height;

	//TODO: Update window size cbuffer when that exists
}

void Window::handleResize(GLFWwindow* window, int width, int height)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->setSize(width, height);
}
