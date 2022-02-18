// css/console.h
// 更新
// # 2015/02/05 雪星(997596@gmail.com)
// 创建
///
#include <stdio.h>
#include <io.h>
#include <fcntl.h> // control

inline HANDLE io_open()
{
    AllocConsole();
    *stdout = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT), "w");
    *stdin  = *_fdopen(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE ),_O_TEXT), "r");
    return GetStdHandle(STD_OUTPUT_HANDLE);
}
inline void   io_close()
{
    FreeConsole();
}