# GraphicsBaseFramework
A base graphics framework for the Non Reality Engine (split into a separate module so it can be re-used for other coursework)

The framework will contain:

Window management:
	-Initialization of the window through glfw
	-Initialization of basic DirectXObjects (device, device context, swapchain)
	-Handling of swapchain
	-Handling of resizing

Wrappers for shaders:
	-Compilation
	-Binding

Wrappers for meshes:
	-Creation
	-Rendering
	-Stores constant buffer for transformation into world space
	
Lighting:
	-Spotlight
	-Pointlight
	-Directional light
	-Ambient light

Materials:
	-Colour

View:
	-Camera perspective
	-Stores constant buffer for projection and transformation (combined)
	-Stores perspective data and position/rotation

Basic shaders:
	-Shaders written for rendering object with lighting and material

Renderer:
	-Allow support for deffered rendering?
