//找出1000以内所有完数.c
//tcc_out=/build/找出1000以内所有完数.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//2015/04/06 雪星(997596439@qq.com)
//

#define uint unsigned int

int main(){
    uint a, b;
    a = 120;
    b = 18440;
    printf("%d %d\n", a, b);
    
    a=a-b;
    b=b+a;
    a=b-a;

    b = b + a - b;
    a = b + a - a;


    printf("%d %d\n", a, b);

    system("pause");
}