#include "stdafx.h"
#include "Frame.h"
#include "resource.h"


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
	g_hDisasm = CreateWindow(L"Edit", L"f834:  7d 45 ad  lda (ad45) ",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_MULTILINE | ES_READONLY,
		308, 48, 288, 152, window, (HMENU)IDB_GROUP1, NULL, NULL);
	SendMessage(g_hDisasm, WM_SETFONT, (WPARAM)hFont, TRUE);


	//========== 
	//  Memory display
	//========== 

	// Group box container for memory
	CreateWindow(L"Button", L"Memory", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 16, 216, 652, 272, window, (HMENU)IDB_GROUP1, NULL, NULL);

	// Memory Page display
	g_hPage = CreateWindow(L"Edit", L"text...", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_MULTILINE | ES_READONLY,
		32, 248, 620, 224, window, (HMENU)IDT_PAGE, NULL, NULL);
	SendMessage(g_hPage, WM_SETFONT, (WPARAM)hFont, TRUE);

}
