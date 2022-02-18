//求质数.c
//tcc_out=/build/求质数.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=
//version 0.13.0

//2015/02/14 雪星(997596@gmail.com)   Primes_1
//2015/02/15 雪星(997596@gmail.com)   Primes_2
//
#include "css/perfTicker.h"
#include "css/typedef.h"

// 整数开平方，返回开方下取整的数
// 用二分法逼近
 DWORD intSqrt(DWORD n) {
    DWORD x, y = n;
    if (!n) return 0;
    do{
        x = y;
        y = (x + n / x) >> 1;
    }while (y < x);
    return x;
}
float kamake_sqr(float number) {     
    long i;     
    float x, y;     
    const float f = 1.5F;     
    x = number * 0.5F;     
    y = number;     
    i = *(long *) &y;     
    i = 0x5f3759df - (i>> 1);     
    y = *(float *) &i;     
    y = y * (f - (x * y * y));     
    y = y * (f - (x * y * y));     
    return number * y;     
}

void Primes_2(DWORD *a, DWORD n){
    DWORD i, j;
    DWORD max = intSqrt(n);
    memset(a, 0xFF, n * sizeof(DWORD));
    a[0] = 0;a[1] = 0;
    for(i = 2; i < max; i++){
        for(j = 2; i * j < n; j++){
            a[i * j] = 0;
        }
    }
}
void Primes_1(DWORD *a, DWORD n){
    DWORD i, j;
    memset(a, 0x00, n * sizeof(DWORD));
    for(i = 2; i < n; i++){
        a[i] = 1;
        for(j = 2; j <= intSqrt(i); j++){
            if( (i % j) == 0 ){
                a[i] = 0;
            }
        }
    }
}
int main(){
    system("title 求质数 ");
    InitPerfTick();
    DWORD t1, t2, T;
    DWORD  count = 2048;
    //DWORD  count = 256*1024;
    DWORD *array = (DWORD*)malloc(count * sizeof(DWORD));
    
    DWORD check;

    Primes_1(array, count);

    DWORD i;
    if(count<=2048){
        for(i = 0; i < count; i++){
            if( array[i] ){
                printf("%u ", i);
            }
        }
    }
    printf("\n");
    Primes_2(array, count);

    if(count<=2048){
        for(i = 0; i < count; i++){
            if( array[i] ){
                printf("%u ", i);
            }
        }
    }
    printf("\n");
    system("pause");
}