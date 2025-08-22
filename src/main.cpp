#include <windows.h>
#include <string>
#include <print>
#include <format>

// Window procedure to handle messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        {
            // Create OK button
            CreateWindow(
                L"BUTTON",  // Predefined class
                L"OK",      // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
                150,        // x position
                100,        // y position
                100,        // Button width
                30,         // Button height
                hwnd,       // Parent window
                (HMENU)1,   // Button ID
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL);      // Pointer not needed
        }
        return 0;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case 1:  // OK button clicked
                std::println("OK button clicked - Exiting application");
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
            }
        }
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Draw "Hello, World!" text
            RECT rect;
            GetClientRect(hwnd, &rect);
            rect.bottom = 80;  // Position text above button
            
            SetTextAlign(hdc, TA_CENTER);
            DrawText(hdc, L"Hello, World!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

            EndPaint(hwnd, &ps);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Allocate a console for this GUI application to demonstrate C++23 output
    if (AllocConsole())
    {
        // Redirect stdout to the console
        FILE* pCout;
        freopen_s(&pCout, "CONOUT$", "w", stdout);
        
        // Demonstrate C++23 std::print and std::println
        std::println("Windows C++ Application Starting...");
        std::println("Using C++23 modern output features!");
        
        int appVersion = 1;
        std::string appName = "WinApp";
        std::println("Application: {} v{}", appName, appVersion);
        
        // Format example
        std::string formatted = std::format("Window will be created at {}:{}", "default position", "default size");
        std::println("{}", formatted);
    }
    
    // Register the window class
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class
        L"Windows C++ Application",     // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    std::println("Window created successfully - entering message loop");

    // Run the message loop
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}