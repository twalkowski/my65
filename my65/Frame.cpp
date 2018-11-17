#include "stdafx.h"
#include "Frame.h"
#include "resource.h"

#pragma comment(lib, "comctl32.lib") 

// Enable Visual Style 
#if defined _M_IX86 
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"") 
#elif defined _M_IA64 
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"") 
#elif defined _M_X64 
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"") 
#else 
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 
#endif 
#pragma endregion 


INITCOMMONCONTROLSEX icex;						// Structure for control initialization

const unsigned int valMin = 0;					// the range of values for the UpDown control
const unsigned int valMax = 255;


void DrawGUI(HWND window)
{
	// Get a fixed-font style to show CPU and menory values
	HFONT hFont = (HFONT)GetStockObject(ANSI_FIXED_FONT);

	//==========
	//  Control buttons
	//========== 

	// Group box container for buttons
	CreateWindow(L"Button", L"Actions", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 16, 16, 112, 200, window, (HMENU)IDB_GROUP1, NULL, NULL);

	// RESET
	CreateWindow(L"Button", L"Reset", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 32, 48, 80, 24, window, (HMENU)IDB_RESET, NULL, NULL);

	// RUN
	CreateWindow(L"Button", L"Run", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 32, 80, 80, 24, window, (HMENU)IDB_RUN, NULL, NULL);

	// STOP
	CreateWindow(L"Button", L"Stop", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 32, 112, 80, 24, window, (HMENU)IDB_STOP, NULL, NULL);

	// STEP
	CreateWindow(L"Button", L"Step", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 32, 144, 80, 24, window, (HMENU)IDB_STEP, NULL, NULL);

	// LOAD - a binary image
	CreateWindow(L"Button", L"Load", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 32, 176, 80, 24, window, (HMENU)IDB_LOAD, NULL, NULL);

	//========== 
	//  CPU registers
	//========== 

	// Group box container for CPU registers
	CreateWindow(L"Button", L"CPU", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 144, 16, 132, 200, window, (HMENU)IDB_GROUP1, NULL, NULL);

	// Accumulator
	CreateWindow(L"static", L"A:", WS_CHILD | WS_VISIBLE | SS_RIGHT, 160, 48, 48, 20, window, NULL, NULL, NULL);
	g_hCpuA = CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY,
		216, 48, 48, 20, window, (HMENU)IDT_ACCUM, NULL, NULL);
	SendMessage(g_hCpuA, WM_SETFONT, (WPARAM)hFont, TRUE);

	// X register
	CreateWindow(L"static", L"X:", WS_CHILD | WS_VISIBLE | SS_RIGHT, 160, 76, 48, 20, window, NULL, NULL, NULL);
	g_hCpuX = CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY,
		216, 76, 48, 20, window, (HMENU)IDT_X, NULL, NULL);
	SendMessage(g_hCpuX, WM_SETFONT, (WPARAM)hFont, TRUE);

	// Y register
	CreateWindow(L"static", L"Y:", WS_CHILD | WS_VISIBLE | SS_RIGHT, 160, 104, 48, 20, window, NULL, NULL, NULL);
	g_hCpuY = CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY,
		216, 104, 48, 20, window, (HMENU)IDT_Y, NULL, NULL);
	SendMessage(g_hCpuY, WM_SETFONT, (WPARAM)hFont, TRUE);

	// Stack Pointer
	CreateWindow(L"static", L"SP:", WS_CHILD | WS_VISIBLE | SS_RIGHT, 160, 132, 48, 20, window, NULL, NULL, NULL);
	g_hCpuSP = CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY,
		216, 132, 48, 20, window, (HMENU)IDT_SP, NULL, NULL);
	SendMessage(g_hCpuSP, WM_SETFONT, (WPARAM)hFont, TRUE);

	// Program Counter
	CreateWindow(L"static", L"PC:", WS_CHILD | WS_VISIBLE | SS_RIGHT, 160, 160, 48, 20, window, NULL, NULL, NULL);
	g_hCpuPC = CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY,
		216, 160, 48, 20, window, (HMENU)IDT_PC, NULL, NULL);
	SendMessage(g_hCpuPC, WM_SETFONT, (WPARAM)hFont, TRUE);


	//========== 
	//  Disassembly display
	//========== 

	// Group box container for disassembly window
	CreateWindow(L"Button", L"Disassembly", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 292, 16, 320, 200, window, (HMENU)IDB_GROUP1, NULL, NULL);
	g_hDisasm = CreateWindow(L"Edit", L"f834:  7d 45 ad  lda ($ad45) ",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_MULTILINE | ES_READONLY,
		308, 48, 288, 152, window, (HMENU)IDB_GROUP1, NULL, NULL);
	SendMessage(g_hDisasm, WM_SETFONT, (WPARAM)hFont, TRUE);


	//========== 
	//  Memory display
	//========== 

	// Group box container for memory
	CreateWindow(L"Button", L"Memory", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 16, 216, 676, 300, window, (HMENU)IDB_GROUP1, NULL, NULL);

	// Memory Page display
	g_hPage = CreateWindow(L"Edit", L"text...", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_MULTILINE | ES_READONLY,
		32, 272, 620, 224, window, (HMENU)IDT_PAGE, NULL, NULL);
	SendMessage(g_hPage, WM_SETFONT, (WPARAM)hFont, TRUE);

	//Create the UpDown buddy window
	icex.dwICC = ICC_STANDARD_CLASSES;    // Set the Initialization Flag value.
	InitCommonControlsEx(&icex);          // Initialize the Common Controls Library to use 
										  // Buttons, Edit Controls, Static Controls, Listboxes, 
										  // Comboboxes, and  Scroll Bars.

	g_hBuddy = CreateWindowEx(WS_EX_LEFT | WS_EX_CLIENTEDGE | WS_EX_CONTEXTHELP,    //Extended window styles.
		WC_EDIT,
		NULL,
		WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER    // Window styles.
		| ES_NUMBER | ES_LEFT,                     // Edit control styles.
		32, 240,
		80, 24,
		window,
		NULL,
		NULL,
		NULL);


	// Create an UpDown control
	icex.dwICC = ICC_UPDOWN_CLASS;    // Set the Initialization Flag value.
	InitCommonControlsEx(&icex);      // Initialize the Common Controls Library.

	g_hUpDown = CreateWindowEx(WS_EX_LEFT | WS_EX_LTRREADING,
		UPDOWN_CLASS,
		NULL,
		WS_CHILDWINDOW | WS_VISIBLE
		| UDS_AUTOBUDDY | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
		0, 0,
		0, 0,         // Set to zero to automatically size to fit the buddy window.
		window,
		NULL,
		NULL,
		NULL);

	SendMessage(g_hUpDown, UDM_SETRANGE, 0, MAKELPARAM(valMax, valMin));    // Sets the controls direction 
																			// and range.
	SendMessage(g_hUpDown, UDM_SETBASE, 16, 0);								// show hex digits in buddy window



}
