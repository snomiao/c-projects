//tcc_out_BAK=E:/TEST/2015420/src/css/求高精度幂.exe
//tcc_out=D:\L\tcc\build\求高精度幂.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//<求高精度幂.input

// 求高精度幂.c
// 更新
// # 2015/04/20 雪星(997596439@qq.com)
// 创建
///
//题目 http://poj.org/problem?id=1001&lang=zh-CN&change=true
//未完成
typedef unsigned int uint;
typedef unsigned char byte;

char*INPUT =
"95.123 12\n"
"0.4321 20\n"
"5.1234 15\n"
"6.7592  9\n"
"98.999 10\n"
"1.0100 12\n";


#define DEBUGF(...) printf(__VA_ARGS__)
void csAdding(char*a, char*b, uint la, uint lb){
    
}

int main(){//_
    char *s = (char*)malloc(6);
    uint p, n;
    uint i;
    while(sscanf(INPUT, "%s%d",s,&n)==2){
        INPUT+=10;
        DEBUGF("======================================\n");
        ////////////////////////////////////////////////////////////////
        //get p
        p = 0;
        for(i = 0; i < 6; ++i)
        {
            if(s[i] == '.' && i < 5)
            {
                s[i] = s[i + 1];
                s[i + 1] = '.';
                p++;
            }
        }
        s[5] = '\0';
        DEBUGF("%se%d  pow %d\n", s, p, n);
        ////////////////////////////////////////////////////////////////
        //get a
        unsigned char *a = (unsigned char*)calloc(5 * n, sizeof(unsigned char));
        //DEBUGF("p=%d\n", p);
        for(i = 0; i < 5; i++)
            a[i] = s[4-i] - '0';
        for(i = 0; i < 5; i++)
            s[i] = a[i];
        for(i = 5-1; i != -1; i--)
            DEBUGF("%d", s[i]);
        DEBUGF(" * ");
        for(i = 5 * n - 1; i != -1; i--)
            DEBUGF("%d", a[i]);
        DEBUGF("\n");
        ////////////////////////////////////////////////////////////////
        for(i = 0; i < n; ++i){
            uint x, y, z;
            for(y = 0; y < 5; ++y){
                for(x = 0; x < 5 * n; ++x){
                    a[x] *= s[y]
                    z = 
                }
            }
        }

    }
    system("pause");
}

//548815620517731830194541899025343415715973535967221869852721  60 = 12 * 5 = #s * n
//                        899025343415715973535967221869852721  36 = 12 * 3 =  p * n