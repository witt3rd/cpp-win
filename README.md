# Windows C++ Application Template

A clean, modern template for Windows C++ desktop application development using Win32 API, CMake, and vcpkg.

## Features

- ✅ **Simple Win32 GUI Application** - Basic window with Hello World
- ✅ **Modern C++20** - Latest language features
- ✅ **CMake Build System** - Cross-platform build configuration
- ✅ **vcpkg Integration** - Automatic dependency management
- ✅ **Visual Studio Support** - Full IDE integration
- ✅ **x64 and ARM64** - Build for both architectures

## Prerequisites

### Required Tools

```powershell
# Visual Studio 2022 (Community edition is free)
winget install Microsoft.VisualStudio.2022.Community

# CMake
winget install Kitware.CMake

# Git (if not already installed)
winget install Git.Git

# vcpkg (C++ package manager) - Optional, but recommended
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
C:\vcpkg\bootstrap-vcpkg.bat
setx VCPKG_ROOT "C:\vcpkg"
```

### Visual Studio Configuration

Ensure you have the required Windows development components:

1. In Visual Studio Installer, select "Desktop development with C++"
2. Ensure "Windows 10/11 SDK" is checked
3. Install and restart

## Quick Start

### Using as a Template

1. Click "Use this template" on GitHub
2. Create your new repository
3. Clone your new repository:
   ```bash
   git clone https://github.com/yourusername/your-new-project.git
   cd your-new-project
   ```

### Building the Application

#### x64 Build (Intel/AMD)

```powershell
# Configure once
cmake --preset x64

# Build Release
cmake --build --preset x64-release

# Run the application
.\build\Release\winapp.exe
```

#### ARM64 Build (Windows on ARM)

```powershell
# Configure once
cmake --preset arm64

# Build Release
cmake --build --preset arm64-release

# Run
.\build-arm64\Release\winapp.exe
```

#### Debug Builds

```powershell
# For x64 Debug
cmake --build --preset x64-debug

# For ARM64 Debug  
cmake --build --preset arm64-debug
```

## Project Structure

```
your-project/
├── CMakeLists.txt          # CMake configuration
├── CMakePresets.json       # Build presets for x64 and ARM64
├── vcpkg.json             # Package dependencies
├── CLAUDE.md              # AI assistant guidance
├── src/
│   └── main.cpp           # Main Windows application
├── build/                 # x64 build output (generated)
├── build-arm64/          # ARM64 build output (generated)
└── README.md             # This file
```

## Customizing the Template

### 1. Update Project Name

Edit `CMakeLists.txt`:
```cmake
project(your_app_name CXX)
```

Edit `vcpkg.json`:
```json
{
  "name": "your-app-name",
  "version": "1.0.0",
  ...
}
```

### 2. Add Dependencies

Add packages to `vcpkg.json`:
```json
{
  "dependencies": [
    "fmt",
    "spdlog",
    "sqlite3",
    "curl"
  ]
}
```

Then in `CMakeLists.txt`:
```cmake
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(CURL REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        unofficial::sqlite3::sqlite3
        CURL::libcurl
        # ... other libraries
)
```

### 3. Add Source Files

Add new source files to `src/` and update `CMakeLists.txt`:
```cmake
add_executable(${PROJECT_NAME} WIN32
    src/main.cpp
    src/window.cpp
    src/utils.cpp
)
```

## Development in Visual Studio

1. Open the generated solution:
   ```powershell
   # For x64
   start build\winapp.sln
   
   # For ARM64
   start build-arm64\winapp.sln
   ```

2. Set as startup project (automatically done via CMake)
3. Press F5 to build and debug

## Common Tasks

### Adding a Menu

```cpp
// In WM_CREATE handler
HMENU hMenu = CreateMenu();
HMENU hFileMenu = CreatePopupMenu();
AppendMenu(hFileMenu, MF_STRING, ID_FILE_NEW, L"&New");
AppendMenu(hFileMenu, MF_STRING, ID_FILE_OPEN, L"&Open");
AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
AppendMenu(hFileMenu, MF_STRING, ID_FILE_EXIT, L"E&xit");
AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");
SetMenu(hwnd, hMenu);
```

### Adding Icons and Resources

1. Create a resource file `resources.rc`
2. Add to `CMakeLists.txt`:
   ```cmake
   add_executable(${PROJECT_NAME} WIN32
       src/main.cpp
       resources.rc
   )
   ```

### Console Output for Debugging

To enable console output alongside the GUI:
```cpp
// Add at the beginning of wWinMain
AllocConsole();
FILE* pCout;
freopen_s(&pCout, "CONOUT$", "w", stdout);
```

## Troubleshooting

### vcpkg not found

If CMake can't find vcpkg:
1. Set the `VCPKG_ROOT` environment variable
2. Or specify the toolchain file manually:
   ```powershell
   cmake -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake --preset x64
   ```

### Windows SDK not found

Ensure Visual Studio is installed with Windows SDK components.

### Application doesn't start

Check that all required DLLs are present. Use Dependency Walker or `dumpbin /dependents` to check dependencies.

## License

This template is released as public domain. Use it however you want!

## Contributing

Feel free to submit issues and pull requests to improve this template.