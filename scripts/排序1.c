//tcc_out=/build/排序1.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//排序1.c
// 更新
// # 2015/02/10 雪星(997596439@qq.com)
// 创建
// # 2015/04/12 雪星(997596439@qq.com)
// 加入归并排序，整理代码
///

////////////////////////////////////////////////////////////////
//#include "css/perfTicker.h"//
    //_
    //css/perfTicker.h
    #ifndef CSS_PERFTICK
    #define CSS_PERFTICK
    // 更新
    // # 2015/02/09 雪星(997596@gmail.com)
    // 创建
    // # 2015/02/14 雪星(997596@gmail.com)
    // 修改
    ///
    #include <windows.h>
    typedef      unsigned int uint;
    typedef long unsigned int uint64;
    uint64 perfFreq, perfCount;
    inline uint InitPerfTick(){//_
        return QueryPerformanceFrequency((void*)&perfFreq);
    }
    inline uint64 tick_count(){//_
        QueryPerformanceCounter((void*)&perfCount);
        return perfCount;
    }
    inline uint64 tick_ns(){//_
        QueryPerformanceCounter((void*)&perfCount);
        return perfCount * 1000 / (perfFreq / 1000000);
    }
    inline uint64 tick_us(){//_
        QueryPerformanceCounter((void*)&perfCount);
        return perfCount / (perfFreq / 1000000);
    }
    inline uint64 tick_ms(){//_
        QueryPerformanceCounter((void*)&perfCount);
        return perfCount / (perfFreq / 1000);
    }
    inline uint64 tick_s (){//_
        QueryPerformanceCounter((void*)&perfCount);
        return perfCount / (perfFreq);
    }
    inline uint64 tick_min(){//_
        QueryPerformanceCounter((void*)&perfCount);
        return perfCount / (perfFreq) / 60;
    }
    inline uint64 tick_hour(){//_
        QueryPerformanceCounter((void*)&perfCount);
        return perfCount / (perfFreq) / 3600;
    }
    #endif
////////////////////////////////////////////////////////////////
#define TIMECOUNT_T0(unit, ...)                                \
    printf("%-40.40s", ##__VA_ARGS__);                         \
    t0 = tick_##unit()                                          //_
#define TIMECOUNT_T1(unit)                                     \
    t1 = tick_##unit();                                        \
    printf("> %10d"#unit" \n", T = t1 - t0)                     //_
#define MAKE_ARRAY_ORDER_NORMAL(a, n)                          \
    for(uint i = 0    ; i < n  ; a[i] = i++)                    //_
#define MAKE_ARRAY_ORDER(a, n)                                 \
    for(uint i = n - 1; i != -1; a[i] = i--)                    //_
#define MAKE_ARRAY_REVERSE_NORMAL(a, n)                        \
    for(uint i = 0    ; i < n  ; a[i] = n - 1 - i++)            //_
#define MAKE_ARRAY_REVERSE(a, n)                               \
    for(uint i = n - 1; i != -1; a[i] = n - 1 - i--)            //_
#define MAKE_ARRAY_INTERMINGLE_BYTMP(a, n, seed)               \
    MAKE_ARRAY_ORDER(a, n);                                    \
    Intermingle_bytmp(a, n, seed)                               //_
#define SHOW_ARRAY(a, n)                                       \
    for(uint i = 0; i < n; printf("%8d\n", a[i++]))             //_
#define CHECK_SORT(a, n)                                       \
    PRINT_CHECK(Check_sort(a, n))                               //_
#define CHECK_SORT_REVERSE(a, n)                               \
    PRINT_CHECK(Check_sort_reverse(a, n))                       //_
#define PRINT_CHECK(check)                                     \
    if(!check) printf("FAILED!\n")                              //_
////////////////////////////////////////////////////////////////
#define SWAP_BYBIT(a, b) ((a) ^= (b) ^= (a) ^= (b))
#define SWAP_BYSUB(a, b) ((a) = -a + (b += a -= b))
inline void swap_bypointer(uint *a, uint *b){//_
    uint tmp = *a ; //FASTER
    *a        = *b ;
    *b        = tmp;
}
inline void swap_bybit    (uint *a, uint *b){//_
    *a ^= *b ^= *a ^= *b;
}
inline void swap_bysub    (uint *a, uint *b){//_
    //a = a - b  //== a - b
    //b = a + b  //== a - b + b == a
    //a = b - a  //== (b + a - b) - (a - b) == b
    *a = -*a + (*b += *a -= *b);
}
inline uint cmp_lt(uint a, uint b){//_
    return a <  b;
}
inline uint cmp_le(uint a, uint b){//_
    return a <= b;
}
inline uint cmp_eq(uint a, uint b){//_
    return a == b;
}
////////////////////////////////////////////////////////////////
uint Check_sort        (uint *a, uint n){//_
    for(uint i = n - 1; i != -1; i--)
        if(a[i] != i)
            return 0;
    return 1;
}
uint Check_sort_reverse(uint *a, uint n){//_
    for(uint i = n - 1; i != -1; i--)
        if(a[i] != n - i - 1)
            return 0;
    return 1;
}
////////////////////////////////////////////////////////////////
uint rand40000000H(uint seed){//_
    uint result;
    seed *= 1103515245;
    seed += 12345;
    result  = (uint) (seed / 65536) % 2048;
    seed *= 1103515245;
    seed += 12345;
    result <<= 9;
    result ^= (uint) (seed / 65536) % 1024;
    seed *= 1103515245;
    seed += 12345;
    result <<= 10;
    result ^= (uint) (seed / 65536) % 1024;
    return result;
}
void Intermingle_bytmp(uint *a, uint n, uint seed){//_
    for (uint i = 0; i < n; ++i){
        seed    = rand40000000H(seed);
        uint j = (seed % n);
        swap_bypointer(&a[i], &a[j]);
    }
}
void Intermingle_bybit(uint *a, uint n, uint seed){//_
    for (uint i = 0; i < n; ++i){
        seed    = rand40000000H(seed);
        uint j = (seed % n); //SLOWER
        //swap_bybit(&a[i], &a[j]);
        SWAP_BYBIT(a[i], a[j]);
    }
}
void Intermingle_bysub(uint *a, uint n, uint seed){//_
    for (uint i = 0; i < n; ++i){
        seed    = rand40000000H(seed);
        uint j = (seed % n); //SLOWER
        SWAP_BYSUB(a[i], a[j]);
    }
}
////////////////////////////////////////////////////////////////
void Sort_bubble              (uint *a, uint n){//_
    for(uint i = n - 1; i != 0; i--){
        if(cmp_lt(a[i], a[i - 1])){
            swap_bypointer(&a[i], &a[i - 1]);
            i = n;
        }
    }
}
////////////////////////////////////////////////////////////////
void Sort_insertion           (uint *a, uint n){//_
    for(uint i = 1, t, j; i < n; i++){
        t = a[i]; //uint 没有-1, 所以可以用j < n
        for(j = i - 1; j < n && cmp_lt(t, a[j]); j--)
            a[j + 1] = a[j]; //右移
        a[j + 1] = t; //插入
    }
}
////////////////////////////////////////////////////////////////
void Sort_quick               (uint *a, uint n){//_
    if(n <= 1) return;

    uint i, splitpos = 0, spliter = a[0];
    swap_bypointer(&a[0], &a[n-1]); //放到最后
    for(i = 0; i < n; ++i)
        if(cmp_lt(a[i], spliter))
            swap_bypointer(&a[i], &a[splitpos++]);
    swap_bypointer(&a[splitpos], &a[n-1]); //放回正确的位置

    Sort_quick(a, splitpos);
    Sort_quick(&(a[splitpos+1]), n - splitpos - 1);
}
////////////////////////////////////////////////////////////////
void Sort_quick_middle        (uint *a, uint n){//_
    if(n <= 1) return;

    uint i, pos = 0, pivot = a[n/2];  //中取主元
    swap_bypointer(&a[n/2], &a[n-1]); //主元后置
    for(i = 0; i != n - 1; ++i)       //小主置左
        if(cmp_lt(a[i], pivot)){
            if(i != pos)
                swap_bypointer(&a[i], &a[pos]);
            pos++;
        }
    swap_bypointer(&a[pos], &a[n-1]); //主元归中

    Sort_quick_middle(&a[0], pos);               //对主元左边排序
    Sort_quick_middle(&a[pos + 1], n - pos - 1); //对主元右边排序
}
////////////////////////////////////////////////////////////////
void Sort_quick_last          (uint *a, uint n){//_
    if(n <= 1) return;

    uint i, splitpos = 0, spliter = a[n-1];
    swap_bypointer(&a[n-1], &a[n-1]); //放到最后
    for(i = 0; i < n; ++i)
        if(cmp_lt(a[i], spliter))
            swap_bypointer(&a[i], &a[splitpos++]);
    swap_bypointer(&a[splitpos], &a[n-1]); //放回正确的位置

    Sort_quick_last(a, splitpos);
    Sort_quick_last(&(a[splitpos+1]), n - splitpos - 1);
}
////////////////////////////////////////////////////////////////
void Sort_selection           (uint *a, uint n){//_
    uint i, j, min, mini;
    for(i = 0; i < n; i++){
        min  = a[mini = i];
        for(j = i; j < n; j++)
            if(cmp_lt(a[j], min)) min = a[mini = j];
        if(mini != i) swap_bypointer(&a[mini], &a[i]);
    }
}
////////////////////////////////////////////////////////////////
void Sort_merge               (uint *a, uint n){//_
    if(n <= 1) return;
    uint *e = &a[0    ], d = n / 2,     //切出左边
         *r = &a[n / 2], f = n - n / 2; //切出右边
    Sort_merge(e, d); //对左边排序
    Sort_merge(r, f); //对右边排序
    //建个一样大的数组装结果
    uint *final = (uint*)calloc(n, sizeof(uint));
    uint pfinal = 0, c = 0, v = 0;
    //两边比较, 把较小的数装进结果
    while(c < d && v < f)
        final[pfinal++] = !cmp_lt(r[v], e[c]) ? e[c++] : r[v++];
    //把上一步剩下的数装进结果
    while(c < d) final[pfinal++] = e[c++];
    while(v < f) final[pfinal++] = r[v++];
    //结果写回原数组
    memcpy(a, final, n * sizeof(uint));
    free(final);
}
////////////////////////////////////////////////////////////////
void Sort_merge_nospace       (uint *a, uint n){//_
    if(n <= 1) return;
    Sort_merge_nospace(a, n / 2);             //对左边排序
    Sort_merge_nospace(a + n / 2, n - n / 2); //对右边排序
    uint p = n / 2, j = 0; //切成 3 半
    while((j < p) && (p < n)){ 
        if(cmp_lt(a[p], a[j])){ //后 2 半比较
            uint r = a[p];      //把较小数拿出
            for(uint i = p; i > j; i--)
                a[i] = a[i-1]; //右移 1 位, 给前半腾位置
            a[j] = r; //把较小数放左边
            p++;
        }
        j++;
    }
}
////////////////////////////////////////////////////////////////
void Sort_heap_print          (uint *a, uint n){//_
    uint i;
    printf("\n");
    for(i = 0; i < n; i++){
        printf("%3d ", a[i]);
        if((i+2 & (i+1)) == 0){
            printf("\n");
        }
    }
}
void sort_heap_max_heapify    (uint *a, uint n, uint i){//_
    uint l = i * 2 + 1, // l =>  left child // i =>  the parent
         r = i * 2 + 2, // r => right child // m =>    max item
         m = l < n && cmp_lt(a[i], a[l]) ? l : i; //左和父比
    if(r < n && cmp_lt(a[m], a[r])) m = r;        //再和右比, 选出最大节点
    if(m != i && swap_bypointer(&a[i], &a[m]))    //最大节点和父交换
        sort_heap_max_heapify(a, n, m);           //递归把小的节点也做相同处理
}
void Sort_heap                (uint *a, uint n){//_
    uint i;
    for(i = n / 2 - 1; i < n                                ; i--)
        sort_heap_max_heapify(a, n, i);
    for(i = n - 1    ; i < n && swap_bypointer(&a[0], &a[i]); i--)
        sort_heap_max_heapify(a, i, 0);
}
////////////////////////////////////////////////////////////////
uint SortTest(uint *copy, uint count){//_
    uint *array = (uint*)calloc(count, sizeof(uint));
    uint t0, t1, T;
    {
        memcpy(array, copy, count * sizeof(uint));
        TIMECOUNT_T0(us, "不排序，测试错误处理");

        TIMECOUNT_T1(us); CHECK_SORT(array, count);
    }
    if(count <= 8192){
        memcpy(array, copy, count * sizeof(uint));
        TIMECOUNT_T0(us, "冒泡排序，Sort_bubble");
        Sort_bubble(array, count);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);
    }
    if(count <= 64 * 1024){
        memcpy(array, copy, count * sizeof(uint));
        TIMECOUNT_T0(us, "插入排序，Sort_insertion");
        Sort_insertion(array, count);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        memcpy(array, copy, count * sizeof(uint));
        TIMECOUNT_T0(us, "选择排序，Sort_selection");
        Sort_selection(array, count);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        memcpy(array, copy, count * sizeof(uint));
        TIMECOUNT_T0(us, "前基快排，Sort_quick");
        Sort_quick(array, count);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        memcpy(array, copy, count * sizeof(uint));
        TIMECOUNT_T0(us, "后基快排，Sort_quick_last");
        Sort_quick_last(array, count);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);
    }
    if(count <= 1024 * 1024){
        memcpy(array, copy, count * sizeof(uint));
        TIMECOUNT_T0(us, "中基快排，Sort_quick_middle");
        Sort_quick_middle(array, count);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        memcpy(array, copy, count * sizeof(uint));
        TIMECOUNT_T0(us, "归并排序，Sort_merge");
        Sort_merge(array, count);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        memcpy(array, copy, count * sizeof(uint));
        TIMECOUNT_T0(us, "原地归并，Sort_merge_nospace");
        Sort_merge_nospace(array, count);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);
    }
    {
        memcpy(array, copy, count * sizeof(uint));
        TIMECOUNT_T0(us, "堆积排序，Sort_heap");
        Sort_heap(array, count);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);
    }
}
int main(){//_
    system("title 排序测试");
    InitPerfTick();

    //总体： quick < heap < insert < selection < bubble
    //       wow!    不错   还行     挺慢        巨慢

    //uint  count = (uint)16;                //在这个数量级内 Sort_insertion 最快
    uint  count = (uint)1024;              //16 ~ 262144 用 Sort_quick 都是极好的
    //uint count = (uint)30000;             //在这个点测试的数据比较好看
    //uint count = (uint)1000000;             //题目要求
    //uint  count = (uint)64 * 1024;         //到这里，Sort_insertion的时间已经不能忍
    //uint  count = (uint)256 * 1024;        //内存1M
    //uint  count = (uint)300 * 1024;        //以300K左右为界 Sort_heap 速度慢慢超过 Sort_quick
    //uint  count = (uint)256 * 1024 * 1024; //内存到了G级，只剩 Sort_heap 可以用了

    uint *array = (uint*)calloc(count, sizeof(uint));
    
    uint t0, t1, T;
    //计时精度和CPU有关，一般来说 3GHz 就能达到1微秒以下的精度，也就是纳秒级
    printf("测试规模：%d\n", count);

    TIMECOUNT_T0(us, "计时精度测试, 单位：microsecond");
    TIMECOUNT_T1(us);

    TIMECOUNT_T0(ns, "计时精度测试, 单位：nanosecond");
    TIMECOUNT_T1(ns);

    TIMECOUNT_T0(us, "生成顺序数组（普通）");
    MAKE_ARRAY_ORDER_NORMAL(array, count);
    TIMECOUNT_T1(us); CHECK_SORT(array, count);

    TIMECOUNT_T0(us, "生成顺序数组（算法优化）");
    MAKE_ARRAY_ORDER(array, count);
    TIMECOUNT_T1(us); CHECK_SORT(array, count);

    TIMECOUNT_T0(us, "生成逆序数组（算法优化）");
    MAKE_ARRAY_REVERSE(array, count);
    TIMECOUNT_T1(us); CHECK_SORT_REVERSE(array, count);

    TIMECOUNT_T0(us, "打乱，变量交换，Intermingle_bytmp");
    Intermingle_bytmp(array, count, 0);
    TIMECOUNT_T1(us);

    TIMECOUNT_T0(us, "打乱，异或交换，Intermingle_bybit");
    Intermingle_bybit(array, count, 0);
    TIMECOUNT_T1(us);

    TIMECOUNT_T0(us, "打乱，减法交换，Intermingle_bybit");
    Intermingle_bysub(array, count, 0);
    TIMECOUNT_T1(us);

    uint seed = 1;
    printf("\n乱序排序测试, 种子 = 0x%08X\n", seed);
    MAKE_ARRAY_INTERMINGLE_BYTMP(array, count, seed);
    SortTest(array, count);

    printf("\n顺序排序测试\n");
    MAKE_ARRAY_ORDER(array, count);
    SortTest(array, count);

    printf("\n逆序排序测试\n");
    MAKE_ARRAY_REVERSE(array, count);
    SortTest(array, count);

    //if(count <= 64)
    //    SHOW_ARRAY(array, count);
    system("pause");
    free(array);
}

//上次结果 2015-04-20
/*测试规模：1024{//_
计时精度测试, 单位：microsecond         >          0us
计时精度测试, 单位：nanosecond          >          0ns
生成顺序数组（普通）                    >          3us
生成顺序数组（算法优化）                >          2us
生成逆序数组（算法优化）                >          3us
打乱，变量交换，Intermingle_bytmp       >         31us
打乱，异或交换，Intermingle_bybit       >         30us
打乱，减法交换，Intermingle_bybit       >         30us

乱序排序测试, 种子 = 0x00000001
不排序，测试错误处理                    >          0us
FAILED!
冒泡排序，Sort_bubble                   >     691676us
插入排序，Sort_insertion                >       1825us
选择排序，Sort_selection                >       4424us
归并排序_原地，Sort_merge_nospace       >        871us
前基快速排序，Sort_quick                >        175us
后基快速排序，Sort_quick_last           >        187us
中基快速排序，Sort_quick_middle         >        165us
归并排序，Sort_merge                    >        548us
堆积排序，Sort_heap                     >        267us

顺序排序测试
不排序，测试错误处理                    >          0us
冒泡排序，Sort_bubble                   >          7us
插入排序，Sort_insertion                >         10us
选择排序，Sort_selection                >       3968us
归并排序_原地，Sort_merge_nospace       >         37us
前基快速排序，Sort_quick                >       3307us
后基快速排序，Sort_quick_last           >       5826us
中基快速排序，Sort_quick_middle         >         90us
归并排序，Sort_merge                    >        379us
堆积排序，Sort_heap                     >        225us

逆序排序测试
不排序，测试错误处理                    >          0us
FAILED!
冒泡排序，Sort_bubble                   >    1108304us
插入排序，Sort_insertion                >       3414us
选择排序，Sort_selection                >       3181us
归并排序_原地，Sort_merge_nospace       >       1627us
前基快速排序，Sort_quick                >       5088us
后基快速排序，Sort_quick_last           >       4472us
中基快速排序，Sort_quick_middle         >        111us
归并排序，Sort_merge                    >        331us
堆积排序，Sort_heap                     >        217us
请按任意键继续. . .
}*/
/*测试规模：30000{//_
计时精度测试, 单位：microsecond         >          0us
计时精度测试, 单位：nanosecond          >        333ns
生成顺序数组（普通）                    >         90us
生成顺序数组（算法优化）                >         90us
生成逆序数组（算法优化）                >         84us
打乱，变量交换，Intermingle_bytmp       >        932us
打乱，异或交换，Intermingle_bybit       >        884us
打乱，减法交换，Intermingle_bybit       >        892us

乱序排序测试, 种子 = 0x00000001
不排序，测试错误处理                    >          0us
FAILED!
插入排序，Sort_insertion                >    1381546us
选择排序，Sort_selection                >    2638198us
前基快速排序，Sort_quick                >       7814us
后基快速排序，Sort_quick_last           >       7070us
中基快速排序，Sort_quick_middle         >       6882us
归并排序，Sort_merge                    >      10944us
归并排序_原地，Sort_merge_nospace       >     615258us
堆积排序，Sort_heap                     >      13691us

顺序排序测试
不排序，测试错误处理                    >          0us
插入排序，Sort_insertion                >        222us
选择排序，Sort_selection                >    2643682us
前基快速排序，Sort_quick                >    2644572us
后基快速排序，Sort_quick_last           >    5201464us
中基快速排序，Sort_quick_middle         >       3617us
归并排序，Sort_merge                    >       7058us
归并排序_原地，Sort_merge_nospace       >       1883us
堆积排序，Sort_heap                     >       9657us

逆序排序测试
不排序，测试错误处理                    >          0us
FAILED!
插入排序，Sort_insertion                >    3017878us
选择排序，Sort_selection                >    2665279us
前基快速排序，Sort_quick                >    3737837us
后基快速排序，Sort_quick_last           >    3971120us
中基快速排序，Sort_quick_middle         >       4106us
归并排序，Sort_merge                    >       6853us
归并排序_原地，Sort_merge_nospace       >    1303325us
堆积排序，Sort_heap                     >       8958us
请按任意键继续. . .
}*/
/*测试规模：1000000{//_
计时精度测试, 单位：microsecond         >          0us
计时精度测试, 单位：nanosecond          >        334ns
生成顺序数组（普通）                    >       4112us
生成顺序数组（算法优化）                >       2751us
生成逆序数组（算法优化）                >       2924us
打乱，变量交换，Intermingle_bytmp       >      39324us
打乱，异或交换，Intermingle_bybit       >      38001us
打乱，减法交换，Intermingle_bybit       >      37253us

乱序排序测试, 种子 = 0x00000001
不排序，测试错误处理                    >          0us
AILED!
中基快速排序，Sort_quick_middle         >     269810us
归并排序，Sort_merge                    >     300162us
堆积排序，Sort_heap                     >     443762us

顺序排序测试
不排序，测试错误处理                    >          1us
中基快速排序，Sort_quick_middle         >     164324us
归并排序，Sort_merge                    >     258811us
堆积排序，Sort_heap                     >     449015us

逆序排序测试
不排序，测试错误处理                    >          0us
AILED!
中基快速排序，Sort_quick_middle         >     208494us
归并排序，Sort_merge                    >     255019us
堆积排序，Sort_heap                     >     438599us
请按任意键继续. . .
}*/
