// css/win.h


*WNDCLASSEX Win_CreateClass(FUNC Func1, char* ClassName)
{
    WNDCLASSEX wolfsprit_snowstar_form;
    wolfsprit_snowstar_form.cbClsExtra=0;                                     //32位窗口的附加数据，设为0
    wolfsprit_snowstar_form.cbSize=sizeof(WNDCLASSEX);                        //结构体大小
    wolfsprit_snowstar_form.cbWndExtra=0;                                     // 这是附加窗口数据，一般也不用
    wolfsprit_snowstar_form.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);//CreateSolidBrush……
    wolfsprit_snowstar_form.hCursor=LoadCursor(NULL,IDC_CROSS);               //这个是光标
    wolfsprit_snowstar_form.hIcon=LoadIcon(NULL,IDI_ERROR);                   //窗口图标
    wolfsprit_snowstar_form.hIconSm=NULL;                                     //窗口小图标
    wolfsprit_snowstar_form.hInstance=hInstance;                              //窗口实例 这个很重要
    wolfsprit_snowstar_form.lpfnWndProc=Func1;                                //窗口回调函数//这个一会在定义
    wolfsprit_snowstar_form.lpszClassName="myclass";
    wolfsprit_snowstar_form.lpszMenuName=NULL;                                //没有菜单，名字就不要了
    wolfsprit_snowstar_form.style=CS_HREDRAW | CS_VREDRAW;
    RegisterClassEx(&wolfsprit_snowstar_form);                                //这样一个窗口类就赋值完了 然后注册它
}