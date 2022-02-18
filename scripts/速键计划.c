//速键计划.c
//tcc_out=/build/速键计划/FastKey.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

// 更新记录
// # 2015/04/26 雪星(997596439@qq.com)
// 创建

//keyName 按键码

/* 更新:
 * v0.1.0.0
 * 创建: 2015.8.7 雪星( 997596@gmail.com )
 */

/*
GetKeyCode = function(scanName){
    return _lsScanCode[scanName]
}
GetKeyCodeLeft = function(scanName){
    return assert(_lsScanCode[scanName]) & ~128
}
GetKeyCodeRight = function(scanName){
    var c = _lsScanCode[scanName]
    return assert(c) | (_lsScanName[c] ? 128 : 0)
}
GetKeyName = function(scanCode){
    return _lsScanName[scanCode]
}
GetKeyNameFlags = function(scanCode, flags = 0){
    return _lsScanName[scanCode | (flags & 1 ) << 7]
}
GetKeyNameLeft = function(scanCode){
    return _lsScanName[scanCode & ~128]
}
GetKeyNameRight = function(scanCode){
    return _lsScanName[scanCode | 128] : lsCodeToName[scanCode]
}
*/
char* *keyName;
int   *keyCode;

char* *mbName;
int   *mbCode;
//void ReadKeyLine(char* line){
//
//}
//void ReadConfig(){
//    if(FILE *fp = fopen("KeyName.cfg", "r")){
//        char buf[1024];
//        while(fread(buf, 1, sizeof(buf), fp))
//            v.insert(v.end(), buf, buf + len);
//        fclose(fp);
//    }else{
//        exit(0);
//    }
//}
int main(){
    //system("chcp 65001");
    printf("中文 GBK\n");
    printf(L"中文 GBK\n");

    system("pause");
}

/*
lsMBCode = {
    ["{LMB}" ] = 1 ;
    ["{RMB}" ] = 2 ;
    ["{MMB}" ] = 3 ;
    ["{XMB1}"] = 4 ;
    ["{XMB2}"] = 5 ;
    ["{MWU}" ] = 8 ;
    ["{MWD}" ] = 9 ;
    ["{HWL}" ] = 16;
    ["{HWR}" ] = 17;
}
_lsMBName = {
    [1 ] = "{LMB}" ;
    [2 ] = "{RMB}" ;
    [3 ] = "{MMB}" ;
    [4 ] = "{XMB1}";
    [5 ] = "{XMB2}";
    [8 ] = "{MWU}" ;
    [9 ] = "{MWD}" ;
    [16] = "{HWL}" ;
    [17] = "{HWR}" ;
}
*/
/*
GetKeyCode = function(scanName){
    return _lsScanCode[scanName]
}
GetKeyCodeLeft = function(scanName){
    return assert(_lsScanCode[scanName]) & ~128
}
GetKeyCodeRight = function(scanName){
    var c = _lsScanCode[scanName]
    return assert(c) | (_lsScanName[c] ? 128 : 0)
}
GetKeyName = function(scanCode){
    return _lsScanName[scanCode]
}
GetKeyNameFlags = function(scanCode, flags = 0){
    return _lsScanName[scanCode | (flags & 1 ) << 7]
}
GetKeyNameLeft = function(scanCode){
    return _lsScanName[scanCode & ~128]
}
GetKeyNameRight = function(scanCode){
    return _lsScanName[scanCode | 128] : lsCodeToName[scanCode]
}
*/

/**intellisense(css)
keyName                   = 按键码转换库, 注意此库的按键名和key库不通用
end intellisense**/
/**intellisense(css.keyName)
_lsScanName               = 表 [scancode] = scanName
_lsScanCode               = 表 [scanName] = scanCode
_lsMBtnName               = 表 [mBtnCode] = mBtnName
_lsMBtnCode               = 表 [mBtnName] = mBtnCode
GetKeyCode(keyName)       = 传入 keyName  返回 scancode \n//可以区分小键盘回车
GetKeyCodeLeft(keyName)   = 传入 keyName  返回 scancode \n//非扩展键
GetKeyCodeRight(keyName)  = 传入 keyName  返回 scancode \n//扩展键
GetKeyName(scancode)      = 传入 scancode 返回 keyName  \n//可以区分小键盘回车
GetKeyNameLeft(scancode)  = 传入 scancode 返回 keyName  \n//非扩展键
GetKeyNameRight(scancode) = 传入 scancode 返回 keyName  \n//扩展键
GetKeyNameFlags(scancode, flags) = 传入 scancode, flags  返回 keyName  \n//flags为proc的参数
end intellisense**/
/*}}*/

