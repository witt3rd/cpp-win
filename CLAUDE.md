# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a Windows C++ application template project that provides a clean starting point for developing Windows desktop applications. It includes:

- Modern C++23 standard support (see `llm-docs\cpp\cpp_spec.md` for C++23 modern output guidelines)
- Windows SDK integration for native Windows API programming
- vcpkg package manager for dependencies
- CMake build system with presets for x64 and ARM64
- Simple GUI application with Win32 API

## Build Commands

### x64 Build (Intel/AMD)

```powershell
# Configure once
cmake --preset x64

# Build Release
cmake --build --preset x64-release

# Build Debug
cmake --build --preset x64-debug

# Run the application
.\build\Release\winapp.exe
```

### ARM64 Build (Windows on ARM)

```powershell
# Configure
cmake --preset arm64

# Build Release
cmake --build --preset arm64-release

# Run
.\build-arm64\Release\winapp.exe
```

## Architecture & Key Components

### Technology Stack

- **Windows SDK**: Native Windows API programming
- **Win32 API**: Direct Windows system calls for GUI and system interaction
- **C++23**: Modern C++ features
- **vcpkg**: Package management for C++ libraries
- **CMake**: Cross-platform build system

### Code Organization

```
src/
├── main.cpp          # Main Windows application entry point
└── [additional source files can be added here]
```

## Critical Implementation Details

### Windows Application Entry Point

The application uses `wWinMain` as the entry point for a Windows GUI application (not console).

### Window Creation Pattern

```cpp
// Register window class
WNDCLASS wc = { };
wc.lpfnWndProc = WindowProc;
wc.hInstance = hInstance;
RegisterClass(&wc);

// Create window
HWND hwnd = CreateWindowEx(...);

// Message loop
MSG msg;
while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
```

### Common Windows API Headers

- `<windows.h>` - Core Windows API
- `<commctrl.h>` - Common controls
- `<shellapi.h>` - Shell API functions
- `<shlwapi.h>` - Path and registry utilities

## Dependencies

The project uses vcpkg for dependency management. Currently no external dependencies are required as the project uses C++23 standard library features including:

- **std::format**: Type-safe string formatting (C++20)
- **std::print/std::println**: Direct formatted output (C++23)

Additional libraries can be added to `vcpkg.json` as needed.

## Building for Different Configurations

The project uses CMake presets for simple, consistent builds:

- **x64**: `cmake --preset x64` then `cmake --build --preset x64-release`
- **ARM64**: `cmake --preset arm64` then `cmake --build --preset arm64-release`
- **Debug builds**: Use `x64-debug` or `arm64-debug` presets
- Visual Studio generator is configured automatically in the presets

## Environment Requirements

- **Windows 10/11**: Target platform
- **Visual Studio 2022**: For MSVC compiler
- **CMake 4.1+**: Build system
- **vcpkg**: Package manager (auto-detected from environment or common paths)

## Extending the Template

To add new functionality:

1. Add source files to `src/` directory
2. Update `CMakeLists.txt` to include new source files
3. Add dependencies to `vcpkg.json` if needed
4. Use Windows API or third-party libraries as required

## Common Tasks

### Adding a Menu Bar

```cpp
// In window creation or WM_CREATE
HMENU hMenu = CreateMenu();
HMENU hFileMenu = CreatePopupMenu();
AppendMenu(hFileMenu, MF_STRING, ID_FILE_EXIT, L"Exit");
AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
SetMenu(hwnd, hMenu);
```

### Adding Dialog Boxes

```cpp
MessageBox(hwnd, L"Message", L"Title", MB_OK | MB_ICONINFORMATION);
```

### Handling Keyboard Input

```cpp
case WM_KEYDOWN:
    switch (wParam) {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;
    }
    break;
```

# important-instruction-reminders
- Do what has been asked; nothing more, nothing less.
- NEVER create files unless they're absolutely necessary for achieving your goal.
- ALWAYS prefer editing an existing file to creating a new one.
- NEVER proactively create documentation files (*.md) or README files unless explicitly requested.