
list(APPEND GRAPHICS "graphicsEngine/Window.cpp")
list(APPEND GRAPHICS "graphicsEngine/View.cpp")
list(APPEND GRAPHICS "graphicsEngine/Input.cpp")

list(APPEND GRAPHICS "graphicsEngine/Pipeline/Mesh.cpp")
list(APPEND GRAPHICS "graphicsEngine/Pipeline/InputLayout.cpp")
list(APPEND GRAPHICS "graphicsEngine/Pipeline/Shader.cpp")
list(APPEND GRAPHICS "graphicsEngine/Pipeline/Texture2D.cpp")

cmake_minimum_required (VERSION 3.8)

add_library(GraphicsFramework ${GRAPHICS})

#Include framework header files and libraries used within framework
target_include_directories(GraphicsFramework PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
#target_include_directories(GraphicsFramework PUBLIC "${CMAKE_CURRENT_LIST_DIR}/libraries/includes")
target_include_directories(GraphicsFramework PUBLIC "${CMAKE_CURRENT_LIST_DIR}/engine/VectorMathOverloads.h")

#Define macros "debug" or "release" for the debug and release builds of the project
if(CMAKE_BUILD_TYPE MATCHES "Debug")
	target_compile_definitions(GraphicsFramework PRIVATE "DEBUG")
else()
	target_compile_definitions(GraphicsFramework PRIVATE "RELEASE")
endif()

#Create library for ImGui
file(GLOB IMGUIMAINSOURCE "${CMAKE_CURRENT_LIST_DIR}/imgui/*.cpp")
list(APPEND DearImGuiSource ${IMGUIMAINSOURCE})
list(APPEND DearImGuiSource "${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_dx11.cpp")
list(APPEND DearImGuiSource "${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_glfw.cpp")

add_library(DearImGui STATIC ${DearImGuiSource})

#Add ImGui path
target_include_directories(DearImGui PUBLIC "${CMAKE_CURRENT_LIST_DIR}/imgui")
target_include_directories(DearImGui PUBLIC "${CMAKE_CURRENT_LIST_DIR}/imgui/backends")
target_include_directories(DearImGui PUBLIC "${CMAKE_CURRENT_LIST_DIR}/libraries/includes")

#Include glfw statically(Library for creating windows)
add_library(GLFW STATIC IMPORTED GLOBAL)	#Create library
set_property(TARGET GLFW PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/libraries/GLFW/glfw3.lib")	#Set location to the .lib file
target_link_libraries(DearImGui GLFW)	#Add library to ImGui (allows ImGui to compile with glfw backends)

#Add libraries for d3d11
#Add Direct3D11 libraries (static libraries)
find_library("d3d11.lib" PATH "$ENV{DXSDK_DIR}/Lib")
find_library("dxgi.lib" PATH "$ENV{DXSDK_DIR}/Lib")
find_library("d3dcompiler.lib" PATH "$ENV{DXSDK_DIR}/Lib")
find_library("dxguid.lib" PATH "$ENV{DXSDK_DIR}/Lib")





target_link_libraries(GraphicsFramework d3d11)
target_link_libraries(GraphicsFramework dxgi)
target_link_libraries(GraphicsFramework d3dcompiler)
target_link_libraries(GraphicsFramework dxguid)
target_link_libraries(GraphicsFramework DearImGui)

#Add custom target to copy shaders folder into the output directory

add_custom_target(copyFrameworkShaders ALL
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_LIST_DIR}/shaders" "${CMAKE_BINARY_DIR}/shaders"
COMMENT "Copied shaders in graphics framework" VERBATIM
)

add_dependencies(GraphicsFramework copyFrameworkShaders)