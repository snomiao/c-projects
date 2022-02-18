//ABCDEFG位移.c
//tcc_out=/build/ABCDEFG位移.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

// 更新记录
// # 2015/04/26 雪星(997596439@qq.com)
// 创建

int main(){
    unsigned int i, j, n, m;
    printf("请输入2个数 (行数, 每行字符数) : ");
    scanf("%d%d", &n, &m);
    for(j = 0; j != n; j++, printf("\n"))
        for(i = 0; i != m; i++) 
            printf("%c", 'A' + ((i - 2 * j + m) % m));
    system("pause");
}