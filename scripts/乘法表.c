//tcc_out=/build/乘法表.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//乘法表.c
//2015/02/09 雪星(997596@gmail.com)
//完成！赠送一个16进制版本 FF乘法表

//理想输出
//1
//2   4
//3   6    9
//..........
//9  18   27 .... 81


int main(){
    system("title 乘法表");

    //单循环
    int x=0,y=1;
    while(x++<y?:y++<9?x=1:0)
        printf(x==y?"%d\n":"%d ",x*y);

    int X=0,Y=1;
    while(X++<Y?:Y++<15?X=1:0)
        printf(X==Y?"%X\n":"%X ",X*Y);

    system("PAUSE");
}

