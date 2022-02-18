//tcc_out=/build/斐波那契数列.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//斐波那契数列.c
//2015/02/09 雪星(997596@gmail.com)
//完成！

//理想输出
//0 1 1 2 3 5 8 13 21 34 ...



int Array(int c){
    int *p = (int*)malloc((c+2)*sizeof(int));
    c = (int)((int)p + c*sizeof(int));
    *(((int*)c)--) = 0;
    *(((int*)c)  ) = 1;
    while(((int*)c)-- >= p){
        printf("%d ",  ((int*)c)[2]);
        ((int*)c)[0] = ((int*)c)[1] + ((int*)c)[2];
    }
    free(c);
}
int Recursive(int c, int a, int b){
    if(0>=c) return 0;
    printf("%d ", a);
    a = a + b;
    Recursive(--c, b, a);
}
int Loop(int c){
    int a=0, b=1;
    while(1){
        if(c--<=0) break;
        printf("%d ", a);
        if(c--<=0) break;
        printf("%d ", b);
        a+=b; b+=a;
    }
}
int main(){
    int c = 0;
    system("title 斐波那契数列");
    printf("请输入数量\n");
    scanf("%d",&c);
    
    Loop(c);
    printf("\n");
    Recursive(c, 0, 1);
    printf("\n");
    Array(c);
    printf("\n");
    system("PAUSE");
}

