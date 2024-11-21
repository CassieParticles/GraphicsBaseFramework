#pragma once

#include <string>
#include <memory>

#include <d3d11.h>
#include <dxgi1_3.h>
#include <wrl.h>
#include <DirectXMath.h>




class GLFWwindow;
class InputHandler;

class Window
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	Window(const std::string& windowTitle, int windowWidth, int windowHeight);
	Window(Window& window) = delete;	//Do not copy the window, should only be one
	Window(Window&& other);
	~Window();

	bool getWindowShouldClose();
	GLFWwindow* getWindow() { return window; }

	void changeClearColour(DirectX::XMFLOAT4 newColour) { this->clearColour = newColour; }
	void clearBackBuffer();
	void presentBackBuffer();

	void bindRenderTarget();

	int getWidth() { return width; }
	int getHeight() { return height; }
	float getAspectRatio() { return static_cast<float>(width) / height; }

	ComPtr<ID3D11Device> getDevice() { return device; }
	ComPtr<ID3D11DeviceContext> getDeviceContext() { return deviceContext; }

	//Get a pointer to the input
	InputHandler* getInput() { return input.get(); }

	//Friend function from input, called this way so only window can update the input
	void UpdateF(InputHandler& input);
protected:
	
	//Window data
	GLFWwindow* window;

	std::unique_ptr<InputHandler> input;

	int width{};
	int height{};

	DirectX::XMFLOAT4 clearColour{};

	void setSize(int width, int height);
	static void handleResize(GLFWwindow* window, int width, int height);



	//DirectX objects
	ComPtr<IDXGIFactory2> factory;
	ComPtr<IDXGISwapChain1> swapChain;

	ComPtr<ID3D11Texture2D> backBuffer;
	ComPtr<ID3D11Texture2D> depthBuffer;

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;

	//TODO: Update this to use render target class when implemented
	ComPtr<ID3D11RenderTargetView> backBufferRTV;
	ComPtr<ID3D11DepthStencilView> backBufferDSV;
	ComPtr<ID3D11DepthStencilState> depthStencilState;
	D3D11_VIEWPORT viewport;
	
};