//tcc_out=/build/逆序.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//逆序.c
//2015/02/10 雪星(997596@gmail.com)
//

int main(){
    printf("输入任意长度字符串：");
    char *s = (char*)calloc(65536, sizeof(char));
    scanf("%s", s);
    printf("倒序\n");
    int i;
    for(i = 0; s[i]; i++); //把p指到\0
    for(i--  ; i>=0; i--)  //往前打印
        printf("%c", s[i]);
    printf("\n");
    system("pause");
}