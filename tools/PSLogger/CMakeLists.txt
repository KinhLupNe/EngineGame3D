cmake_minimum_required(VERSION 3.8)
project(PSLogger LANGUAGES CXX)

# Mặc định build Debug nếu không chỉ định
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Đảm bảo Windows Console API
add_definitions(-DWINVER=0x0501 -D_WIN32_WINNT=0x0501)

# Chuẩn C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tạo executable
add_executable(PSLogger
        PSLogger.cpp
)
target_link_libraries(PSLogger PRIVATE shlwapi)

# Cấu hình compiler flags theo config
target_compile_options(PSLogger PRIVATE
        $<$<CONFIG:Debug>:-g;-O0>
        $<$<CONFIG:Release>:-O2>
)

# Xuất binary ra out/bin
set_target_properties(PSLogger PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../out/bin"
)


