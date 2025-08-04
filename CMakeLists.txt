cmake_minimum_required(VERSION 3.10)

project(Engine3D LANGUAGES CXX)

# Nếu chưa chỉ định, ép build Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# MSVC: Enable Edit&Continue cho Debug
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
          "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,"
          " $<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,"
          " $<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# C++20
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Khai báo executable và sources
add_executable(Engine3D
        Engine3D.cpp  Engine3D.h
        Geometry/Mesh.cpp  Geometry/Mesh.h
        Geometry/Vertex.cpp Geometry/Vertex.h
        Geometry/Model.cpp  Geometry/Model.h
        Core/Buffer.cpp     Core/Buffer.h
        Core/Camera.cpp     Core/Camera.h
        Render/Render.cpp   Render/Render.h
        Render/FrameBuffer.cpp Render/FrameBuffer.h
        Math/Math.cpp       Math/Math.h
        Pipeline/Pipeline.cpp      Pipeline/Pipeline.h
        Pipeline/Culling.cpp       Pipeline/Culling.h
        Pipeline/Rasterization.cpp Pipeline/Rasterization.h
        Scene/Scene.cpp      Scene/Scene.h
        Debugger/DebugLogger.cpp   Debugger/DebugLogger.h
	Game/GameRender/GameRender.cpp Game/GameRender/GameRender.h
	Game/World/Block.cpp Game/World/Block.h
	Game/World/World.cpp Game/World/World.h
)

# Flags chung cho Debug/Release
if(MSVC)
  # MSVC: chỉ tối ưu Release
  target_compile_options(Engine3D PRIVATE
          $<$<CONFIG:Release>:/O2 /DNDEBUG>
  )
else()
  # GCC/Clang trên UNIX (Linux/macOS): cho phép sanitizers
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND UNIX)
    target_compile_options(Engine3D PRIVATE
            $<$<CONFIG:Debug>:-g;-O0;-fsanitize=address,undefined>
            $<$<CONFIG:Release>:-O2;-DNDEBUG>
    )
    target_link_options(Engine3D PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address,undefined>
    )
  else()
    # Trên Windows (MinGW) hoặc các compiler khác, không bật sanitizer
    target_compile_options(Engine3D PRIVATE
            $<$<CONFIG:Debug>:-g;-O0>
            $<$<CONFIG:Release>:-O2;-DNDEBUG>
    )
  endif()
endif()

# PSLogger subproject
add_subdirectory(tools/PSLogger)
