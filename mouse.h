#include <windows.h>
#include <stdio.h>

HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD mer,int *x,int *y);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
int e=0;

int start(int *x,int *y){
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];
    int counter=0;

    // Get the standard input handle.

    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");

    // Save the current input mode, to be restored on exit.

    if (! GetConsoleMode(hStdin, &fdwSaveOldMode) )
        ErrorExit("GetConsoleMode");

    // Enable the window and mouse input events.

    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (! SetConsoleMode(hStdin, fdwMode) )
        ErrorExit("SetConsoleMode");

        // Wait for the events.

        if (! ReadConsoleInput(
                hStdin,      // input buffer handle
                irInBuf,     // buffer to read into
                128,         // size of read buffer
                &cNumRead) ) // number of records read
            ErrorExit("ReadConsoleInput");

        // Dispatch the events to the appropriate handler.
		
        for (i = 0; i < cNumRead; i++){
	            switch(irInBuf[i].EventType){
	                /*case KEY_EVENT: // keyboard input
	                    KeyEventProc(irInBuf[i].Event.KeyEvent);
	                    break;*/
	
	                case MOUSE_EVENT: // mouse input
						if(e==1){
							e=0;
							MouseEventProc(irInBuf[i].Event.MouseEvent,x,y);
						}
						else{
							e++;
						}
	                    break;
	
	                /*case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
	                    ResizeEventProc( irInBuf[i].Event.WindowBufferSizeEvent );
	                    break;*/
	
	                //case FOCUS_EVENT:  // disregard focus events
	
	                //case MENU_EVENT:   // disregard menu events
	                    //break;
	
	                /*default:
	                    ErrorExit("Unknown event type");
	                    break;*/
	            }
        }

    // Restore input mode on exit.

   // SetConsoleMode(hStdin, fdwSaveOldMode);

    return 0;
}
VOID ErrorExit (LPSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
    printf("Key event: ");
    if(ker.bKeyDown)
        printf("key pressed\n");
    else printf("key released\n");
}
VOID MouseEventProc(MOUSE_EVENT_RECORD mer,int *x,int *y)
{
    #ifndef MOUSE_HWHEELED
    #define MOUSE_HWHEELED 0x0008
    #endif
    //printf("Mouse event: ");

    switch(mer.dwEventFlags)
    {
        case 0:
        	(*x)=mer.dwMousePosition.X;
        	(*y)=mer.dwMousePosition.Y;
			//click(mer.dwMousePosition.X,mer.dwMousePosition.Y);
            /*if(mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
            	//accio per quan fas left click
                //printf("left button press \n");
            }
            else if(mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
            {
            	//accio per quan fas right click
                //printf("right button press \n");
            }
            else
            {
                printf("button press\n");
            }*/
            break;
        /*case DOUBLE_CLICK:
            printf("double click\n");
            break;
        case MOUSE_HWHEELED:
            printf("horizontal mouse wheel\n");
            break;
        case MOUSE_MOVED:
            printf("mouse moved\n");
            break;
        case MOUSE_WHEELED:
            printf("vertical mouse wheel\n");
            break;
        default:
            printf("unknown\n");
            break;*/
    }
}
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
    printf("Resize event\n");
    printf("Console screen buffer is %d columns by %d rows.\n",    wbsr.dwSize.X, wbsr.dwSize.Y);
}
