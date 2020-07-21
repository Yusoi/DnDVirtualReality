# CMakeList.txt : CMake project for DnDVirtualReality, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories("glm/")

# Add source to this project's executable.
add_executable(DnDVirtualReality "DnDVirtualReality.cpp" "DnDVirtualReality.h" 
		                         "Engine.cpp" "Engine.h"
								 "Model.cpp" "Model.h"
								 "Light.cpp" "Light.h"
								 "Camera.cpp" "Camera.h"
								 "Actor.cpp" "Actor.h"
								 "Shader.cpp" "Shader.h"
								 "tinyxml2.cpp" "tinyxml2.h"
								 "Tile.cpp" "Tile.h"   
								 "PackageReader.cpp" "PackageReader.h" 
								 "ImageInterpreter.cpp" "ImageInterpreter.h")