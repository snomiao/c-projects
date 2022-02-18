//tcc_out=/build/鼠标粘附测试.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=
//version 0.13.0

// 鼠标边缘贴靠C++.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"

#include <io.h>
#include <fcntl.h> // control
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


#define PROCESS_PER_MONITOR_DPI_AWARE 0x2
void fixDPI() {
	// typedef HRESULT (WINAPI *IntFuncInt)(int);
	// HINSTANCE hDll = LoadLibraryA("Shcore.dll");
	// if (hDll){
	// 	int _ = ((IntFuncInt)GetProcAddress(hDll, "SetProcessDpiAwareness"))(PROCESS_PER_MONITOR_DPI_AWARE);
	// }
}


int EndKeyPressedQ() {
	return GetKeyState(VK_F10);
}

BITMAPINFO Win_bi;
HBITMAP Win_hbmp;
HDC Win_hdc;
HWND Win_hwnd;
RECT Win_box;

BITMAPINFO Clip_bi;
HBITMAP Clip_hbmp;
HDC Clip_hdc;
unsigned int*Clip_pixels;
int Clip_x;
int Clip_y;
unsigned int Clip_h;
unsigned int Clip_w;

void WinLoad() {
	fixDPI();
	
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	Win_hwnd = WindowFromPoint(ptMouse);
	//Win_hwnd = 0;
	Win_hdc = GetDC(Win_hwnd);

	POINT ptWindow;
	ClientToScreen(Win_hwnd, &ptWindow);
	
    Win_hbmp = (HBITMAP)GetCurrentObject(Win_hdc, OBJ_BITMAP);
	GetDIBits(Win_hdc, Win_hbmp, 0, 0, NULL, &Win_bi, DIB_RGB_COLORS);

	Win_box = { ptWindow.x, ptWindow.y, Win_bi.bmiHeader.biWidth, Win_bi.bmiHeader.biHeight};
	printf(" %d x %d, %d x %d ", Win_box.left, Win_box.top, Win_box.right, Win_box.bottom);
	SetCursorPos(Win_box.left, Win_box.top);

	// /dw = rct.right;             dh = rct.bottom;
	//printf("Client Rect: (%d, %d)\n             (%d, %d)\n", dx, dy, dw, dh);
}

// unsigned char*矩阵1;
// unsigned char*矩阵2;

// void WinLoad() {

// 	hMemDC = 
//     HBITMAP directBmp = CreateDIBSection(hMemDC, (BITMAPINFO*)&RGB24BitsBITMAPINFO,   
//         DIB_RGB_COLORS, (void **)&lpBitmapBits, NULL, 0);  
//     HGDIOBJ previousObject = SelectObject(hMemDC, directBmp);  

// 	//dllname = "User32.dll";

// 	//"Shcore.dll"
// 	//SetProcessDpiAwareness, 0, PROCESS_PER_MONITOR_DPI_AWARE);

// 	hdcScreen = GetDC(NULL);
// 	hbmpScreen = (HBITMAP)GetCurrentObject(hdcScreen, OBJ_BITMAP);

// 	binfoScreen.bmiHeader.biSize = sizeof(binfoScreen.bmiHeader);
// 	BOOL re;
// 	//re = GetDIBits(hdcScreen, hbmpScreen, 0, 0, NULL, &binfoScreen, DIB_RGB_COLORS); // 查询BITMAPINFO int nBitClrUsed = 0;
// 	BitBlt
// 	// // 																			 //printf("33 re: %d\n", re);getchar();
// 	binfoScreen.bmiHeader.biCompression = BI_RGB;
// 	printf(" %d", re);
// 	printf(" %d", BI_RGB);
// 	printf(" %d", binfoScreen.bmiHeader.biCompression);
// 	wScreen = binfoScreen.bmiHeader.biWidth;
// 	hScreen = binfoScreen.bmiHeader.biHeight;

// 	// 	//截图hdc = CreateCompatibleDC(hdcScreen);
// 	// 	//hbmpScreen = CreateCompatibleBitmap(hdcScreen, wScreen, 截图高);
// 	// 	//matrixScreen = (unsigned int*)calloc(截图宽 * 截图高, sizeof(int));
// 	matrixScreen = (unsigned int*)calloc(wScreen * hScreen, sizeof(int));
// 	printf(" %d x %d \n", wScreen, hScreen);



// 	getchar();

// }

void WinUnload() {
	//DeleteDC(截图dc);
	//free(matrixScreen);
}

// RECT 取坐标为中心的区域(POINT 坐标, int 宽, int 高) {
// 	return RECT{
// 		坐标.x - 宽 / 2,
// 		坐标.y - 高 / 2,
// 		坐标.x - 宽 / 2 + 宽, // 规避四舍五入
// 		坐标.y - 高 / 2 + 高,
// 	};
// }
// #define SCAN(y) (hScreen - y)
void Capture() {
	//POINT pt;
	//GetCursorPos(&pt);
	//截图区域 = 取坐标为中心的区域(pt, wScreen, hScreen);

	// 	BOOL re;

	// 	binfoScreen.bmiHeader.biClrUsed = binfoScreen.bmiHeader.biBitCount / 8;
	// 	printf(" %d %d", binfoScreen.bmiHeader.biBitCount, binfoScreen.bmiHeader.biClrUsed);
	// 	re = GetDIBits(hdcScreen, hbmpScreen, 0, 300, matrixScreen, &binfoScreen, DIB_RGB_COLORS);
	// 	printf(" %d", re);
	// 	//BITMAPINFO 截图binfo2 = 截图binfo;
	// /*	for (size_t i = 0; i < 200 * wScreen; i++)
	// 	{
	// 		matrixScreen[i] |= 0x0000EE;
	// 	}*/
	// 	re = SetDIBitsToDevice(hdcScreen, 0, 0, wScreen, 600, 0, 0, 0, 300, matrixScreen, &binfoScreen, DIB_RGB_COLORS);
	// 	printf(" %d", re);
	// 	printf(" asdf\n");
	//getchar();
}
void Preview()
{

	/*SetDIBitsToDevice(
	hdcScreen,
	cx, cy,
	cw - (dx - cx), ch,
	0, 0,
	cy + ch - dy - dh, dh, cdata, &Win_bi, DIB_RGB_COLORS);*/
}

void MainLoop() {
	Capture();
	//	SetCursorPos(0, 0);
}

HANDLE hStdout;
inline void clr(int color) {
	SetConsoleTextAttribute(hStdout, color);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	AllocConsole();
	*stdout = *freopen("CONOUT$", "w", stdout);
	*stdin = *freopen("CONIN$", "r", stdin);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	system("title Mona_边缘贴靠");
	clr(0x07);
	printf("\x9 鼠标边缘贴靠 @雪星(snomiao@gmail.com)\n");
	clr(0x0F);
	printf("\n");
	clr(0x0F);
	printf("    < 开始! 你随时可以按");
	clr(0x0B);
	printf("[F10]");
	clr(0x0F);
	printf("结束程序. \n\n");
	clr(0x07);

	WinLoad();

	while (!EndKeyPressedQ())
		MainLoop();

	FreeConsole();
	return 0;
}

