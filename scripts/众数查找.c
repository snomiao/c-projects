//tcc_out=/build/众数查找/众数查找_旧.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//众数查找.c
// 更新
// # 2015/04/19 雪星(997596439@qq.com)
// 创建
///
typedef unsigned int uint;
#define FALSE 0
#define TRUE 1
inline void swap_bypointer(uint *a, uint *b){//_
    uint tmp = *a ; //FASTER
    *a       = *b ;
    *b       = tmp;
}
inline uint cmp_lt(uint a, uint b){//_
    return a <  b;
}

uint Sort_quick_middle_spliter(uint *a, uint n){//_
    uint i, splitpos = 0, spliter = a[n/2];
    swap_bypointer(&a[n/2], &a[n-1]); //放到最后
    for(i = 0; i < n; ++i)
        if(cmp_lt(a[i], spliter))
            swap_bypointer(&a[i], &a[splitpos++]);
    swap_bypointer(&a[splitpos], &a[n-1]); //放回正确的位置
    return splitpos;
}
void Sort_quick_middle        (uint *a, uint n){//_
    if(n <= 1) return;
    uint splitpos = Sort_quick_middle_spliter(a, n);
    Sort_quick_middle(&a[0], splitpos);
    Sort_quick_middle(&a[splitpos+1], n - splitpos - 1);
}
int readNumber(char**str){
    uint n = 0;
    uint ret = FALSE;
    do{
        char c = *(*str)++;
        switch(c){
            case ' ':
            case '\r':
            case '\n':
                if(ret)
                    return n;
                break;
            case '\0':
                return n;
            default:
                n *= 10;
                n += c - '0';
                ret = TRUE;
        }
    }while(1);
}

#define PATH_I "众数查找.in"
#define PATH_O "众数查找.out"
#include <stdio.h>
int main(){//_
    //system("title 众数测试");
    ////////////////////////////////////////////////////////////////
    FILE*filei = fopen(PATH_I, "rb");
    fseek(filei , 0 , SEEK_END);
    uint len = ftell(filei);
    rewind(filei);

    char*str = (char*)malloc(len + 1 * sizeof(1));
    fread(str,1,len,filei);
    fclose(filei);
    str[len] = '\0';
    ////////////////////////////////////////////////////////////////
    uint i;
    uint n     = readNumber(&str);
    uint*arr   = (uint*)malloc(sizeof(uint)*n);
    for(i = 0; i < n; i++){      //O(n)
        arr[i] = readNumber(&str);    //读数据 O(1)
    }
    Sort_quick_middle(arr, n); // n log n
    ////////////////////////////////////////////////////////////////
    uint c = 0, z = 0, p = 0, m = 0;
    for(i = 0; i < n; i++){//找众数 O(n)
        if(arr[p] != arr[i]){
            if(cmp_lt(m, i - p)){
                z = arr[p];
                m = i - p;
            }
            p = i;
        }
        if(i == n - 1){
            if(cmp_lt(m, i + 1 - p)){
                z = arr[p];
                m = i + 1 - p;
            }
            p = i;
        }
    }
    //for(i = 0; i < n; i++)   printf("%d\n", arr[i]);
    //printf("%d %d\n", z, m); system("pause");

    free(arr);
    free(str);
    FILE*fileo = fopen(PATH_O,"wb");
    fprintf(fileo, "%d %d", z, m);
    fclose(fileo);
}