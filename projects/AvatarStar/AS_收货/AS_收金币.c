//tcc_out=./build/AS_收金币2.exe
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
#define clr(a) SetConsoleTextAttribute(HandleStdout, a)

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
{  {  0,   0,       -1,       -1,       -1,       -1, "零点"
}, {690, 435,       -1,       -1,       -1,       -1, "失败"
}, {260, 200,       -1,       -1,       -1,       -1, "搜索框"
}, {975, 540, 0xA33139,       -1,       -1,       -1, "关闭公告"
}, {400, 430, 0xE8D2B5,       -1,       -1,       -1, "有框"
}, {710,  80, 0xFFD154,       -1,       -1,       -1, "拍卖行"
}, {587, 433, 0xF4DF63,       -1,       -1,       -1, "确定购买"
}, {770, 240, 0x214B25,       -1,       -1,       -1, "一口价单价"
}, {725, 241, 0xCE802B,       -1,       -1,       -1, "寄售货币_价格"
}, {350, 300, 0xCBB285, 0xFFD631,       -1,       -1, "货F1"
}, {350, 384, 0xCAB185, 0xFFD631,       -1,       -1, "货F2"
}, {350, 467, 0xCBB285, 0xFFD631,       -1,       -1, "货F3"
}, {350, 550, 0xCBB285, 0xFFD631,       -1,       -1, "货F4"
}, {350, 634, 0xCBB285, 0xFFD631,       -1,       -1, "货F5"
}, {424, 278, 0xD0B88A, 0xFFD631,       -1,       -1, "寄售货币_第一列"
}, { 73, 294, 0x474009, 0x474519,       -1,       -1, "道具"
}, {100, 160, 0xA47E4D, 0xF7D9A3,       -1,       -1, "浏览"
}, {495, 385, 0xCAB084, 0xFFD631,       -1,       -1, "加载中"
}, {511, 404, 0xDBCDB7, 0xDBCDB7,       -1,       -1, "寄售货币_加载中"
}, { 73, 375, 0x5C4333, 0xFFD940,       -1,       -1, "强化材料"
}, {262, 696, 0x6D5343, 0x19541E,       -1,       -1, "查看单价"
}, {438, 200, 0xEEECEA, 0xF0EDEB, 0xF3EFE8,       -1, "搜索"
}, {520, 200, 0xCBB5A9, 0x9D7561, 0xFCD495,       -1, "初始化"
}, {780, 680, 0x895126, 0xAD9631, 0x774A25,       -1, "寄售货币_刷新"
}, {890, 680, 0x895126, 0xAD9631, 0x774A25,       -1, "寄售货币_购买"
}, {490, 690, 0xFFFB7F, 0xFFFFB2, 0xBAB269, 0xBFBFBF, "上一页"
}, {690, 690, 0x75462D, 0xA76642, 0x553327, 0x9F9F9F, "下一页"
}, {930, 695, 0xF3EEEC, 0xF7F0ED, 0xFEF6E7, 0x94918F, "一口价购买"
} };
#define COUNT_PTS 28

inline uint NameToIndex(char* name){
    int i; for(i = 0; i < COUNT_PTS && strcmp(pts[i].ptn, name); i++); if(i == COUNT_PTS) return -1; return i;
}

HWND hc;
HDC hDC;
HBITMAP hbmp;
BITMAPINFO binfo;
unsigned char*cdata;
uint cx, cy, cw, ch;
uint dx, dy, dw, dh;

inline uint WillStop(){
    return GetKeyState(VK_F10);
}
inline uint Paused(){
    return GetKeyState(VK_SCROLL);
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
    hbmp = (HBITMAP)GetCurrentObject(hDC , OBJ_BITMAP);
    binfo.bmiHeader.biSize          = sizeof(binfo.bmiHeader);
    binfo.bmiHeader.biCompression   = BI_RGB;
    binfo.bmiHeader.biPlanes        = 1;
    binfo.bmiHeader.biBitCount      = 32;
    binfo.bmiHeader.biWidth         = cw;
    binfo.bmiHeader.biHeight        = ch;
    /* 调度 */
    //ShowWindow(hc,SW_RESTORE);
    //SetWindowPos(hc, HWND_TOP, cx-dx, cy-dy, 0, 0, SWP_NOSIZE);
    return 0;
}

uint Capture(){
    GetDIBits(hDC, hbmp, cy + ch - dy - dh, dh, cdata, &binfo, DIB_RGB_COLORS);
}
uint getPx(uint x, uint y){
    Capture();
    uint scan = 4 * cw * ( dh -  1  - y);
    uint car  = 4 *      ((dx - cx) + x);
    return cdata[scan + car + 0] << 0x00|
           cdata[scan + car + 1] << 0x08|
           cdata[scan + car + 2] << 0x10;
}
uint getPx_name(char* name){
    uint i = NameToIndex(name);
    uint c = getPx(pts[i].x, pts[i].y);
    printf("\npos, c, .. = %d, %d, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X\n",
        pts[i].x, pts[i].y, c, pts[i].c1, pts[i].c2, pts[i].c3, pts[i].c4);
    return c;
}
#define fTIMEOUT 768
#define fRESULT_CLICKED 0
#define fRESULT_NEEDNT  1
#define fRESULT_TIMEOUT 2
#define fRESULT_FAILED  4
#define fRESULT_DISABLE 8
#define MMOVE()    {SendMessage(hc, WM_MOUSEMOVE  , MK_LBUTTON, MAKELPARAM(x, y));};
#define LMDOWN()   {SendMessage(hc, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG  (x, y));};
#define LMUP()     {SendMessage(hc, WM_LBUTTONUP  , MK_LBUTTON, MAKELONG  (x, y));};
#define LMCLICK()   {LMDOWN(); LMUP();};
uint fcheck(char* name){
    uint i = NameToIndex(name);
    uint x = pts[i].x;
    uint y = pts[i].y;
    uint c1 = pts[i].c1;
    uint c2 = pts[i].c2;
    if(getPx(x, y)==c1){
        MMOVE();
        LMCLICK();
    }
    unsigned long int t = perfTick();
    while(1){
        if(perfTick() - t >= fTIMEOUT) return fRESULT_TIMEOUT;
        if(getPx(x, y)==c2){
            return fRESULT_CLICKED;
        }
    }
}
uint fict(char* name){
    uint i = NameToIndex(name);
    uint x = pts[i].x;
    uint y = pts[i].y;
    uint c1 = pts[i].c1;
    uint c2 = pts[i].c2;
    unsigned long int t = perfTick();
    if(getPx(x, y)==c1){
        MMOVE();
        LMDOWN();
        while(1){
            if(perfTick() - t >= fTIMEOUT) return fRESULT_TIMEOUT;
            if(getPx(x, y)==c2){
                LMUP();
                return fRESULT_CLICKED;
            }
        }
    }
    return fRESULT_NEEDNT;
}
uint fnc(char* name){
    uint i = NameToIndex(name);
    uint x  = pts[i].x;
    uint y  = pts[i].y;
    uint c1 = pts[i].c1;
    if(getPx(x, y)!=c1){
        MMOVE();
        LMCLICK();
        return fRESULT_CLICKED;
    }
    return fRESULT_NEEDNT;
}
uint fmov(char* name){
    uint i = NameToIndex(name);
    uint x  = pts[i].x;
    uint y  = pts[i].y;
    MMOVE();
    return fRESULT_NEEDNT;
}
uint fic(char* name){
    uint i = NameToIndex(name);
    uint x  = pts[i].x;
    uint y  = pts[i].y;
    uint c1 = pts[i].c1;
    if(getPx(x, y)==c1){
        MMOVE();
        LMCLICK();
        return fRESULT_CLICKED;
    }
    return fRESULT_NEEDNT;
}
uint fwc(char* name){
    uint i = NameToIndex(name);
    uint x  = pts[i].x;
    uint y  = pts[i].y;
    uint c1 = pts[i].c1;
    unsigned long int t = perfTick();
    while(1){
        if(perfTick() - t >= fTIMEOUT) return fRESULT_TIMEOUT;
        if(getPx(x, y)==c1){
            MMOVE();
            LMCLICK();
            return fRESULT_CLICKED;
        }
    }
}
uint fbtn(char* name){
    uint i = NameToIndex(name);
    uint x  = pts[i].x;
    uint y  = pts[i].y;
    uint c1 = pts[i].c1;
    uint c2 = pts[i].c2;
    uint c3 = pts[i].c3;
    uint c4 = pts[i].c4;
    uint clicked = 0;
    if(getPx(x, y) == c4) return fRESULT_DISABLE;
    unsigned long int t = perfTick();
    while(1){
        uint c;
        c = getPx(x, y);
        if(c==c1||c==c2||c==c3 && clicked < 5){
            MMOVE();
            LMDOWN();
            clicked++;
        }
        if(perfTick() - t >= fTIMEOUT) return fRESULT_TIMEOUT;
        if(c==c3){
            LMUP();
            return fRESULT_CLICKED;
        }
    }
}
uint fDif(uint Ra,uint Ga,uint Ba,uint Rb,uint Gb,uint Bb){
    uint Rc = Ra - Rb        , Gc = Ga - Gb        , Bc = Ba - Bb        ;
    uint Rt = Rc >> 0x1F     , Gt = Gc >> 0x1F     , Bt = Bc >> 0x1F     ;
    uint Rp = (Rc ^ Rt) - Rt , Gp = (Gc ^ Gt) - Gt , Bp = (Bc ^ Bt) - Bt ;
    return Rp + Gp + Bp;
}
#define val_none (uint)-1
#define val_err  (uint)-2
//#define val_Item1 (uint)352

inline uint val_NameScan(uint ho){
    Capture();
    if(WillStop()) Err("用户停止");
    char* name = "货F_"; name[3] = ho + '0';
    uint i = NameToIndex(name);
    //uint xa = pts[i].x - 59; //389~429 409-350
    uint xa = 330;//389;
    uint ya = pts[i].y - 10;
    //uint xb = xa + 177;
    uint xb = 429 + (389 - 330);
    uint yb = ya + 20;
    uint ts = 0, te, tw, tns;//, tpp;
    uint tc = (xb + xa) / 2;
    uint x, y;
    uint val = 0, valpow = 1, dot = 0;
    uint cwpx = 0;
    uint byt = 0;
    for(x = xb; x > xa; x--)
    for(y = ya; y < yb; y++)
    {
        uint scan = 4 * cw * ( dh -  1  - y);
        uint car  = 4 *      ((dx - cx) + x);
        if(fDif(cdata[scan + car + 0],
                cdata[scan + car + 1],
                cdata[scan + car + 2],
                0x71, 0x53, 0x41) > 60){
        }else {
            if(ts == 0){
                ts = x + 1;
                te = tc * 2 - ts - 1;
                //tw = ts - te + 1;
                tw = (ts - tc) * 2;
                //tns = ts - (12 * 3 + 6);
                tns = ts;
                //tpp = tns - (6 * 2);
                y = ya;
                x = tns;
                if(tw <= 24) return val_none;
            }else{
                cwpx += 1 << (1 + ((tns - x) % 6));
            }
        }
        if(ts != 0 && ya == y && 0 == ((tns - x) % 6) && te - 1 <= x && x < tns){
            
            uint matched = 0;
            uint items[][] = {
            // uint item[] = {LengthCode, Width, Codes, ...};
                {5, 34, 196, 196, 348, 156, 464, 168, -1 },
                {5, 34, 196, 228, 348, 156, 464, 168, -1 },
                {5, 34, 228, 228, 348, 156, 464, 168, -1 },
                {6, 44,  80,  74, 126,  66, 488,  80, 556}
            };
            for(int item = 0; item < 4; ++item)
            {
                if(byt <= items[item][0] && tw==items[item][1] && cwpx == items[item][byt+2]){
                    matched = 1;
                    if(byt == items[item][0]){
                        return item+1;
                    }
                }
            }
            if(matched == 0){
                #if DEBUG
                clr(0x0C);
                printf("%d:%d ", byt, cwpx);
                clr(0x07);
                #else
                return val_err;
                #endif
                
            }
            byt++;
            cwpx = 0;
        }
    }
    return val_err;
    if(!dot) return val_none;
    return 0;
}
uint valmax = -1;
inline uint val_Scan_jinbi(){
    if(WillStop()) Err("用户停止");
    uint xa = 617;
    uint ya = 277;
    uint xb = 727;
    uint yb = ya + 20;
    uint ts = 0, te, tw, tns, tpp;
    uint tc = (xb + xa) / 2;
    uint x, y;
    uint val = 0, valpow = 1, dot = 0;
    uint cwpx = 0;
    for(x = xb; x > xa; x--)
    for(y = ya; y < yb; y++)
    {//fic("关闭公告")
        uint scan = 4 * cw * ( dh -  1  - y);
        uint car  = 4 *      ((dx - cx) + x);
        
        if(y==ya){
            //printf("\n");
        }
        if(fDif(cdata[scan + car + 0],
                cdata[scan + car + 1],
                cdata[scan + car + 2],
                0x71, 0x53, 0x41) > 160){
            //printf("*");
        }else {
            //printf(" ");
            if(ts == 0){
                ts = x + 1;
                te = tc * 2 - ts - 1;
                tw = ts - te;
                tns = ts - (12 * 3 + 6);
                tpp = tns - (6 * 2);
                y = ya;
                x = tns;
                if(tw <= 24) return val_none;
            }else{
                cwpx += 1 << (1 + ((tns - x) % 6));
            }
        }
        if(ts != 0 && ya == y && 0 == ((tns - x) % 6) && te - 1 <= x && x < tns){
            switch(cwpx){
                break; case 32:
                dot++;
                break; case 336:
                val += valpow * 0; valpow*=10;
                break; case 120:
                val += valpow * 1; valpow*=10;
                break; case 222:
                val += valpow * 2; valpow*=10;
                break; case 272:
                val += valpow * 3; valpow*=10;
                break; case 270:
                val += valpow * 4; valpow*=10;
                break; case 620:
                val += valpow * 5; valpow*=10;
                break; case 280:
                val += valpow * 6; valpow*=10;
                break; case 136:
                val += valpow * 7; valpow*=10;
                break; case 348:
                val += valpow * 8; valpow*=10;
                break; case 568:
                val += valpow * 9; valpow*=10;
                break; default:
                printf("\ncpwx %d on %d\n", cwpx, valpow);
                return val_err;
            }
            cwpx = 0;
        }
    }
    //if(!dot) return val_none;
    val*=100;
    return val;
}
inline uint NoFrame(){
    uint i= NameToIndex("有框");
    uint x = pts[i].x, y = pts[i].y;
    if(pts[i].c1 == getPx(x, y)){
        i = NameToIndex("失败");
        SendMessage(hc, WM_MOUSEMOVE  , MK_LBUTTON, MAKELPARAM(pts[i].x, pts[i].y));
        SendMessage(hc, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pts[i].x, pts[i].y));
        SendMessage(hc, WM_LBUTTONUP  , MK_LBUTTON, MAKELPARAM(pts[i].x, pts[i].y));
        Sleep(16);
        return 1;
    }
    return 0;
}
inline uint WaitSearch(){
    fmov("零点");
    uint i = NameToIndex("寄售货币_加载中");
    uint x = pts[i].x, y = pts[i].y;
    uint c;
    while(1){
        if(WillStop()) Err("用户停止");
        //clr(0xC4); printf("[%d, PAUSE]", __LINE__); getch();
        //fcheck("查看单价");
        //fnc("一口价单价");
        fnc("寄售货币_价格");
        c = getPx(x, y);
        if(pts[i].c1 == c || pts[i].c2 == c){
            return 0;
        }
        if(NoFrame()){
            //Sleep(1);
            //return 1;
        }
        Sleep(1);
    }
}
inline uint PageSearch(){
    clr(0x0B);
    printf("\n搜索\n");
    fbtn("搜索");
    Sleep(32);
    return WaitSearch();
}
inline uint PagePrev(){
    if(fbtn("上一页") == fRESULT_DISABLE){
        return PageSearch();
    }else{
        clr(0x0B);
        printf("\n上一页\n");
        Sleep(32);
        return WaitSearch();
    }
}
inline uint PageNext(){
    clr(0x0B);
    printf("\n下一页\n");
    fbtn("下一页");
    Sleep(32);
    return WaitSearch();
}
uint Hot(){
    //getPx_name("搜索"); return;
    //getPx_name("寄售货币_加载中"); return;
    
    Sleep(16);
    if(fRESULT_CLICKED == fic("关闭公告")) return 0;
    if(fRESULT_CLICKED == fnc("拍卖行")) return 0;
    //if(fRESULT_CLICKED == fict("寄售货币")) return 0;
    //if(fRESULT_CLICKED == fict("道具")) return 0;
    //if(fRESULT_CLICKED == fict("强化材料")) return 0;
    Sleep(16);
    
    WaitSearch();


    Capture();
    uint v = val_Scan_jinbi();
    if(v == val_err){
        clr(0x0C);
        printf("挡");
        return 0;
    }else
    if(v <= valmax){
        clr(0x0A);
        printf("买%0.2f", (float)v/100);
        fict("寄售货币_第一列");
        Sleep(16);
        fbtn("寄售货币_购买");
        Sleep(16);
        fwc("确定购买");
        WaitSearch();
    }else{
        clr(0x0F);
        printf("贵%0.2f", (float)v/100);
        fbtn("寄售货币_刷新");
        Sleep(128);
    }
    printf("\n");
    return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    AllocConsole();
    *stdout = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT), "w");
    *stdin = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r" );
    HandleStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!perfInit()) Err("系统不支持高性能计时");
    system("title AS_收货");
    system("color 07");

    clr(0x07);
    printf("\x9 AvatarStar_自动化收金币工具 @雪星(Snowstar.Cyan@gmail.com)\n");
    printf("\n");
    WinLoad();
    clr(0x0F);
    uint index=0;
    printf("%d< 工作环境: [ESC]-视频-恢复默认值\n", ++index);
    printf("%d< 请不要把鼠标伸进游戏窗口内\n", ++index);
    printf("%d< 请不要把游戏窗口最小化\n", ++index);
    printf("%d< 请不要把游戏窗口移出屏幕\n", ++index);
    printf("%d< 请手动切换到 拍卖行 - 寄售货币\n", ++index);
    #if!DEBUG
    printf("%d< 请输入最高入手价格 （数量不计，肯定在10000以上）\n", ++index);
    printf("    >");
    clr(0x0A);
    float fvalmax; fflush(stdin); scanf("%f", &fvalmax);
    clr(0x0F);
    valmax = (uint)(fvalmax * 100);
    printf("%d< 确认收入所有价格为%0.2f以下的10000个以上的金币? (Y/N)\n", ++index, (float)valmax / 100);
    printf("    >");
    clr(0x0A);
    char r;        fflush(stdin); scanf("%c", &r);
    clr(0x0F);
    if (r != 'Y' && r != 'y') Err("用户取消");
    #else

    valmax = 7000;
    #endif
    printf("    < 开始! 你随时可以按");
        clr(0xB0);
    printf("[Scroll Lock]");
        clr(0x0F);
    printf("暂停/继续");
        clr(0xB0);
    printf("[F10]");
        clr(0x0F);
    printf("结束程序. \n\n");
    clr(0x07);

    //SetProcessDPIAware();
    while(!WillStop()){
        if(!Paused()){
            Hot();
        }else{
            Sleep(32);
        }
    }
    Err("用户停止");
    WinUnload();
    FreeConsole();
}