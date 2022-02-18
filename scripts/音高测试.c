//tcc_out=D:\L\tcc\build\音高测试.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

// 音高测试.c
// 更新
// # 2015/07/05 雪星(997596439@qq.com)
// 创建
///
#include <dos.h>
#include <windows.h>

int main(){//_
    unsigned int hz, t = 200;
    for(hz = 0; 1; hz+=50){
        printf("Beeeep~ %dHz %dms\n", hz, t);
        beep(hz, t);
    }
    system("pause");
}