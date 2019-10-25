#include <windows.h>
#include <stdio.h>

HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID MouseEventProc(MOUSE_EVENT_RECORD mer,int *x,int *y);

int start(int *x,int *y){
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");
	if (! GetConsoleMode(hStdin, &fdwSaveOldMode) )
		ErrorExit("GetConsoleMode");
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (! SetConsoleMode(hStdin, fdwMode) )
		ErrorExit("SetConsoleMode");
	if (! ReadConsoleInput(
			hStdin,      // input buffer handle
			irInBuf,     // buffer to read into
			128,         // size of read buffer
			&cNumRead) ) // number of records read
		ErrorExit("ReadConsoleInput");
		// Dispatch the events to the appropriate handler.
	for (i = 0; i < cNumRead; i++){
		if(irInBuf[i].EventType==MOUSE_EVENT{
			MouseEventProc(irInBuf[i].Event.MouseEvent,x,y);
			break;
		}
	}
	return 0;
}
VOID ErrorExit (LPSTR lpszMessage){
	fprintf(stderr, "%s\n", lpszMessage);
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}
VOID MouseEventProc(MOUSE_EVENT_RECORD mer,int *x,int *y){
	#ifndef MOUSE_HWHEELED
	#define MOUSE_HWHEELED 0x0008
	#endif
	if(mer.dwEventFlags==0){
		(*x)=mer.dwMousePosition.X;
		(*y)=mer.dwMousePosition.Y;
	}
}