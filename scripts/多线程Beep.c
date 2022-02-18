//tcc_out=/build/多线程Beep.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=
//version 0.0.1.0

//多线程Beep.c
//2015/02/09 雪星(997596439@qq.com)
//完成！

//理想输出


#include <dos.h>
#include <windows.h>
#include <process.h>
#define uint unsigned int
char *mapKey  = "ZSXDCVGBHNJMQ2W3ER5T6Y7UI9O0P[=] \\";
int   mapHz[] = { 262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494,
                  523,  554,  587,  622,  659,  698,  740,  784,  831,  880,  932,  988,
                 1046, 1109, 1175, 1245, 1318, 1397, 1480, 1568, 1661, 1760, 1865, 1976};

int beeping = 0;
uint __stdcall ThreadBeep(void *param){
    uint hz = *((uint*)(param + 0));
    uint t  = *((uint*)(param + 4));
    free(param);

    printf("Beeeep~ %d %d\n", hz, t);
    beeping++;beep(hz, t);beeping--;
    _endthread();
    return 0;
}
inline uint thBeep(uint hz,uint t){
    uint t_keep = t - beeping * 123;
    int bit_abs = (int)t_keep >> (sizeof(int)*8-1); //带符号右移，得到正负号, 负值为 0xFFFFFFFF, 正值为 0
    t_keep      = (t_keep ^ bit_abs) - bit_abs; //异或，如果前面是负值，得到反码, 然后+1

    uint *BeepData = (uint*)malloc(2*sizeof(uint));
    BeepData[0] = hz;     //用2位数组传子线程的参数
    BeepData[1] = t_keep;

    _beginthreadex(0, 0, ThreadBeep, BeepData, 0, 0);
}
inline uint beepKey(char key){

    for(int i = 0; mapKey[i] && (key == mapKey[i] ? printf(" %c ", key) && thBeep(mapHz[i], 400) : 1); i++);
}
int main(){
    char  key;
    char* start = "ZZBBNNBVVCCXXZBBVVCCXBBVVCCXZZBBNNBVVCCXXZ";
    for (int i = 0; start[i]; ++i){
        beepKey(start[i]);
        sleep(123);
    }
    beeping = 0;
    printf("
多线程/不卡键/键盘钢琴
do re mi fa so la si
Q  W  E  R  T  Y  U 
do re mi fa so la si
Z  X  C  V  B  N  M 
ESC退出
");
    while(VK_ESCAPE != (key = getch()) ){
        if(key == 32/*space*/) beeping = 0;
        beepKey(key);
    }
    system("pause");
}