
list(APPEND GRAPHICS "engine/test.cpp")

cmake_minimum_required (VERSION 3.8)

add_library(GraphicsFramework ${GRAPHICS})

#Include framework header files and libraries used within framework
target_include_directories(GraphicsFramework PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(GraphicsFramework PUBLIC "${CMAKE_CURRENT_LIST_DIR}/libraries/includes")

#Define macros "debug" or "release" for the debug and release builds of the project
if(CMAKE_BUILD_TYPE MATCHES "Debug")
	target_compile_definitions(GraphicsFramework PRIVATE "DEBUG")
else()
	target_compile_definitions(GraphicsFramework PRIVATE "RELEASE")
endif()

#Include glfw statically(Library for creating windows)
add_library(GLFW STATIC IMPORTED GLOBAL)	#Create library
set_property(TARGET GLFW PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/libraries/GLFW/glfw3.lib")	#Set location to the .lib file
target_link_libraries(GraphicsFramework GLFW)	#Add library to framework

#Add libraries for d3d11
#Add Direct3D11 libraries (static libraries)
find_library("d3d11.lib" PATH "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("dxgi.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("d3dcompiler.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("winmm.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")
find_library("dxguid.lib" PATH "C:/Program Files( x86)/Windows Kits/10/Lib/10.0.22000.0/")

target_link_libraries(GraphicsFramework d3d11)
target_link_libraries(GraphicsFramework dxgi)
target_link_libraries(GraphicsFramework d3dcompiler)
target_link_libraries(GraphicsFramework winmm)
target_link_libraries(GraphicsFramework dxguid)

#Add custom target to copy shaders folder into the output directory

add_custom_target(copyFrameworkShaders ALL
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_LIST_DIR}/shaders" "${CMAKE_BINARY_DIR}/shaders"
COMMENT "Copied shaders in graphics framework" VERBATIM
)

add_dependencies(GraphicsFramework copyFrameworkShaders)