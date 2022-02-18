//css/perfTicker.h
// 更新
// # 2015/02/09 雪星(997596@gmail.com)
// 创建
// # 2015/02/14 雪星(997596@gmail.com)
// 修改
///
#ifndef CSS_PERFTICK
#define CSS_PERFTICK
#include <windows.h>
typedef      unsigned int uint;
typedef long unsigned int uint64;
uint64 perfFreq, perfCount;
inline uint InitPerfTick(){
    return QueryPerformanceFrequency((void*)&perfFreq);
}
inline uint64 tick_count(){
    QueryPerformanceCounter((void*)&perfCount);
    return perfCount;
}
inline uint64 tick_ns(){
    QueryPerformanceCounter((void*)&perfCount);
    return perfCount * 1000 / (perfFreq / 1000000);
}
inline uint64 tick_us(){
    QueryPerformanceCounter((void*)&perfCount);
    return perfCount / (perfFreq / 1000000);
}
inline uint64 tick_ms(){
    QueryPerformanceCounter((void*)&perfCount);
    return perfCount / (perfFreq / 1000);
}
inline uint64 tick_s (){
    QueryPerformanceCounter((void*)&perfCount);
    return perfCount / (perfFreq);
}
inline uint64 tick_min(){
    QueryPerformanceCounter((void*)&perfCount);
    return perfCount / (perfFreq) / 60;
}
inline uint64 tick_hour(){
    QueryPerformanceCounter((void*)&perfCount);
    return perfCount / (perfFreq) / 3600;
}
#endif