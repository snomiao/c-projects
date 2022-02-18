//tcc_out=/Build/下雪.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define uint unsigned int
#define SnowNumber (uint)500 //雪点数量
#define true 1
struct SnowNode
{
 POINT postion;                                               //雪点位置
 int   iColor;                                                //先前的颜色f
 int   iSpeed;                                                //下落速度 
 int   iMove;                                                 //下落距离
 int   iStick;                                                //粘贴度
};
struct SnowNode SnowNodes[SnowNumber];                        //雪点数组
int   hTimer=0;
int   CrWind=0;
int   CrStep=0;                                               //当前循环步数(用于限速)
int   ScreenWidth=0;                                          //屏幕宽度
int   ScreenHeight=0;                                         //屏幕高度

void GetScreenSize();
void CALLBACK TimerProc(HANDLE hWnd,UINT uMsg,UINT idEvent,DWORD dwTime);
void InitSnowNodes();
void MoveSnowNodes();

                                                              //入口

int WINAPI  WinMain(HINSTANCE hInstance,
       HINSTANCE hPrevInstance,
       LPSTR  lpCmdLine,
       int   nCmdShow
       )
{

 MSG msg;                                                     //标准windows消息 
 LARGE_INTEGER Frequency;                                     //高性能定时器频率
 LARGE_INTEGER StartCt,EndCt;                                 //高性能定时器计数
float ElapsedTime;                                            //时间间隔
 srand((unsigned)time(NULL));
 GetScreenSize();
 InitSnowNodes();
 QueryPerformanceFrequency(&Frequency);
 hTimer=SetTimer(0,0,rand()%5*50,(TIMERPROC)TimerProc);
 if(hTimer==0)
 {
  MessageBox(0,TEXT("创建定时器失败"),TEXT("提示"),MB_OK|MB_ICONINFORMATION);
  return -1;
 }
 RegisterHotKey(0,0,MOD_CONTROL,(int)'L');
 while(1)
 {
  QueryPerformanceCounter(&StartCt);                          //执行运算前计数值
  if(PeekMessage(&msg,0,0,0,1))
  {
   switch(msg.message)
   {
    case WM_TIMER: TimerProc(0,0,0,0);
        break;                                                //预设风向改变时间已到
    case WM_HOTKEY: KillTimer(0,hTimer);                      //删除随机风向定时 器
        UnregisterHotKey(0,0);                                //删除退出热键
        InvalidateRect(0,NULL,true);
        exit(1);
        break;
    case WM_DISPLAYCHANGE:
        GetScreenSize();                                      //重新取屏幕的尺寸
        InitSnowNodes();                                      //初始化雪点的数组
        break;
   }
  }
  MoveSnowNodes();
  QueryPerformanceCounter(&EndCt);                            //执行运算后的计数值
  ElapsedTime=(EndCt.QuadPart-StartCt.QuadPart)/Frequency.QuadPart;
  if((ElapsedTime<0.0005))
   Sleep(2);                                                  //简单限速
  else if(ElapsedTime<0.0010)
    Sleep(1);
    else if(ElapsedTime<0.0015)
     Sleep(3);
 }
                                                              //MessageBox(0,TEXT("消息"),TEXT("消息"),MB_OK|MB_ICONINFORMATION);
 return 0;
}
void GetScreenSize()
{
 ScreenWidth=GetSystemMetrics(SM_CXSCREEN);
 ScreenHeight=GetSystemMetrics(SM_CYSCREEN);
 return ;
}
void CALLBACK TimerProc(HANDLE hWnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{
                                                              // MessageBox(0,TEXT("消息"),TEXT("消息"),MB_OK|MB_ICONINFORMATION);
 srand((unsigned)time(NULL));
 if(hTimer==0)
 {
  MessageBox(0,TEXT("创建定时器失败"),TEXT("提示"),MB_OK|MB_ICONINFORMATION);
  return ;
 }
 SetTimer(0,hTimer,((rand()%27+4)*50),(TIMERPROC)TimerProc); //// 重设下次风向改变时间
 //修改风向
 if(CrWind!=0)
  CrWind=0;
 else
     CrWind=rand()%3-1;
 return ;
}
void InitSnowNodes()
{
 HDC hScreenDC=0;
 int j=0;
 hScreenDC=CreateDC("DISPLAY",NULL,NULL,NULL);
  if(hScreenDC==NULL)
 {
  MessageBox(0,"获取屏幕DC失败!","信息",MB_OK|MB_ICONERROR);
  return ;
 }
 srand((unsigned)time(NULL));
 for(j=0;j<SnowNumber;j++)
 {
  SnowNodes[j].postion.x=rand()%ScreenWidth;
  SnowNodes[j].postion.y=rand()%ScreenHeight;
  SnowNodes[j].iColor=GetPixel(hScreenDC,SnowNodes[j].postion.x,SnowNodes[j].postion.y);
  SnowNodes[j].iSpeed=(rand()%5+1);       //每次下落距离（1-5）
  SnowNodes[j].iStick=(100-rand()%SnowNodes[j].iSpeed); //粘贴度（几次循环作一次粘贴连判断
//  cout<<SnowNodes[j].postion.x<<"   Y:"<<SnowNodes[j].postion.y<<endl;
  
 }
 DeleteDC(hScreenDC);
}
void MoveSnowNodes()
{
// MessageBox(0,TEXT("消息"),TEXT("消息"),MB_OK|MB_ICONINFORMATION);
 HDC hScreenDC=0;
 srand((unsigned)time(NULL));
 int x=0,y=0,i=0;
 hScreenDC=CreateDC("DISPLAY",NULL,NULL,NULL);
 if(hScreenDC==NULL)
 {
  MessageBox(0,"获取屏幕DC失败!","信息",MB_OK|MB_ICONERROR);
  return ;
 }
// TextOut(hScreenDC,0,0,"虽然大检查顺顺藤摸瓜克格勃呀加",0);
 for(i=0;i<SnowNumber;i++)
 {
  //控制雪点下降速度
  if((CrStep%SnowNodes[i].iSpeed)!=0)
   continue;
  //恢复上次被覆盖点
  if((GetPixel(hScreenDC,SnowNodes[i].postion.x,SnowNodes[i].postion.y))==0XFFFFFF)
   SetPixel(hScreenDC,SnowNodes[i].postion.x,SnowNodes[i].postion.y,SnowNodes[i].iColor);
  //根据几向作随机飘落
  x=SnowNodes[i].postion.x+rand()%3+CrWind;
  y=SnowNodes[i].postion.y+SnowNodes[i].iMove+2;
  //积雪（停留）效果处理
  if(  ( (CrStep%SnowNodes[i].iStick)==0)
     &&( (GetPixel(hScreenDC,x,y))!=(GetPixel(hScreenDC,x,y+1)))
     &&( (GetPixel(hScreenDC,x-1,y))!=(GetPixel(hScreenDC,x-1,y+1)))
     &&( (GetPixel(hScreenDC,x+1,y))!=GetPixel(hScreenDC,x+1,y+1))
     )
  {
   //稍稍调整坐标
   if(GetPixel(hScreenDC,x,y-1)==GetPixel(hScreenDC,x,y-2))
   {
    y--;
   }
   else
   {
       if(GetPixel(hScreenDC,x,y-1)==GetPixel(hScreenDC,x,y-2))
     y++;
    x+=CrWind;
   }
   //画三个雪花点
   SetPixel(hScreenDC,x,y,0XFFFFFF);
   SetPixel(hScreenDC,x+1,y+1,0XFFFFFF);
   SetPixel(hScreenDC,x-1,y+1,0XFFFFFF);
   //重生雪点
   SnowNodes[i].postion.x=rand()%ScreenWidth;
   SnowNodes[i].postion.y=rand()%10;
   SnowNodes[i].iColor=GetPixel(hScreenDC,SnowNodes[i].postion.x,SnowNodes[i].postion.y);
   
  }
  else
  {
   if( (x<0) || (x>ScreenWidth) || (y>ScreenHeight))
   {
    SnowNodes[i].postion.x=(rand()%10);
    SnowNodes[i].postion.y=(rand()%ScreenWidth);
    SnowNodes[i].iColor=GetPixel(hScreenDC,SnowNodes[i].postion.x,SnowNodes[i].postion.y);
   }
   else
   {
    //保存颜色并绘制雪点
    SnowNodes[i].iColor=GetPixel(hScreenDC,x,y);
    SetPixel(hScreenDC,x,y,0XFFFFFF);
    //此时保存新雪点位置
    SnowNodes[i].postion.x=x;
    SnowNodes[i].postion.y=y;
   }
  }
 }
 DeleteDC(hScreenDC);
 CrStep++;
}