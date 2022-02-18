//tcc_out=/build/连续排序测试.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//连续排序测试.c
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
    printf("> %10u"#unit" \n", T = t1 - t0)                     //_
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
    for(uint i = 0; i < n; printf("%8d\n", a[i++]));            //_
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
void Sort_insertion_reverse   (uint *a, uint n){//_
    for(uint i = n - 1, t, j; i != 0; i--){
        t = a[i];
        for(j = i - 1; j < n && cmp_lt(t, a[j]); j--)
            a[j + 1] = a[j]; //右移
        a[j + 1] = t; //插入
    }
}
void Sort_insertion_onlylast  (uint *a, uint n){//_
    int t = a[n-1], j;
    for(j = n - 2; j < n && cmp_lt(t, a[j]); j--)
        a[j + 1] = a[j]; //右移
    a[j + 1] = t; //插入
}
////////////////////////////////////////////////////////////////
uint Sort_quick_spliter       (uint *a, uint n){//_
    uint i, splitpos = 0, spliter = a[0];
    swap_bypointer(&a[0], &a[n-1]); //放到最后
    for(i = 0; i < n; ++i)
        if(cmp_lt(a[i], spliter))
            swap_bypointer(&a[i], &a[splitpos++]);
    swap_bypointer(&a[splitpos], &a[n-1]); //放回正确的位置
    return splitpos;
}
void Sort_quick               (uint *a, uint n){//_
    if(n <= 1) return;
    uint splitpos = Sort_quick_spliter(a, n);
    Sort_quick(a, splitpos);
    Sort_quick(&(a[splitpos+1]), n - splitpos - 1);
}
////////////////////////////////////////////////////////////////
uint Sort_quick_middle_spliter(uint *a, uint n){//_
    uint i, splitpos = 0, spliter = a[n/2];
    swap_bypointer(&a[n/2], &a[n-1]); //放到最后
    for(i = 0; i < n; ++i)
        if(cmp_lt(a[i], spliter))
            swap_bypointer(&a[i], &a[splitpos++]);
    swap_bypointer(&a[splitpos], &a[n-1]); //放回正确的位置
    return splitpos;
}
void Sort_quick_middle        (uint *a, uint n){//_
    if(n <= 1) return;
    uint splitpos = Sort_quick_middle_spliter(a, n);
    Sort_quick_middle(&a[0], splitpos);
    Sort_quick_middle(&a[splitpos+1], n - splitpos - 1);
}
////////////////////////////////////////////////////////////////
uint Sort_quick_last_spliter  (uint *a, uint n){//_
    uint i, splitpos = 0, spliter = a[n-1];
    swap_bypointer(&a[n-1], &a[n-1]); //放到最后
    for(i = 0; i < n; ++i)
        if(cmp_lt(a[i], spliter))
            swap_bypointer(&a[i], &a[splitpos++]);
    swap_bypointer(&a[splitpos], &a[n-1]); //放回正确的位置
    return splitpos;
}
void Sort_quick_last          (uint *a, uint n){//_
    if(n <= 1) return;
    uint splitpos = Sort_quick_last_spliter(a, n);
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
void Sort_merge               (uint *a, uint n);
uint*Sort_merge_merge         (uint *e, uint d, uint *r, uint f){//_
    Sort_merge(e, d); Sort_merge(r, f);
    uint *final = (uint*)calloc(d + f, sizeof(uint));
    uint pfinal = 0, c = 0, v = 0;
    while(c < d && v < f)
        final[pfinal++] = !cmp_lt(r[v], e[c]) ? e[c++] : r[v++];
    while(c < d) final[pfinal++] = e[c++];
    while(v < f) final[pfinal++] = r[v++];
    return final;
}
void Sort_merge               (uint *a, uint n){//_
    if(n < 2) return;
    uint *final = Sort_merge_merge(&a[0], n / 2, &a[n / 2], n - n / 2);
    memcpy(a, final, n * sizeof(uint));
    free(final);
}
////////////////////////////////////////////////////////////////
void Sort_merge_nospace_merge (uint *a, uint n){//_
    uint p = n / 2, j = 0;
    while((j < p) && (p < n)){
        if(cmp_lt(a[p], a[j])){
            uint r = a[p];
            for(uint i = p; i > j; i--)
                a[i] = a[i-1]; //右移1位
            a[j] = r;
            p++;
        }
        j++;
    }
}
void Sort_merge_nospace       (uint *a, uint n){//_
    if(n>=2){
        Sort_merge_nospace(a, n / 2);
        Sort_merge_nospace(a + n / 2, n - n / 2);
        Sort_merge_nospace_merge(a, n);
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
         m = l < n && cmp_lt(a[i], a[l]) ? l : i;
    if(r < n && cmp_lt(a[m], a[r])) m = r; 
    if(m != i && swap_bypointer(&a[i], &a[m]))
        sort_heap_max_heapify(a, n, m);
    return;         // 尾递归
}
void Sort_heap                (uint *a, uint n){//_
    uint i;
    for(i = n / 2 - 1; i < n                                ; i--)
        sort_heap_max_heapify(a, n, i);
    for(i = n - 1    ; i < n && swap_bypointer(&a[0], &a[i]); i--)
        sort_heap_max_heapify(a, i, 0);
}
////////////////////////////////////////////////////////////////
uint SortTestContinuity(uint *copy, uint count){//_
    uint *array = (uint*)calloc(count, sizeof(uint));
    uint t0, t1, T;
    {
        memset(array, 0x00, count * sizeof(uint));
        TIMECOUNT_T0(us, "不排序，测试错误处理");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            ;
        TIMECOUNT_T1(us); CHECK_SORT(array, count);
    }
    if(count <= 8192){
        TIMECOUNT_T0(us, "冒泡排序，Sort_bubble");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            Sort_bubble(array, j + 1);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        TIMECOUNT_T0(us, "选择排序，Sort_selection");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            Sort_selection(array, j + 1);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        TIMECOUNT_T0(us, "前基快速排序，Sort_quick");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            Sort_quick(array, j + 1);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        TIMECOUNT_T0(us, "后基快速排序，Sort_quick_last");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            Sort_quick_last(array, j + 1);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

    }
    if(count <= 64 * 1024){
        TIMECOUNT_T0(us, "插入排序，Sort_insertion");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            Sort_insertion(array, j + 1);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        TIMECOUNT_T0(us, "后插排序，Sort_insertion_reverse");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            Sort_insertion_reverse(array, j + 1);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        TIMECOUNT_T0(us, "连续后插排序，Sort_insertion_onlylast");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            Sort_insertion_onlylast(array, j + 1);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);
    }
    if(count <= 1024 * 1024){
        TIMECOUNT_T0(us, "中基快速排序，Sort_quick_middle");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            Sort_quick_middle(array, j + 1);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        TIMECOUNT_T0(us, "归并排序，Sort_merge");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            Sort_merge(array, j + 1);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);

        TIMECOUNT_T0(us, "归并排序_原地，Sort_merge_nospace");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            Sort_merge_nospace(array, j + 1);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);
    }
    {
        TIMECOUNT_T0(us, "堆积排序，Sort_heap");
        for(uint j = 0; j < count && ((array[j] = copy[j]) || 1); j++)
            Sort_heap(array, j + 1);
        TIMECOUNT_T1(us); CHECK_SORT(array, count);
    }
}
int main(){//_
    system("title 排序测试");
    InitPerfTick();

    //总体： quick < heap < insert < selection < bubble
    //       wow!    不错   还行     挺慢        巨慢

    //uint  count = (uint)16;                //在这个数量级内 Sort_insertion 最快
    uint  count = (uint)1024;                //16 ~ 262144 用 Sort_quick 都是极好的
    //uint  count = (uint)30000;              //在这个点测试的数据比较好看
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

    uint seed = 1;
    printf("\n乱序连续排序测试, 种子 = 0x%08X\n", seed);
    MAKE_ARRAY_INTERMINGLE_BYTMP(array, count, seed);
    SortTestContinuity(array, count);

    printf("\n顺序连续排序测试\n");
    MAKE_ARRAY_ORDER(array, count);
    SortTestContinuity(array, count);

    printf("\n逆序连续排序测试\n");
    MAKE_ARRAY_REVERSE(array, count);
    SortTestContinuity(array, count);

    system("pause");
    free(array);
}
//上次结果 2015-04-20
/*测试规模：1024{//_
计时精度测试, 单位：microsecond         >          0us
计时精度测试, 单位：nanosecond          >          0ns

乱序连续排序测试, 种子 = 0x00000001
不排序，测试错误处理                    >          3us
FAILED!
冒泡排序，Sort_bubble                   >     379793us
选择排序，Sort_selection                >    1185058us
前基快速排序，Sort_quick                >     859925us
后基快速排序，Sort_quick_last           >     979243us
插入排序，Sort_insertion                >       5825us
后插排序，Sort_insertion_reverse        >       5508us
连续后插排序，Sort_insertion_onlylast   >       1588us
中基快速排序，Sort_quick_middle         >      46105us
归并排序，Sort_merge                    >     410990us
归并排序_原地，Sort_merge_nospace       >      20270us
堆积排序，Sort_heap                     >     120714us

顺序连续排序测试
不排序，测试错误处理                    >          3us
冒泡排序，Sort_bubble                   >       3165us
选择排序，Sort_selection                >    1125907us
前基快速排序，Sort_quick                >    1038712us
后基快速排序，Sort_quick_last           >    1937699us
插入排序，Sort_insertion                >       4029us
后插排序，Sort_insertion_reverse        >       3954us
连续后插排序，Sort_insertion_onlylast   >         12us
中基快速排序，Sort_quick_middle         >      42866us
归并排序，Sort_merge                    >     407060us
归并排序_原地，Sort_merge_nospace       >      18220us
堆积排序，Sort_heap                     >     106068us

逆序连续排序测试
不排序，测试错误处理                    >          3us
FAILED!
冒泡排序，Sort_bubble                   >    1104939us
选择排序，Sort_selection                >    1183208us
前基快速排序，Sort_quick                >     522189us
后基快速排序，Sort_quick_last           >     933653us
插入排序，Sort_insertion                >       8850us
后插排序，Sort_insertion_reverse        >       7483us
连续后插排序，Sort_insertion_onlylast   >       3136us
中基快速排序，Sort_quick_middle         >      48323us
归并排序，Sort_merge                    >     406271us
归并排序_原地，Sort_merge_nospace       >      19394us
堆积排序，Sort_heap                     >     107247us
请按任意键继续. . .
}*/