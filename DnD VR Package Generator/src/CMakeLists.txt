﻿# CMakeList.txt : CMake project for DnDVirtualReality, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories("glm/")
include_directories("wxwidgets/")
include_directories("tinyxml2/")
include_directories("opencv2/")

# Add source to this project's executable.
add_executable(DnDVirtualReality "ObjToVbo.cpp" "ObjToVbo.h"
								  "Mesh.cpp" "Mesh.h" 
								  "app.cpp" "app.h"
								  "Exporter.cpp" "Exporter.h"
								  "tinyxml2.cpp" "tinyxml2.h"
								  "QrCode.cpp" "QrCode.hpp"
								  "Face.cpp" "Face.h" "DnDVRPackageGenerator.cpp" "DnDVRPackageGenerator.h")

TARGET_LINK_LIBRARIES (DnDVirtualReality ${OpenCV_LIBS})


# TODO: Add tests and install targets if needed.
#add_subdirectory("Models/")
#add_subdirectory("Shaders/")
#add_subdirectory("Textures/")