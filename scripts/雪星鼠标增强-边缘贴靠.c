//tcc_out=/build/雪星鼠标增强-边缘贴靠.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=
//version 0.13.0




#include <io.h>
#include <fcntl.h> // control
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

HANDLE hStdout;
#define clr(color) ; //(SetConsoleTextAttribute(hStdout, color))

// <perfTicker.h>
    LARGE_INTEGER perfFreq, perfCount;
    unsigned int perfInit(){
        return QueryPerformanceFrequency(&perfFreq);
    }
    unsigned int perfTick(){
        QueryPerformanceCounter(&perfCount);
        return (perfCount.QuadPart * 1000) / perfFreq.QuadPart;
    }

inline uint WillStop(){
    return GetKeyState(VK_F10);
}

void Hello(){
    /* Mona */
    system("title Mona_边缘贴靠");
    system("color 07");

    clr(0x07);
    printf("\x9 Mona_边缘贴靠 @雪星(snomiao@gmail.com)\n");
    printf("\n");
    //WinLoad();
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
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    /* 申请控制台 */
    AllocConsole();
    *stdout = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT), "w");
    *stdin = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r" );
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    /* 加载计时器 */
    if(!perfInit()) Err("系统不支持高性能计时");

    Hello();
    system("pause");
    //SetProcessDPIAware();
    while(!WillStop()) Hot();
    //Err("用户停止");
    //end();
    //  WinUnload();
    FreeConsole();

}


// #define uint unsigned int

// HWND hwndGame;
// HDC hdc;
// HDC hdcScreen;
// HDC hdcDebug;
// unsigned char*cdataDebug;

// HBITMAP hBmpDebug;
// HBITMAP hBmp;
// BITMAPINFO binfo;
// unsigned char*cdata;
// uint cx, cy, cw, ch;
// uint dx, dy, dw, dh;



// uint WinUnload(){
//     //ReleaseDC(hwndGame, hdc);
// }
// inline uint Err(char* err){
//     clr(0xC4); printf("[停止: %s]\n", err); fflush(stdin); getchar();
//     WinUnload();
//     exit(0);
//     return 0;
// }

// uint WinLoad(){
//     /* 缓冲区 */
//     cdata = calloc(cw * ch, sizeof(int));
//     hBmp = (HBITMAP)GetCurrentObject(hdc , OBJ_BITMAP);
//     binfo.bmiHeader.biSize          = sizeof(binfo.bmiHeader);
//     binfo.bmiHeader.biCompression   = BI_RGB;
//     binfo.bmiHeader.biPlanes        = 1;
//     binfo.bmiHeader.biBitCount      = 32;
//     binfo.bmiHeader.biWidth         = cw;
//     binfo.bmiHeader.biHeight        = ch;

//     /* 调试区 */
//     hdcScreen = GetDC(0);
//     hdcDebug   = CreateCompatibleDC(hdc);
//     cdataDebug = calloc(cw * ch, sizeof(int));
//     hBmpDebug  = (HBITMAP)GetCurrentObject(hdcDebug , OBJ_BITMAP);
//     SelectObject(hdcDebug, hBmpDebug);


//     HWND hide;
//     hide = FindWindow("ConsoleWindowClass", "管理员:  Mona_边缘贴靠");
//     if(!hide)
//         hide = FindWindow("ConsoleWindowClass", "Mona_边缘贴靠");
//     ShowWindow(hide, 2);
//     return 0;
// }

// uint Capture(){
//     GetDIBits(hdc, hBmp, cy + ch - dy - dh, dh, cdata, &binfo, DIB_RGB_COLORS);
// }

// uint Preview(){
//     //SetDIBits(hdc, hBmp, cy + ch - dy - dh, dh, cdata, &binfo, DIB_RGB_COLORS);
//     //BitBlt(hdcScreen, 0, 0, cw, ch, hdc, 0, 0, SRCCOPY);
//     //BitBlt(hdcScreen, 0, 0, cw, ch, hdcDebug, 0, 0, SRCCOPY);
//     SetDIBitsToDevice(
//         hdcScreen,
//         cx, cy,
//         cw-(dx-cx), ch,
//         0, 0,
//         cy + ch - dy - dh, dh, cdata, &binfo, DIB_RGB_COLORS);
    
//     // SetDIBitsToDevice(
//     //     hdcScreen,
//     //     //3843, 544,
//     //     //0, -(dy-cy),
//     //     cx, cy+dh,
//     //     cw-(dx-cx), ch,
//     //     0, 0,
//     //     cy + ch - dy - dh, dh, cdataDebug, &binfo, DIB_RGB_COLORS);
//     Sleep(1);
//     //BitBlt(hdcScreen, 3843, 544, cw, ch, hdc, 0, 0, SRCCOPY);
//     //unsigned char*xcdata = calloc(cw * ch, sizeof(int));
//     //Free(xcdata);
// }

// uint getPx(uint x, uint y){
//     Capture();
//     uint scan = 4 * cw * ( dh -  1  - y);
//     uint car  = 4 *      ((dx - cx) + x);
//     return cdata[scan + car + 0] << 0x00|
//            cdata[scan + car + 1] << 0x08|
//            cdata[scan + car + 2] << 0x10;
// }
// int Abs(int x){
//     if(x<0) return -x;
//     return x;
// }

// #define SCAN(y) (4 * cw * ( dh -  1  - y))
// #define CAR(x)  (4 *      ((dx - cx) + x))
// #define IMGA_R(x, y)   (cdata[SCAN(y) + CAR(x) + 2])
// #define IMGA_G(x, y)   (cdata[SCAN(y) + CAR(x) + 1])
// #define IMGA_B(x, y)   (cdata[SCAN(y) + CAR(x) + 0])
// //#define IMGA_ARGB(x, y) (*((int*)cdata + SCAN(y) + CAR(x)))
// #define IMGB_R(x, y) (cdataDebug[SCAN(y) + CAR(x) + 2])
// #define IMGB_G(x, y) (cdataDebug[SCAN(y) + CAR(x) + 1])
// #define IMGB_B(x, y) (cdataDebug[SCAN(y) + CAR(x) + 0])

// uint FilterToGreen(){
    

//     Capture();

//     POINT pnt;
//     GetCursorPos(&pnt);

//     uint mx, my;
//     mx = pnt.x - (dx); // cx
//     my = pnt.y - (dy); // cy

//     int coreR  = 2;
//     int vaildR = 55;

//     // mx -= vaildR;
//     // my -= vaildR;

//     #define SCAN_BEGIN \
//         for(uint iy = coreR; iy < dh-coreR; ++iy){ \
//             for(uint ix = coreR; ix < dw-coreR; ++ix){ \
//                 int distant2 = Abs((ix - mx)*(ix - mx) + (iy - my)*(iy - my)); \
//                 if(distant2 < vaildR*vaildR){
    
//     #define SCAN_END \
//                 } \
//             } \
//         }
    

//     // 获得灰度图像，存到 B 通道
//     SCAN_BEGIN;
//     //uint c = (IMGA_R(ix, iy) + IMGA_G(ix, iy) + IMGA_B(ix, iy)) / 3;
//     // uint c = (BYTE)(0.072169*IMGA_B(ix, iy) +
//     //                 0.715160*IMGA_G(ix, iy) +
//     //                 0.212671*IMGA_R(ix, iy) );
//     uint c = (IMGA_R(ix, iy)*38 + IMGA_G(ix, iy)*75 + IMGA_B(ix, iy)*15) >> 7;
//     IMGA_B(ix, iy) = c;
//     //IMGA_R(ix, iy) = IMGA_G(ix, iy) = IMGA_B(ix, iy) = c;
//     //IMGA_R(ix, iy) = IMGA_G(ix, iy) = 0;
//     //IMGA_R(ix, iy) = 0;
//     SCAN_END;
    
    
//     // 高斯滤波，存到 G 通道
//     float kernelGaosi[][] = { {2,  4,  5,  4, 2} ,
//                               {4,  9, 12,  9, 4} ,
//                               {5, 12, 15, 12, 5} ,
//                               {4,  9, 12,  9, 4} ,
//                               {2,  4,  5,  4, 2}};

//     uint kernelGaosiW = sizeof(kernelGaosi[0]) / sizeof(float);
//     uint kernelGaosiH = sizeof(kernelGaosi) / sizeof(float) / kernelGaosiW;

//     SCAN_BEGIN;
//     float c = 0;
//     c = 0;
//     for(int iry = 0; iry < kernelGaosiH; ++iry)
//         for(int irx = 0; irx < kernelGaosiW; ++irx)
//             c += IMGA_B(ix + irx-2, iy + iry-2) * kernelGaosi[iry][irx];
//     c = (BYTE)(Abs(c) / 159);
//     //IMGA_G(ix, iy) = (BYTE)c;
//     IMGA_R(ix, iy) = IMGA_G(ix, iy) = IMGA_B(ix, iy) = c;
//     SCAN_END;


//     // 绿化
//     // SCAN_BEGIN;
//     // IMGA_B(ix, iy) = IMGA_R(ix, iy) = 0;
//     // SCAN_END;

//     // Sabel 算子，存到右边的RGB通道
//     int kernel[][] =  { {-1,  0,  1},
//                         {-2,  0,  2},
//                         {-1,  0,  1}};
//     int kernel2[][] = { {-1, -2, -1},
//                         { 0,  0,  0},
//                         { 1,  2,  1}};
//     uint DX = sizeof(kernel[0]) / sizeof(int);
//     uint DY = sizeof(kernel) / sizeof(int) / DX;

//     SCAN_BEGIN;
//     uint c = 0;
//     c = 0;
//     for(int iry = 0; iry < DY; ++iry)
//         for(int irx = 0; irx < DX; ++irx)
//             c += IMGA_G(ix + irx, iy + iry) * kernel[iry][irx];
//     for(int iry = 0; iry < DY; ++iry)
//         for(int irx = 0; irx < DX; ++irx)
//             c += IMGA_G(ix + irx, iy + iry) * kernel2[iry][irx];
//     c = Abs(c);
//     IMGB_B(ix, iy) = c / 2;
//     SCAN_END;
    
//     //SCAN_BEGIN;
//     //IMGA_G(ix + 2 * vaildR, iy) = IMGB_B(ix, iy);
//     //IMGA_R(ix + 2 * vaildR, iy) = 0; IMGA_B(ix + 2 * vaildR, iy) = 0;
//     //SCAN_END;
    
//     //IMGB_G(maxcx, maxcy) = 0xFF;
//     // 
//     SCAN_BEGIN;
//     IMGB_B(ix, iy) = IMGB_B(ix, iy) * vaildR * 8 / ( vaildR + distant2 );
//     SCAN_END;


//     // // 
//     // int kernelRuiHua[][] = {{-1,  -1,  -1},
//     //                         {-1,   9,  -1},
//     //                         {-1,  -1,  -1}};

//     // uint kernelRuiHuaW = sizeof(kernelRuiHua[0]) / sizeof(int);
//     // uint kernelRuiHuaH = sizeof(kernelRuiHua) / sizeof(int) / kernelRuiHuaW;
//     // SCAN_BEGIN;
//     // uint c = 0;
//     // c = 0;
//     // for(int iry = 0; iry < kernelRuiHuaH; ++iry)
//     //     for(int irx = 0; irx < kernelRuiHuaW; ++irx)
//     //         c += IMGB_B(ix + irx, iy + iry) * kernelRuiHua[iry][irx];
//     // //c = Abs(c);
//     // c = Abs(c) / 10;
//     // IMGB_R(ix, iy) = c;
//     // SCAN_END;



//     uint maxc = 0;
//     uint maxcx = mx;
//     uint maxcy = my;
//     SCAN_BEGIN;
//     uint c = IMGB_B(ix, iy);
//     if(c > maxc){
//         maxc = c;
//         maxcx = ix;
//         maxcy = iy;
//     }
//     SCAN_END;
//     // if(maxc){
//     //     IMGB_G(maxcx, maxcy) = 0xFF;
//     //     IMGA_R(maxcx, maxcy) = 0xFF;
//     //     IMGA_G(maxcx, maxcy) = 0xFF;
//     //     IMGA_B(maxcx, maxcy) = 0xFF;
//     // }



//     // SCAN_BEGIN;
//     // //if(distant2 > 9*9){
//     //     uint c = IMGA_G(ix, iy);
//     //     // c = c *50 / (distant2);
//     //     // c = Abs(c);
//     //     // if(c>255) c=255;
//     //     IMGB_R(ix, iy) = c;
//     //     //IMGB_R(ix, iy) = IMGB_B(ix, iy) = IMGB_G(ix, iy);
//     // //}
//     // SCAN_END;

//     // 标记鼠标所在中心
//     for(int iry = 0; iry < 3; ++iry){
//         for(int irx = 0; irx < 3; ++irx){
//             IMGA_R(mx + irx - 1, my + iry - 1) = 0xFF;
//             IMGA_G(mx + irx - 1, my + iry - 1) = 0x00;
//             IMGA_B(mx + irx - 1, my + iry - 1) = 0xFF;
//         }
//     }

//     // 标记边缘帖点
//     for(int iry = 0; iry < 3; ++iry){
//         for(int irx = 0; irx < 3; ++irx){
//             IMGA_R(maxcx + irx - 1, maxcy + iry - 1) = 0x00;
//             IMGA_G(maxcx + irx - 1, maxcy + iry - 1) = 0xFF;
//             IMGA_B(maxcx + irx - 1, maxcy + iry - 1) = 0x00;
//         }
//     }

//     Preview();

//     static uint moved = 0;
//     #define DWORDPOS(x, y) (( y << 16 ) | ( x & 0xffff ))
//     if(GetAsyncKeyState(0xC0)){

//         if(!moved){
//             //SetCursorPos(dx + maxcx, dy + maxcy);
//             //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
//             //SetCursorPos(dx + mx, dy + my); 
            
//             SendMessage(hwndGame, WM_LBUTTONDOWN, 1, DWORDPOS(maxcx, maxcy));
//             SendMessage(hwndGame, WM_LBUTTONUP  , 0, DWORDPOS(maxcx, maxcy));

//             moved = 1;
//         }else{
//             //SendMessage(hwndGame, WM_MOUSEMOVE, 0, DWORDPOS(maxcx, maxcy));
//         }
//     }else{
//         //SendMessage(hwndGame, WM_MOUSEMOVE, 0, DWORDPOS(maxcx, maxcy));
//         moved = 0;
//     }
//     //getchar();
//     //ShowCursor(FALSE);
//     //SetCursor(NULL);
// }
// uint FilterToGreen2(){
    

//     Capture();

//     POINT pnt;
//     GetCursorPos(&pnt);

//     uint mx, my;
//     mx = pnt.x - (dx); // cx
//     my = pnt.y - (dy); // cy
//     //printf("m: %d, %d\n", mx, my);
    
//     //cdata[0] = 0;
//     // int kernel[][] = {
//     //     {-1, 0},
//     //     {0, 1}
//     // };
//     // int kernel2[][] = {
//     //     {0, 1},
//     //     {-1, 0}
//     // };
//     int kernel[][] = {    {-1,  0,  1},
//                         {-2,  0,  2},
//                         {-1,  0,  1}};
//     int kernel2[][] = {   {-1, -2, -1},
//                         { 0,  0,  0},
//                         { 1,  2,  1}};

//     // int kernel[][] = {
//     //     {1, -1}
//     // };

//     uint DX = sizeof(kernel[0]) / sizeof(int);
//     uint DY = sizeof(kernel) / sizeof(int) / DX;
//     // printf("%08X, %08X", DX, DY);

//     int vaildR = 999;
//     for(uint iy = 0; iy < dh; ++iy){
//         for(uint ix = 0; ix < dw; ++ix){

//             int distant2 = Abs((ix - mx)*(ix - mx) + (iy - my)*(iy - my));
//             IMGA_R(ix, iy) = (IMGA_R(ix, iy) + IMGA_G(ix, iy) + IMGA_B(ix, iy)) / 3;
//             IMGA_R(ix, iy) = IMGA_G(ix, iy) = IMGA_B(ix, iy);
//         }
//     }
//     for(uint iy = 0; iy < dh - DY; ++iy){
//         for(uint ix = 0; ix < dw - DX; ++ix){

//             int distant2 = Abs((ix - mx)*(ix - mx) + (iy - my)*(iy - my));
//             if(distant2 <= vaildR*vaildR){
//                 int c;

//                 c = 0;
//                 for(int iry = 0; iry < DY; ++iry)
//                     for(int irx = 0; irx < DX; ++irx)
//                         c += IMGA_G(ix + irx, iy + iry) * kernel[iry][irx];
//                 for(int iry = 0; iry < DY; ++iry)
//                     for(int irx = 0; irx < DX; ++irx)
//                         c += IMGA_G(ix + irx, iy + iry) * kernel2[iry][irx];
//                 c = Abs(c);
//                 IMGB_B(ix, iy) = c / 2;


//                 // c = 0;
//                 // for(int iry = 0; iry < DY; ++iry)
//                 //     for(int irx = 0; irx < DX; ++irx)
//                 //         c += IMGA_B(ix + irx, iy + iry) * kernel[iry][irx];
//                 // for(int iry = 0; iry < DY; ++iry)
//                 //     for(int irx = 0; irx < DX; ++irx)
//                 //         c += IMGA_B(ix + irx, iy + iry) * kernel2[iry][irx];
//                 // c = Abs(c);
//                 // IMGB_B(ix, iy) = c / 2;


//                 // c = 0;
//                 // for(int iry = 0; iry < DY; ++iry)
//                 //     for(int irx = 0; irx < DX; ++irx)
//                 //         c += IMGA_R(ix + irx, iy + iry) * kernel[iry][irx];
//                 // for(int iry = 0; iry < DY; ++iry)
//                 //     for(int irx = 0; irx < DX; ++irx)
//                 //         c += IMGA_R(ix + irx, iy + iry) * kernel2[iry][irx];
//                 // c = Abs(c);
//                 //  IMGB_R(ix, iy) = c / 2;
//             }
//         }
//     }
    
//     for(uint iy = 0; iy < dh - DY; ++iy){
//         for(uint ix = 0; ix < dw - DX; ++ix){
//             int distant2 = Abs((ix - mx)*(ix - mx) + (iy - my)*(iy - my));
//             if(distant2 <= vaildR*vaildR){
//                 //IMGB_R(ix, iy) = IMGB_G(ix, iy) * 2000 / distant2;
//                 if(distant2 > 9*9){
//                     int c = IMGB_B(ix, iy);
//                     c = c *50 / (distant2);
//                     c = Abs(c);
//                     if(c>255) c=255;
//                     IMGB_R(ix, iy) = c;
//                     // If(IMGB_G(ix, iy) > 255){
                        
//                     // }
//                     //IMGB_R(ix, iy) = IMGB_B(ix, iy) = IMGB_G(ix, iy);
//                 }
//             }
//         }
//     }
//     uint maxPoint = 0;
//     uint maxPointX = 0;
//     uint maxPointY = 0;
//     for(uint iy = 0; iy < dh - DY; ++iy){
//         for(uint ix = 0; ix < dw - DX; ++ix){
//             int distant2 = Abs((ix - mx)*(ix - mx) + (iy - my)*(iy - my));
//             if(distant2 <= vaildR*vaildR){
//                 uint c = IMGB_R(ix, iy);
//                 if(maxPoint <= c){
//                     maxPoint = c;
//                     maxPointX = ix;
//                     maxPointY = iy;
//                 }
//                 IMGB_G(ix, iy) = 0;
//             }
//         }
//     }

//     for(int iy = -3; iy < 3; ++iy){
//         for(int ix = -3; ix < 3; ++ix){
//             IMGB_G(maxPointX, maxPointY) = 0xFF;
//         }
//     }
//     IMGB_R(mx, my) = IMGB_G(mx, my) = IMGB_B(mx, my) = 0xFF;

//     //IMGB_R(ix, iy) = IMGB_G(ix, iy) = IMGB_B(ix, iy);

//     //for (int i = 0; i < 80000; ++i){
//     //    cdata[i] = 0;
//     //}
//     //cdata[] = 4 * cw * 
//     if(GetAsyncKeyState(0xC0)){
//         SetCursorPos(dx + maxPointX-3, dy + maxPointY-3);
//     }
//     Preview();
//     //getchar();
// }

// uint getPxRelative(uint x, uint y){
//     POINT pnt;
//     uint mx, my;
//     GetCursorPos(&pnt);
//     mx = pnt.x; my = pnt.y;

//     return getPx(mx - (cx + dx) + x, my - (cy + dy) + y);
// }

// #define val_none (uint)-1
// #define val_err  (uint)-2
// //#define val_Item1 (uint)352
// uint Hot(){
//     // uint px = getPxRelative(0, 0);
//     // printf("color %08X\n", px);
//     //SetCursor(LoadCursor(NULL, IDC_WAIT));
//     //ShowCursor(FALSE);
//     FilterToGreen();
//     return 0;
// }
// void begin(){
    

// }
// void end(){
//     WinUnload();
//     FreeConsole();
// }

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
// {
//     begin();
//     system("title Mona_边缘贴靠");
//     system("color 07");

//     clr(0x07);
//     printf("\x9 Mona_边缘贴靠 @雪星(snomiao@gmail.com)\n");
//     printf("\n");
//     WinLoad();
//     clr(0x0F);
//     uint index=0;
//     clr(0x0A);
//     clr(0x0F);
//     clr(0x0A);
//     clr(0x0F);
//     printf("    < 开始! 你随时可以按");
//     clr(0xB0);
//     printf("[F10]");
//     clr(0x0F);
//     printf("结束程序. \n\n");
//     clr(0x07);
//     //SetProcessDPIAware();
//     while(!WillStop()) Hot();
//     Err("用户停止");
//     end();
// }