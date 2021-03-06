// my65.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "my65.h"
#include "Frame.h"
#include "Mem.h"
#include "CPU.h"


#define UNICODE 1

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND g_hPage;									// handle to the memory page display window
HWND g_hBuddy;									// handle to the UpDown buddy window
HWND g_hUpDown;									// handle to the Updown control
HWND g_hDisasm;									// handle to the disassembly window
HWND g_hCpuA;									// handle to the accumulator display window
HWND g_hCpuX;									// handle to the X-register display window
HWND g_hCpuY;									// handle to the Y-register display window
HWND g_hCpuSP;									// handle to the Stack Pointer display window
HWND g_hCpuPC;									// handle to the Program Counter display window

Mem* pMem = new Mem;							// pointer to the memory object
CPU* pCPU = new CPU;							// pointer to the CPU object



// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY65, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY65));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY65));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY65);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		DrawGUI(hWnd);
		pMem->InitMem();
		pCPU->Reset();
	}
	break;

	case WM_NOTIFY:
	{
		unsigned int nCode = ((LPNMHDR)lParam)->code;
		switch (nCode)
		{
			case UDN_DELTAPOS:
			{
				LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
				int page = lpnmud->iPos + lpnmud->iDelta;
				if ((page > 0xff) | (page < 0)) page = lpnmud->iPos;
			
				std::wstring memString = pMem->PrintMem(page);
				SetWindowText(g_hPage, memString.c_str());
			}
			break;
		}
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			HWND hwndButtonId = (HWND)lParam;

            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDB_RESET:
			{
				TCHAR Buffer[10];
				std::wstring memString;

				pCPU->Reset();
				pMem->InitMem();			

				// Display the CPU registers
				StringCchPrintf(Buffer, _countof(Buffer), _T("%02x"), pCPU->m_A);
				SetWindowText(g_hCpuA, Buffer);

				StringCchPrintf(Buffer, _countof(Buffer), _T("%02x"), pCPU->m_X);
				SetWindowText(g_hCpuX, Buffer);

				StringCchPrintf(Buffer, _countof(Buffer), _T("%02x"), pCPU->m_Y);
				SetWindowText(g_hCpuY, Buffer);

				StringCchPrintf(Buffer, _countof(Buffer), _T("%04x"), pCPU->m_SP);
				SetWindowText(g_hCpuSP, Buffer);

				StringCchPrintf(Buffer, _countof(Buffer), _T("%02x"), pCPU->m_PC);
				SetWindowText(g_hCpuPC, Buffer);


				// Display a page of memory
				SendMessage(g_hUpDown, UDM_SETPOS, 0, 0x00);							// set the initial page to 0 on the UpDown control
				memString = pMem->PrintMem(0x00);
				SetWindowText(g_hPage, memString.c_str());
			}
			break;
			case IDB_RUN:
			{
				SetWindowText(hwndButtonId, L"Run msg");
			}
			break;
			case IDB_STOP:
			{
				SetWindowText(hwndButtonId, L"Stop msg");
			}
			break;
			case IDB_STEP:
			{
				SetWindowText(hwndButtonId, L"Step msg");
			}
			break;
			case IDB_LOAD:
			{
				SetWindowText(hwndButtonId, L"Load msg");
			}
			break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
