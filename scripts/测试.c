//测试.c
//tcc_out=/build/测试.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//2015/02/13 雪星(997596439@qq.com)
//

#define uint unsigned int
#define PrintP(a)   printf("P:% 08p == %s\n", a, #a#)
#define PrintD(a)   printf("P:% 10d == %s\n", a, #a#)
#define PrintX(a)   printf("0x%08X == %s\n", a, #a#)
#define PrintL(a)   printf("%10.10s == %s\n", a?"true":"false", #a#)
#define PrintSep(a) printf("\n============================ %-60.60s\n", a)
int foo(){
    printf("hello, world\n");
    return 3;
}
int main(){
    PrintSep("类型大小");
    PrintD(sizeof(int));
    PrintD(sizeof(unsigned int));
    PrintD(sizeof(short));
    PrintD(sizeof(unsigned short));
    PrintD(sizeof(double));
    PrintD(sizeof(float));
    PrintD(sizeof(double*));
    PrintD(sizeof(char*));
    PrintD(sizeof(int*));
    PrintD((sizeof(int) * 8)-1);
    PrintD((sizeof(double) * 8)-1);
    
    PrintSep("位运算");
    PrintX(1<<(sizeof(int) * 8)-1);
    PrintX(1<<31);
    PrintX(1<<(-1));
    PrintX(1<<0);
    PrintX(-1>>0);
    PrintX((  signed int)-1>>((sizeof(int) * 8)-1));
    PrintX((unsigned int)-1>>((sizeof(int) * 8)-1));
    
    PrintSep("符号运算");
    PrintL(-1 > 2);
    PrintL((  signed    ) -1 > 2);
    PrintL((unsigned    ) -1 > 2);
    PrintL((  signed int) -1 > 2);
    PrintL((unsigned int) -1 > 2);
    PrintL((unsigned int) -2 > -4);
    PrintL((  signed int) -2 > -4);
    
    PrintSep("运算优先级");
    PrintD( 4 | 1      );
    PrintD( 55 % 50    );
    PrintD(!55 % 50);
    PrintD( 55 % 50 + 5);
    PrintD( 55 % 50 / 5);
    PrintD( 55 % 50 & 3);
    PrintD( 55 % 50 ^ 1);
    PrintD( 50 / 55 % 5);
    PrintD( foo());
    PrintD( 0 && foo());
    PrintD( 1 && foo());
    PrintD( 1 || foo());
    PrintD( foo() || foo());
    PrintD( foo() && foo());
    
    PrintSep("赋值");
    {
    int i = 1;
    PrintD( i );
    PrintD( i++ );
    PrintD( ++i );
    PrintD( i+=1 );
    PrintD( i*=1+1 );
    PrintD( i>>=1 );
    }
    
    PrintSep("指针");
    PrintP( "hello");
    PrintP( "hello");
    PrintP( "world"); 
    PrintP( "hello, world");

    PrintSep("数据格式");
    PrintP( "SONY");
    PrintP( "hello");
    PrintP( "world"); 
    PrintP( "hello, world");

    system("pause");
}