//tcc_out=E:\TEST\2015420\src\css2\众数查找.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//众数查找v2.c
// 更新
// # 2015/04/21 雪星(997596439@qq.com)
// 创建
///
typedef unsigned int uint;
#define Dot(a, b) a##_WILL_BE_##b
#define FALSE 0
#define TRUE 1
#define PATH_I "众数查找.in"
#define PATH_O "众数查找.out"
#include <stdio.h>
int readNumber(char**str){//_
    uint n   = 0;
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
int main(){
    char*str, *fre;
    /*输入 O(n)*/{//_
        FILE*filei = fopen(PATH_I, "rb");
        fseek(filei , 0 , SEEK_END);
        uint len = ftell(filei);
        rewind(filei);

        str = fre = (char*)malloc(len + 1 * sizeof(1));
        fread(str,1,len,filei);
        fclose(filei);
        str[len] = '\0';
    }
    ////////////////////////////////////////////////////////////////
    uint i;
    uint n     = readNumber(&str);
    uint*arr   = (uint*)malloc(sizeof(uint)*n);
    uint min, max;
    /*读数据 O(n)*/{//_
        min = max = arr[n - 1] = readNumber(&str);
        for(i = n - 2; i != -1; i--){
            arr[i] = readNumber(&str);
            if(arr[i] < min) min = arr[i];
            if(max < arr[i]) max = arr[i];
        }
        free(fre);
    }
    ////////////////////////////////////////////////////////////////
    uint z, m = 0;
    //max = min + (max - min) / 2;
    /*统计 O(n) */{//_
        uint*ks    = (uint*)calloc(sizeof(uint), max - min + 1);
        for(i = n - 1; i != -1; i--)
            ks[arr[i] - min]++;
        for(i = max - min + 1 - 1; i != -1 ; i--){ //O(1)
            if (m <= ks[i]){
                m  = ks[i];
                z  = i + min;
            }
        }
        free(ks);
        free(arr);
    }
    ////////////////////////////////////////////////////////////////
    /*输出 O(1) */{//_
        FILE*fileo = fopen(PATH_O,"wb");
        fprintf(fileo, "%d %d", z, m);
        fclose(fileo);
    }
}