
#include "stdio.h"
#include "stdlib.h"
typedef unsigned int uint;
uint cmp_lt(uint len, char* a, char* b){ //a小于b返回true
    uint i;
    for(i=0;i<len;i++){
        if(*(a++) >= *(b++)){
            return 1;
        }
    }
    return 0;
}
void swap_bypointer(uint len, char* a, char* b){ //a小于b返回true
    uint i;
    char* c = (char*)malloc(len);
    memcpy(a, c, len);
    memcpy(b, a, len);
    memcpy(c, b, len);
}
void Sort_quick_middle(void *a, uint n, uint len, (void*)fCmp_Lt, (void*)fSwap){//_002.
    if(n <= 1) return;

    uint i, pos = 0;
    char* pivot = a[n/2];  //中取主元
    swap_bypointer(len, pivot, a[n-1]); //主元后置
    for(i = 0; i != n - 1; ++i)       //小主置左
        if(cmp_lt(len, a[i], pivot)){
            if(i != pos)
                swap_bypointer(len, a[i], a[pos]);
            pos++;
        }
    swap_bypointer(len, a[pos], a[n-1]); //主元归中

    Sort_quick_middle(&a[0], pos, len);               //对主元左边排序
    Sort_quick_middle(&a[pos + 1], n - pos - 1, len); //对主元右边排序
}
void main(){
    uint i,j,k;
    char a[5][20];
    for(i=0;i<5;i++)
        gets(a[i]);
    //Sort_quick_middle(a, 5, 20);
    for(i=0;i<5;i++)
        printf("%s\n", a[i]);
}