# CMakeList.txt : CMake project for DnDVirtualReality, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories("glm/")

# Add source to this project's executable.
add_executable(DnDVirtualReality "ObjToVbo.cpp" "ObjToVbo.h"
								  "Mesh.cpp" "Mesh.h" 
								  "Face.cpp" "Face.h")


# TODO: Add tests and install targets if needed.
#add_subdirectory("Models/")
#add_subdirectory("Shaders/")
#add_subdirectory("Textures/")