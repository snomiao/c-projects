//tcc_out=AS_收货.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=


#include <io.h>
#include <fcntl.h> // control
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

LARGE_INTEGER perfFreq, perfCount;
unsigned int perfInit(){
    return QueryPerformanceFrequency(&perfFreq);
}
unsigned int perfTick(){
    QueryPerformanceCounter(&perfCount);
    return (perfCount.QuadPart * 1000) / perfFreq.QuadPart;
}

typedef struct tpt{
    unsigned int x ;
    unsigned int y ;
    unsigned int c1; //cNormal; // Actived
    unsigned int c2; //cHover;  // unActived
    unsigned int c3; //cDown;
    unsigned int c4; //cDisable;
    char* ptn;
};
struct tpt pts[] =
{ {  0,   0,       -1,       -1,       -1,       -1, "零点"
},{930, 695,       -1,       -1,       -1,       -1, "一口价购买"
},{690, 435,       -1,       -1,       -1,       -1, "失败"
},{260, 200,       -1,       -1,       -1,       -1, "搜索框"
},{438, 200,       -1,       -1,       -1,       -1, "搜索"
},{710,  80, 0xFFD154,       -1,       -1,       -1, "拍卖行"
},{587, 433, 0xF4DF63,       -1,       -1,       -1, "确定购买"
},{770, 240, 0x214B25,       -1,       -1,       -1, "一口价单价"
},{400, 430, 0xE8D2B5,       -1,       -1,       -1, "有框"
},{ 73, 294, 0x474009, 0x474519,       -1,       -1, "道具"
},{ 73, 375, 0x5C4333, 0xFFD940,       -1,       -1, "强化材料"
},{100, 160, 0xA47E4D, 0xF7D9A3,       -1,       -1, "浏览"
},{350, 300, 0xCBB285, 0xFFD631,       -1,       -1, "货F1"
},{350, 384, 0xCAB185, 0xFFD631,       -1,       -1, "货F2"
},{350, 467, 0xCBB285, 0xFFD631,       -1,       -1, "货F3"
},{350, 550, 0xCBB285, 0xFFD631,       -1,       -1, "货F4"
},{350, 634, 0xCBB285, 0xFFD631,       -1,       -1, "货F5"
},{262, 696, 0x6D5343, 0x19541E,       -1,       -1, "查看单价"
},{520, 200, 0xCBB5A9, 0x9D7561, 0xFCD495,       -1, "初始化"
},{690, 690, 0x75462D, 0xA76642, 0x553327, 0x9F9F9F, "下一页"
} };

unsigned int tick = 0, fps = 0;

RECT rct; POINT pnt;
unsigned char*cdata;
unsigned char*couta;

unsigned int cx, cy, cw, ch;
unsigned int dx, dy, dw, dh;
unsigned int gx, gy, gw, gh;
HWND    hc  , hg ;
HDC     hDC , gDC, mDC;
HBITMAP hbmp, mbmp;
BITMAPINFO binfo;

unsigned int WILLSTOP(){
    return GetKeyState(VK_F10);
}
unsigned int capture(){
    GetDIBits(hDC, hbmp, cy + ch - dy - dh, dh, cdata, &binfo, DIB_RGB_COLORS);
}
unsigned int encode(){
    int x, y, c, scan, car;
    for(y = 0; y < dh; y++){
        scan = 4 * cw * (dh - 1 - y);
        for(x = 0; x < dw; x++){
            car = 4 * (dx - cx + x);
            couta[4 * dw * y + x * 4 + 0] = cdata[scan + car + 0];
            couta[4 * dw * y + x * 4 + 1] = cdata[scan + car + 1];
            couta[4 * dw * y + x * 4 + 2] = cdata[scan + car + 2];
        }
    }
}
unsigned int paint(){
    SetBitmapBits(mbmp, dw*dh*4, couta);
    BitBlt(gDC, gx, gy, gw, gh, mDC, 0, 0, SRCCOPY);
}
unsigned int getPx(char* name){
    //E4C392
    capture();
    int i, c, scan, car;
    for(i=0; i < 20 && strcmp(pts[++i].ptn, name);); if(i==20) return -1;
    c =0;
    scan = 4 * cw * (dh -  1 - pts[i].y);
    car  = 4 *      ((dx - cx) + pts[i].x);
    c|=cdata[scan + car + 0] << 0;
    c|=cdata[scan + car + 1] << 8;
    c|=cdata[scan + car + 2] << 16;
    printf("X, Y, C = %d, %d, 0x%08X\n", pts[i].x, pts[i].y, c);
    return c;
}
unsigned int fnc(char* name){
    int i, x, y, c1;
    for(i=0, x=y=-1; i < 20 && strcmp(pts[++i].ptn, name););
    if(i==20) return -1;
    x = pts[i].x; y = pts[i].y;
    c1 = pts[i].c1;
    if(c1 != cdata[dw*4 * y + x])
    printf("click! %d, %d | 0x%08X, 0x%08X, %s\n", x, y, c1, cdata[dw*4 * y + x], pts[i].ptn);
    // for(x = 0; x < dw)
    // for(y = 0; y < dh)
    {

    }
    return 0;
}
int faHot(){
    //capture();
    //getPx("拍卖行");
    getPx("零点");
    //fnc("拍卖行");
    /*printf("0x%08X", getPx());*/
    //sleep(1);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 召唤一只萌萌的控制台
    AllocConsole();
    *stdout = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT), "w");
    *stdin = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r" );
    // 初始化
    printf("加载开始\n");
    // 计时器
    if(!perfInit())
        printf("error: 系统不支持 QueryPerformanceCounter\n");
    // 找窗口
    hc  = FindWindow("Screen","创想兵团");
    //hc  = FindWindow(0,"计算器");
    //hc = GetDesktopWindow();
    hDC = GetDC(hc);
    if(!hc ) goto onError;
    if(!hDC) goto onError;
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
    /* 绘图区*/
    gx = 0;                     gy = 0;
    gw = dw;                    gh = dh;
    if(hg = FindWindow(0,"无标题 - 画图")){
        gDC = GetDC(hg);
        gx = 5; gy = 60;
    }else if(hg = FindWindow(0,"无标题 - 记事本")){
        gDC = GetDC(hg);
        gx = 5; gy = 60;
    }else if(hg = GetDesktopWindow()){
        gDC = GetDC(hg);
        gx = dx + dw; gy = dy;
    }
    if(!hg ) goto onError;
    if(!gDC) goto onError;
    //memset(cdata, 0xFF, dw * dh * 4);
    cdata = calloc(cw * ch, sizeof(int));
    couta = calloc(dw * dh, sizeof(int));
    hbmp = (HBITMAP)GetCurrentObject(hDC , OBJ_BITMAP);
    mDC = CreateCompatibleDC(hDC);
    mbmp = CreateCompatibleBitmap(hDC, dw, dh);
    DeleteObject(SelectObject(mDC, mbmp));
    binfo.bmiHeader.biSize          = sizeof(binfo.bmiHeader);
    binfo.bmiHeader.biCompression   = BI_RGB;
    binfo.bmiHeader.biPlanes        = 1;
    binfo.bmiHeader.biBitCount      = 32;
    binfo.bmiHeader.biWidth         = cw;
    binfo.bmiHeader.biHeight        = ch;
    printf("hc  = 0x%08X\n", hc);
    printf("hg  = 0x%08X\n", hg);
    printf("hDC = 0x%08X\n", hDC);
    printf("gDC = 0x%08X\n", gDC);
    printf("c(%d, %d)[%d, %d]\n", cx, cy, cw, ch);
    printf("d(%d, %d)[%d, %d]\n", dx, dy, dw, dh);
    printf("g(%d, %d)[%d, %d]\n", gx, gy, gw, gh);
    printf("加载成功\n");


    printf("按F10结束\n");
    unsigned int fpslimiter = 0;
    printf("SWITCH LIMITER ON\n");
    while(!WILLSTOP())
    {
        faHot();
        // FPS Calc
        // sleep(fpslimiter);
        if(perfTick() - tick >= 1000){
            /*
            fpslimiter+=fps>60;
            if(fpslimiter>0)
                fpslimiter-=fps<60;
            */
            printf("fps: %d, limiter: %d\n", fps, fpslimiter);
            fps=0;
            tick = perfTick();
        }
        fps++;
    }
    // 错误处理
    goto noError;
    onError:
    printf("失败\n");
    noError:
    // 结束
    printf("任意键退出");
    getch();
    // 扫地
    free(cdata);
    ReleaseDC(hc, hDC);
    ReleaseDC(hg, gDC);
    //DeleteDC(mDC);
    FreeConsole();
}