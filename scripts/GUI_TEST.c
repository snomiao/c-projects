//tcc_out=DS.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include <io.h>
#include <fcntl.h> // control

#include "css/define.h"
#include "css/console.h"
#include "css/win.h"
// 控制台


HANDLE hOut     = 0;
HWND   hWndMain = 0;
char   xxx[] = "aaaaaaaaaaaaa";
LRESULT CALLBACK Func1(
                        HWND hwnd,      // handle to window
                        UINT uMsg,      // message identifier
                        WPARAM wParam,  // first message parameter
                        LPARAM lParam   // second message parameter
){
    switch(uMsg){
    case WM_CHAR:
    //.....
    case WM_LBUTTONDOWN:
    //messagebox（....）
    case WM_PAINT:
        //textout（....）
    case WM_CLOSE:
        DestroyWindow(hwnd);

    case WM_DESTROY:
        PostQuitMessage(0);
    default:
        return DefWindowProc(hwnd,uMsg,wParam,lParam);
    }
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine, int nCmdShow)
{
    hOut     = io_open();
    hWndMain = CreateWindowEx(0, APP_CLASSNAME, W"GUI_测试", WS_OVERLAPPEDWINDOW, 0, 0, 400, 800, hWndParent, NULL, hInstance, NULL);
    printf("%s\n", "aaaaaaaaa");
    getch();

/*
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
*/
    MSG msg;
    while(PeekMessage(&msg,0,0,0,1))
    {
        switch(msg.message)
        {
            //case WM_TIMER: TimerProc(0,0,0,0);
            //break;                                                //预设风向改变时间已到

            case WM_HOTKEY:
            //KillTimer(0,hTimer);                      //删除随机风向定时 器
            UnregisterHotKey(0,0);                                //删除退出热键
            InvalidateRect(0,NULL,true);
            exit(1);
            break;

            case WM_DISPLAYCHANGE:

            break;
        }
    }
    io_close();
    return 0;
}