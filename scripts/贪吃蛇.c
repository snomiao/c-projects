//tcc_out=/build/贪吃蛇.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=


//贪吃蛇.c
//2015/02/09 雪星(997596@gmail.com)
//建立！


#include <windows.h>
////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <io.h>
#include <fcntl.h> // control
inline HANDLE io_open(){
    AllocConsole();
    *stdout = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT), "w");
    *stdin  = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE ),_O_TEXT), "r");
    return GetStdHandle(STD_OUTPUT_HANDLE);
}
inline void   io_close(){
    FreeConsole(); 
}
////////////////////////////////////////////////////////////////
#define uint unsigned int
////////////////////////////////////////////////////////////////
char *APP_NAME = "贪吃蛇";
////////////////////////////////////////////////////////////////
uint wCX = 0, wCY = 0;
HWND hWndMain;
HDC  wDC = 0;
HBITMAP wBmp;

uint *bmBytes = 0;
uint bmW, bmH;
HDC  mDC;
HBITMAP mBmp;
BITMAPINFO BI;


uint *gmCells = 0;
uint gmW, gmH;
uint gmSnakeDirection = 0;     LURD 0x25 0x26 0x27 0x28
uint gmSnakeLength    = 0;
uint gmState          = 0;

int GameLoop(){
    if(gmState)
    {
        
    }
}
int ReDraw(){
    BitBlt(wDC, 0, 0, bmW, bmH, mDC, 0, 0, SRCCOPY);
}
int DrawGame(){
    //清屏
    //画字

    switch(gmState){
        case 0:
        ""
        break;
        case 1:
        memset(bmBytes, 0xFF, bmW*bmH*4);
        break;
        
    }
//　ＭＭＭ　ＭＭＭ　ＭＭＭ　ＭＭＭ　ＭＭＭ　ＭＭＭ　ＭＭＭ　ＭＭＭ　ＭＭＭ
//　Ｍ　　　　　Ｍ　　Ｍ　　Ｍ　Ｍ　Ｍ　　　　Ｍ　　Ｍ　Ｍ　Ｍ　Ｍ　　Ｍ
//　ＭＭＭ　ＭＭＭ　　Ｍ　　Ｍ　Ｍ　ＭＭＭ　　Ｍ　　ＭＭＭ　ＭＭＭ　　Ｍ
//　Ｍ　　　Ｍ　　　　Ｍ　　Ｍ　Ｍ　　　Ｍ　　Ｍ　　Ｍ　Ｍ　ＭＭ　　　Ｍ
//　Ｍ　　　ＭＭＭ　　Ｍ　　ＭＭＭ　ＭＭＭ　　Ｍ　　Ｍ　Ｍ　Ｍ　Ｍ　　Ｍ

    SetBitmapBits(mBmp, bmW*bmH*4, bmBytes);
}
int ReSize(){
    RECT rct;
    GetClientRect(hWndMain, &rct);
    wCX = rct.right;
    wCY = rct.bottom;
    wprintf(L"ReSize %d, %d\n", wCX, wCY);

    bmW = wCX;
    bmH = wCY;
    bmBytes = (int*)calloc(bmW * bmH, sizeof(int));
    
    BI.bmiHeader.biWidth         = bmW;
    BI.bmiHeader.biHeight        = bmH;
    mBmp = CreateCompatibleBitmap(wDC, bmW, bmH);
    DeleteObject(SelectObject(mDC, mBmp));
    DrawGame();
}
int InitDC(){
    BI.bmiHeader.biSize        = sizeof(BI.bmiHeader);
    BI.bmiHeader.biCompression = BI_RGB;
    BI.bmiHeader.biPlanes      = 1;
    BI.bmiHeader.biBitCount    = 32;
    wDC  = GetDC(hWndMain);
    mDC  = CreateCompatibleDC(wDC);
}
LRESULT CALLBACK WndProcWolfSprit(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CHAR:{
            if(wParam == VK_ESCAPE) SendMessage(hWnd, WM_DESTROY, 0, 0);
            wprintf(L"CHAR %c\n", wParam);
            if(wParam == VK_LEFT)
            gmState = 0
            break;
        }
        case WM_SIZE:{
            ReSize();
            break;
        }
        case WM_PAINT:{
            PAINTSTRUCT rct;
            HDC tmpHDC = BeginPaint(hWnd, &rct);
            ReDraw();
            EndPaint(hWnd, &rct);
            break;
        }
        case WM_DESTROY:{                  //关闭窗口
            PostQuitMessage(0);           //发送关闭消息
            break;
        }
        default:{
            return DefWindowProc(hWnd, message, wParam, lParam);  //缺省窗口处理函数
        }
   }
   return 0;
}

void RegisterWolfSpritClass(HINSTANCE hInstance){
    WNDCLASSEX wcx;
    wcx.cbClsExtra    = 0;                                   //32位窗口的附加数据，设为0
    wcx.cbSize        = sizeof(WNDCLASSEX);                  //结构体大小
    wcx.cbWndExtra    = 0;                                   // 这是附加窗口数据，一般也不用
    wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //CreateSolidBrush……
    wcx.hCursor       = LoadCursor(NULL,IDC_CROSS);          //这个是光标
    wcx.hIcon         = LoadIcon(NULL,IDI_ERROR);            //窗口图标
    wcx.hIconSm       = NULL;                                //窗口小图标
    wcx.hInstance     = hInstance;                           //窗口实例 这个很重要
    wcx.lpfnWndProc   = WndProcWolfSprit;                    //窗口回调函数
    wcx.lpszClassName = "WolfSprit_Form";
    wcx.lpszMenuName  = NULL;                                //没有菜单，名字就不要了
    wcx.style         = CS_HREDRAW | CS_VREDRAW;
    return RegisterClassEx(&wcx);                            //这样一个窗口类就赋值完了 然后注册它
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine, int nCmdShow)
{
    io_open();

    if(!RegisterWolfSpritClass(hInstance)) return 0;

    if(!(hWndMain = CreateWindowEx(
                0, "WolfSprit_Form", APP_NAME, WS_OVERLAPPEDWINDOW,
                90*8+20, 0, 400, 800, NULL, NULL, hInstance, NULL))
        )
        return 0;

    InitDC();
    ShowWindow(hWndMain, nCmdShow); //显示窗口
    UpdateWindow(hWndMain);         //立即显示

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) //消息循环
    {
        TranslateMessage(&msg); //消息解释
        DispatchMessage(&msg);  //消息发送
    }

    io_close();
    return (int)msg.wParam; //注意：不能用“return 0;”，因为有非正常退出的可能性
}