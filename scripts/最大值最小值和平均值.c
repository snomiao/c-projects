//最大值最小值和平均值.c
//tcc_out=/build/最大值最小值和平均值.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

/* 更新 V1.0.2
 * 2015/04/06 雪星(997596439@qq.com)
 * 创建
 */

//题目
//输入十个数，输出当中的最大值最小值和平均值，要求，最多定义五个变量。
//改题目
//输入好多数，输出当中的最大值最小值和平均值，要求，最多定义五个变量。

#define uint unsigned int

int main(){
    double max, min, ave, num;
    uint i = 0;
    printf("尽情地输入数字吧！（双精度）\n");
    scanf("%lf", &num);
    max = min = ave = num;
    while(1){
        printf(
            "最大值=%lf\n"
            "最小值=%lf\n"
            "平均值=%lf\n"
            ,max, min, ave
            );
        i++;
        scanf("%lf", &num);
        if(num>max)max=num;
        if(num<min)min=num;
        ave=(ave*i+num)/(i+1);
    }
}