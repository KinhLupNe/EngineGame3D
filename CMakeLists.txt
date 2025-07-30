# CMakeList.txt : CMake project for Engine3D, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Engine3D")

# Add source to this project's executable.
add_executable (Engine3D "Engine3D.cpp" "Engine3D.h" "Geometry/Mesh.cpp" "Geometry/Vertex.cpp" "Geometry/Model.cpp" "Core/Buffer.cpp" "Core/Camera.cpp" "Render/Render.cpp" "Math/Math.cpp" "Pipeline/Pipeline.cpp" "Pipeline/Culling.cpp" "Scene/Scene.cpp" "Pipeline/Rasterization.cpp" "Render/FrameBuffer.cpp" "Core/Buffer.h" "Core/Camera.h" "Geometry/Model.h" "Geometry/Mesh.h" "Geometry/Vertex.h" "Render/Render.h" "Scene/Scene.h" "Math/Math.h" "Pipeline/Pipeline.h" "Pipeline/Culling.h" "Pipeline/Rasterization.h" "Render/FrameBuffer.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property (TARGET Engine3D PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
