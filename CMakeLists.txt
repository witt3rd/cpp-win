cmake_minimum_required(VERSION 4.1)

# Automatic vcpkg integration
# Check for vcpkg toolchain file in order of precedence:
# 1. CMAKE_TOOLCHAIN_FILE already set (e.g., from command line)
# 2. VCPKG_ROOT environment variable
# 3. Common vcpkg installation locations
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VCPKG_ROOT})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
        message(STATUS "Using vcpkg from VCPKG_ROOT: $ENV{VCPKG_ROOT}")
    elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
        message(STATUS "Using local vcpkg installation")
    elseif(EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
        message(STATUS "Using system vcpkg at C:/vcpkg")
    elseif(EXISTS "C:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "C:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
        message(STATUS "Using system vcpkg at C:/tools/vcpkg")
    else()
        message(WARNING "vcpkg not found. Please set VCPKG_ROOT environment variable or install vcpkg")
    endif()
endif()

project(winapp CXX)

set(CMAKE_CXX_STANDARD 20)  # C++20 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Windows definitions
add_compile_definitions(
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    _WIN32_WINNT=0x0A00  # Windows 10
    WINVER=0x0A00
    UNICODE
    _UNICODE
)

# Find packages from vcpkg
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# Main executable - Windows application (not console)
add_executable(${PROJECT_NAME} WIN32
    src/main.cpp
)

# Link Windows libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        user32.lib      # Windows User Interface
        gdi32.lib       # Windows Graphics Device Interface
        kernel32.lib    # Windows Base APIs
        shell32.lib     # Windows Shell API
        comctl32.lib    # Common Controls
        fmt::fmt        # fmt library for formatting
        spdlog::spdlog  # spdlog for logging
)

# Enable proper exception handling
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /EHsc   # Enable C++ exceptions
        /W4     # Warning level 4
    )
endif()

# Set this project as the default startup project in Visual Studio
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

message(STATUS "===========================================")
message(STATUS "  Windows C++ Application Template")
message(STATUS "===========================================")
