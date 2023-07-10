//HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#define IDM_FILE_OPEN 1001
#define IDM_FILE_SAVE 1002
#define IDM_HELP_ABOUT 2001

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

//Global variables
// the main windows class name.

static TCHAR szWindowsClass[] = _T("DesktopApp");


// The string that apears in the application's title bar

static	TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application by TechVendi");


// Stored instance handle for use in Wind32 API calls such as FindResource
HINSTANCE hInst;
HWND hButton;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void OnButtonClick()
{
	MessageBox(NULL, _T("Button clicked!"), _T("Button Click Event"), MB_OK);
}

void OnMenuItemClicked(int menuItemId)
{
	// Handle menu item click event
	switch (menuItemId)
	{
	case IDM_FILE_OPEN:
		// perform open file operation
		MessageBox(NULL, _T("Open file clicked!"), _T("Menu Item Clicked"), MB_OK);
		break;
	case IDM_FILE_SAVE:
		// Perform save file operation
		MessageBox(NULL, _T("Save file clicked!"), _T("Menu Item Clicked"), MB_OK);
		break;
	case IDM_HELP_ABOUT:
		// Display about dialog
		MessageBox(NULL, _T("About clicked!"), _T("Menu Item is Clicked"), MB_OK);
		break;

	}
}





int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR	lpCmdLine,
	_In_ int	nCmdShow
)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		return 1;

	}

	// Store instance handle in our global variable
	hInst = hInstance;
	//the parameters to CreateWindowEx explained:
	//WS_Ex_OVERLAPPEDWINDOW : An optional extended window style.
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
   // WS_OVERLAPPEDWINDOW: the type of window to create
   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
   // 500, 100: initial size (width, length)
   // NULL: the parent of this window
   // NULL: this application does not have a menu bar
   // hInstance: the first parameter from WinMain
   // NULL: not used in this application


	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowsClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);


	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		return 1;

	}

	// Create the main menu
	HMENU hMenu = CreateMenu();
	HMENU hFileMenu = CreatePopupMenu();
	HMENU hHelpMenu = CreatePopupMenu();


	// Add menu items to the File menu

	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_OPEN, _T("Open"));
	AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVE, _T("Save"));


	// Add menu to the help menu
	AppendMenu(hHelpMenu, MF_STRING, IDM_HELP_ABOUT, _T("About"));


	// add the file menu and help menus to the main menu

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, _T("File"));
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, _T("Help"));

	hButton = CreateWindow(
		_T("BUTTON"),					// Button class name
		_T("Click Me"), // Button Text
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, //Button style
		200, 50, 100, 30,		/// Button position and size
		hWnd,	// Parent window handler
		NULL, // Button ID (not used in this example
		hInstance, // Application instance handle
		NULL,	// Additional data (not used in this example)

		);


	//set the main menu for the window

	SetMenu(hWnd, hMenu);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	//The parameters to ShowWindow explained:
	//hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);


	// Main message loop;
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows desktop! Welcome to almayas private limited");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// Here your application is laid out.
	  // For this introduction, we just print out "Hello, Windows desktop!"
	  // in the top left corner.
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application-specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
	{
		//check if a menu item or  the button was clicked
		if (HIWORD(wParam) == 0)
		{
			int menuItemId = LOWORD(wParam);
			OnMenuItemClicked(menuItemId);

		}
		else if (lParam == (LPARAM)hButton && HIWORD(wParam) == BN_CLICKED)
		{
			OnButtonClick();

		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
