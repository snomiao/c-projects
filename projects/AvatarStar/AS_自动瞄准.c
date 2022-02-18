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
struct tpt pts[] =
{ {  0,   0,       -1,       -1,       -1,       -1, "零点"
},{690, 435,       -1,       -1,       -1,       -1, "失败"
},{260, 200,       -1,       -1,       -1,       -1, "搜索框"
},{400, 430, 0xE8D2B5,       -1,       -1,       -1, "有框"
},{710,  80, 0xFFD154,       -1,       -1,       -1, "拍卖行"
},{587, 433, 0xF4DF63,       -1,       -1,       -1, "确定购买"
},{770, 240, 0x214B25,       -1,       -1,       -1, "一口价单价"
},{350, 300, 0xCBB285, 0xFFD631,       -1,       -1, "货F1"
},{350, 384, 0xCAB185, 0xFFD631,       -1,       -1, "货F2"
},{350, 467, 0xCBB285, 0xFFD631,       -1,       -1, "货F3"
},{350, 550, 0xCBB285, 0xFFD631,       -1,       -1, "货F4"
},{350, 634, 0xCBB285, 0xFFD631,       -1,       -1, "货F5"
},{ 73, 294, 0x474009, 0x474519,       -1,       -1, "道具"
},{100, 160, 0xA47E4D, 0xF7D9A3,       -1,       -1, "浏览"
},{495, 385, 0xCAB084, 0xFFD631,       -1,       -1, "加载中"
},{ 73, 375, 0x5C4333, 0xFFD940,       -1,       -1, "强化材料"
},{262, 696, 0x6D5343, 0x19541E,       -1,       -1, "查看单价"
},{438, 200, 0xEEECEA, 0xF0EDEB, 0xF3EFE8,       -1, "搜索"
},{975, 540, 0xA33139,       -1,       -1,       -1, "关闭公告"
},{520, 200, 0xCBB5A9, 0x9D7561, 0xFCD495,       -1, "初始化"
},{490, 690, 0xFFFB7F, 0xFFFFB2, 0xBAB269, 0xBFBFBF, "上一页"
},{690, 690, 0x75462D, 0xA76642, 0x553327, 0x9F9F9F, "下一页"
},{930, 695, 0xF3EEEC, 0xF7F0ED, 0xFEF6E7, 0x94918F, "一口价购买"
} };
#define COUNT_PTS 22

inline uint NameToIndex(char* name){
    int i; for(i = 0; i < COUNT_PTS && strcmp(pts[i].ptn, name); i++); if(i == COUNT_PTS) return -1; return i;
}

HWND hc;
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
    ReleaseDC(hc, hDC);
}
inline uint Err(char* err){
    clr(0xC4); printf("[停止: %s]\n", err); fflush(stdin); getchar();
    WinUnload();
    exit(0);
    return 0;
}
uint WinLoad(){
    //SetProcessDpiAwareness

    RECT rct; POINT pnt;
    hc  = FindWindow("Screen","创想兵团");
    if(!hc) return Err("未找到游戏");
    hDC = GetDC(hc);
    if(!hDC) return Err("无法观测到游戏");
    /* 控制区*/
    GetWindowRect(hc, &rct);
    cx = rct.left;              cy = rct.top;
    cw = rct.right - rct.left;  ch = rct.bottom - rct.top;
    /* 图像区 */
    pnt.x = pnt.y = 0;
    ClientToScreen(hc, &pnt);
    GetClientRect(hc, &rct);
    dx = pnt.x;                 dy = pnt.y;
    dw = rct.right;             dh = rct.bottom;
    /* 缓冲区 */
    cdata = calloc(cw * ch, sizeof(int));
    hBmp = (HBITMAP)GetCurrentObject(hDC , OBJ_BITMAP);
    binfo.bmiHeader.biSize          = sizeof(binfo.bmiHeader);
    binfo.bmiHeader.biCompression   = BI_RGB;
    binfo.bmiHeader.biPlanes        = 1;
    binfo.bmiHeader.biBitCount      = 32;
    binfo.bmiHeader.biWidth         = cw;
    binfo.bmiHeader.biHeight        = ch;
    /* 调度 */
    ShowWindow(hc,SW_RESTORE);
    //SetWindowPos(hc, HWND_TOP, cx-dx, cy-dy, 0, 0, SWP_NOSIZE);
    SetWindowPos(hc, HWND_TOP, cx-dx, cy-dy, 0, 0, SWP_NOSIZE);
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
    printf("\x9 AvatarStar_自动瞄准工具 @雪星(snomiao@gmail.com)\n");
    printf("\n");
    WinLoad();
    clr(0x0F);
    uint index=0;
    printf("%d< 工作环境: [ESC]-视频-恢复默认值\n", ++index);
    printf("%d< 请不要把鼠标伸进游戏窗口内\n", ++index);
    printf("%d< 请不要把游戏窗口最小化\n", ++index);
    printf("%d< 请不要把游戏窗口移出屏幕\n", ++index);
    printf("%d< 请手动切换到 道具 - 强化材料\n", ++index);
    printf("%d<   或在搜索栏填入名称\n", index);
    #if!DEBUG
    printf("%d< 请输入最高入手单价\n", ++index);
    printf("    >");
    clr(0x0A);
    float fvalmax; fflush(stdin); scanf("%f", &fvalmax);
    clr(0x0F);
    valmax = (uint)(fvalmax * 100);
    printf("%d< 确认收入所有一口价单价为%0.2f以下的物品? (Y/N)\n", ++index, (float)valmax / 100);
    printf("    >");
    clr(0x0A);
    char r;        fflush(stdin); scanf("%c", &r);
    clr(0x0F);
    if (r != 'Y' && r != 'y') Err("用户取消");
    #else

    valmax = 1500;
    #endif
    printf("    < 开始! 你随时可以按");
        clr(0xB0);
    printf("[F10]");
        clr(0x0F);
    printf("结束程序. \n\n");
    clr(0x07);

    //SetProcessDPIAware();
    while(!WillStop()){
        Hot();
    }
    Err("用户停止");
    end();
}