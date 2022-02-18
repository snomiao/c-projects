//tcc_out=/build/AS_自动瞄准.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=
//version 0.13.0

#include <io.h>
#include <fcntl.h> // control

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DEBUG 0
enum{
DEBUG_LEVEL_HIDE,
DEBUG_LEVEL_INFO,
DEBUG_LEVEL_WARNING,
DEBUG_LEVEL_ERROR
};

HANDLE HandleStdout;
#define clr(a) ;//SetConsoleTextAttribute(HandleStdout, a)

// <perfTicker.h>
LARGE_INTEGER perfFreq, perfCount;
unsigned int perfInit(){
    return QueryPerformanceFrequency(&perfFreq);
}
unsigned int perfTick(){
    QueryPerformanceCounter(&perfCount);
    return (perfCount.QuadPart * 1000) / perfFreq.QuadPart;
}
//

#define uint unsigned int

typedef struct tpt{
    uint x ;
    uint y ;
    uint c1; //cNormal; // Actived
    uint c2; //cHover;  // unActived
    uint c3; //cDown;
    uint c4; //cDisable;
    char* ptn;
};

HWND hwndGame;
HDC hDC;
HBITMAP hBmp;
BITMAPINFO binfo;
unsigned char*cdata;
uint cx, cy, cw, ch;
uint dx, dy, dw, dh;

inline uint WillStop(){
    return GetKeyState(VK_F10);
}

uint WinUnload(){
    ReleaseDC(hwndGame, hDC);
}
inline uint Err(char* err){
    clr(0xC4); printf("[停止: %s]\n", err); fflush(stdin); getchar();
    WinUnload();
    exit(0);
    return 0;
}
uint WinLoad(){
    //SetProcessDpiAwareness
//Mona_.* ahk_class Qt5QWindowIcon
    RECT rct; POINT pnt;

    hwndGame  = FindWindow("Qt5QWindowIcon",NULL);
    if(!hwndGame) return Err("未找到游戏");

    hDC = GetDC(hwndGame);
    if(!hDC) return Err("无法观测到游戏");
    /* 控制区*/
    //GetWindowRect(hwndGame, &rct);
    cx = rct.left;              cy = rct.top;
    cw = rct.right - rct.left;  ch = rct.bottom - rct.top;
    
    /* 图像区 */
    pnt.x = pnt.y = 0;
    
    /* 缓冲区 */
    cdata = calloc(cw * ch, sizeof(int));
    hBmp = (HBITMAP)GetCurrentObject(hDC , OBJ_BITMAP);
    binfo.bmiHeader.biSize          = sizeof(binfo.bmiHeader);
    binfo.bmiHeader.biCompression   = BI_RGB;
    binfo.bmiHeader.biPlanes        = 1;
    binfo.bmiHeader.biBitCount      = 32;
    binfo.bmiHeader.biWidth         = cw;
    binfo.bmiHeader.biHeight        = ch;
    return 0;
}

uint Capture(){
    GetDIBits(hDC, hBmp, cy + ch - dy - dh, dh, cdata, &binfo, DIB_RGB_COLORS);
}
uint getPx(uint x, uint y){
    Capture();
    uint scan = 4 * cw * ( dh -  1  - y);
    uint car  = 4 *      ((dx - cx) + x);
    return cdata[scan + car + 0] << 0x00|
           cdata[scan + car + 1] << 0x08|
           cdata[scan + car + 2] << 0x10;
}
#define val_none (uint)-1
#define val_err  (uint)-2
//#define val_Item1 (uint)352
uint Hot(){
    {
    //getPx_name("搜索"); return;
    }
}
void begin(){
    AllocConsole();
    *stdout = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT), "w");
    *stdin = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r" );
    HandleStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!perfInit()) Err("系统不支持高性能计时");
}
void end(){
    WinUnload();
    FreeConsole();
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    begin();
    system("title AS_自动瞄准");
    system("color 07");

    clr(0x07);
    printf("\x9 雪星桌面AI @雪星(snomiao@gmail.com)\n");
    printf("\n");
    WinLoad();
    clr(0x0F);
    uint index=0;
    clr(0x0A);
    clr(0x0F);
    clr(0x0A);
    clr(0x0F);
    printf("    < 开始! 你随时可以按");
    clr(0xB0);
    printf("[F10]");
    clr(0x0F);
    printf("结束程序. \n\n");
    clr(0x07);
    //SetProcessDPIAware();
    while(!WillStop()) Hot();
    Err("用户停止");
    end();
}