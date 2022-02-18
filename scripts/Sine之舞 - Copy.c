//Sine之舞.c
//tcc_out=/build/Sine之舞.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//2015/04/06 雪星(997596439@qq.com)
//创建

//    题目
//　　A(n)=sin(1–sin(2+sin(3–sin(4+...sin(n))...)
//　　S(n)=(...(A1+n)A2+n-1)A3+...+2)An+1


#define uint unsigned int
#define BUFLEN 2048
char outT[BUFLEN];
char outA[BUFLEN];
char outS[BUFLEN];
int A(int n){
    for(int i = n; i > 0; --i){
        if(i == n)
            sprintf(outA, "sin(%d)", n);
        else{
            memcpy(outT, outA, BUFLEN);
            sprintf(outA, "sin(%d%s%s)", i, i % 2 ? "-" : "+", outT);
        }
    }
}
int S(int n){
    for(int i = 0; i < n; ++i){
        A(i+1); //Get An
        if(i==0){
            sprintf(outS, "%s+%d", outA, n-i); //A1+n-0
        }else{
            memcpy(outT, outS, BUFLEN);
            sprintf(outS, "(%s)%s+%d", outT, outA, n-i); //(%s)A2+n-1
        }
    }
}

int main(){
    //input
    unsigned int n;
    do{
        printf("输入，n < 201:\n");
        scanf("%d", &n);
    }while(n>200);

    printf("输入，n = %d:\n", n);

    char output[BUFLEN];
    printf("输出\n");
    S(n);
    memcpy(output, outS, BUFLEN);

    printf("%s\n", output);
    system("pause");
}