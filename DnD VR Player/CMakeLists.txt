# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("DnDVirtualReality")

list(APPEND CMAKE_PREFIX_PATH "deps/")

find_package(GLEW REQUIRED)
include_directories("include/")
link_libraries(${GLEW_LIBRARIES})
if(NOT GLEW_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT GLEW_FOUND)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_libraries(${GLUT_LIBRARIES})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

find_package(DevIL REQUIRED)
link_libraries(${IL_LIBRARIES})
include_directories(${IL_INCLUDE_DIR})
if(NOT DevIL_FOUND)
  message(ERROR " Devil not found!")
endif(NOT DevIL_FOUND)

link_libraries("D:/opencv/build/x64/vc15/lib/opencv_world440d.lib")
include_directories("D:/opencv/build/include")

#find_package( OpenCV REQUIRED )
#link_libraries(${OPENCV_LIBS})
#include_directories( ${OpenCV_INCLUDE_DIRS} )
#if(NOT OpenCV_FOUND)
#  message(ERROR " OpenCV not found!")
#endif(NOT OpenCV_FOUND)

# Include sub-projects.
add_subdirectory ("src")


