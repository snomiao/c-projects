//tcc_out=/build/井字棋和五子棋.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//井字棋和五子棋.c
//2015/02/13 雪星(997596439@qq.com)
//创建


#include "css/typedef.h"

#define MAX_PLAYER (DWORD)9
BYTE *pad_item; //pad_size*pad_size
DWORD pad_size;
DWORD rule_len;
DWORD c_player;
DWORD switcher;

void AskPushItem(){
    DWORD x = 0, y = 0;
    if(pad_size==3){
        char *mapNumPad = "789456123";
        printf("%s (789456123)\n", "请按小键盘落子: ");
        while((--x) >= pad_size * pad_size || pad_item[mapNumPad[x] - '1']){
            x = getch() - '0';
        }
        pad_item[mapNumPad[x] - '1'] = switcher;
    }else{
        printf("%s (1~%d 1~%d)\n", "请输入落子坐标 x y: ", pad_size, pad_size);
        while((--x)>=pad_size || (--y)>=pad_size || pad_item[pad_size * y + x]){
            scanf("%u %u", &x, &y);
        }
        pad_item[pad_size * y + x] = switcher;
    }
}
DWORD Winner(){
    DWORD x, y, clen;
    for(y = 0; y < pad_size - rule_len + 1; y++)
    for(x = 0; x < pad_size - rule_len + 1; x++){
        //*     //
        //  *   //
        //    * //
        for(clen = 0;  pad_item[pad_size * (y + clen    ) + (x + clen    )]
                    == pad_item[pad_size * (y + clen + 1) + (x + clen + 1)]
                    && clen + 1 < rule_len;  clen++);
        if((clen + 1 >= rule_len) && pad_item[pad_size * y + x])
            return pad_item[pad_size * y + x];
        //    * //
        //  *   //
        //*     //
        for(clen = 0;  pad_item[pad_size * (y + clen    ) + (x + rule_len - 1 - clen    )]
                    == pad_item[pad_size * (y + clen + 1) + (x + rule_len - 1 - clen - 1)]
                    && clen + 1 < rule_len;  clen++);
        if((clen + 1 >= rule_len) && pad_item[pad_size * y + (x + rule_len - 1)])
            return pad_item[pad_size * y + (x + rule_len - 1)];
    }
    //  *   //
    //  *   //
    //  *   //
    for(y = 0; y < pad_size - rule_len + 1; y++)
    for(x = 0; x < pad_size               ; x++){
        for(clen = 0;  pad_item[pad_size * (y + clen    ) + (x           )]
                    == pad_item[pad_size * (y + clen + 1) + (x           )]
                    && clen + 1 < rule_len;  clen++);
        if((clen + 1 >= rule_len) && pad_item[pad_size * y + x])
            return pad_item[pad_size * y + x];
    }
    //      //
    //* * * //
    //      //
    for(y = 0; y < pad_size               ; y++)
    for(x = 0; x < pad_size - rule_len + 1; x++){
        for(clen = 0;  pad_item[pad_size * (y           ) + (x + clen    )]
                    == pad_item[pad_size * (y           ) + (x + clen + 1)]
                    && clen + 1 < rule_len;  clen++);
        if((clen + 1 >= rule_len) && pad_item[pad_size * y + x])
            return pad_item[pad_size * y + x];
    }
    //? ? ?
    //? ? ?
    //? ? ?
    for(clen = 0; clen < pad_size * pad_size && pad_item[clen]; clen++);
    if( clen == pad_size * pad_size) return -1;
    return 0;
}
DWORD SwitchPlayer(){
    return switcher < c_player ? ++switcher : (switcher = 1);
}
char GetPlayer(DWORD playerid){
    char* players = "_XO*&%#@$!";
    return players[playerid];
}
void DrawPad(){
    system("cls");
    printf("  ");
    for(DWORD x = 0; x < pad_size; x++)
        printf("%2d", x+1);
    printf("\n");
    for(DWORD y = 0; y < pad_size; y++){
        printf("%2d", y+1);
        for(DWORD x = 0; x < pad_size; x++){
            char ch = pad_item[pad_size * y + x];
            printf(" %c", GetPlayer(ch));
        }
        printf("\n");
    }
    printf("%d\n", rule_len);
}
int main(){
    printf("%s", "请输入棋盘边长( 43以下 如有更高，请正确设置控制台大小 ): "); scanf("%u", &pad_size);
    rule_len = pad_size < 5 ? pad_size : 5;
    pad_item = (BYTE*)calloc(pad_size * pad_size, sizeof(BYTE));

    if(pad_size>12){
        do{
            printf("%s", "请输入游戏人数(  9以下 ): ");
            scanf("%u", &c_player);
        }while(c_player - 1 >= MAX_PLAYER);
    }else{
        c_player = 2; printf("\n");
    }
    switcher = MAX_PLAYER;

    switch(rule_len){
        case  3: system("title 井字棋"); break;
        case  5: system("title 五子棋"); break;
        default:{
            char title[256] = "title %d子棋";
            sprintf(title, title, rule_len);
            system(title);
        }
    }
    DWORD winner;
    while(!(winner = Winner())){
        DrawPad();
        SwitchPlayer();
        printf("当前玩家：%c\n", GetPlayer(switcher));
        AskPushItem();
    }
    DrawPad();
    if(winner == -1){
        printf("平局！\n");
    }else{
        printf("本局获胜玩家是：%c！\n", GetPlayer(winner));
        for(int i = 0; i < 10; i++){
            sleep(500);
            printf("%c", GetPlayer(winner));
            printf("%c", GetPlayer(winner));
            printf("%c", GetPlayer(winner));
            printf("%c", GetPlayer(winner));
            printf("%c", GetPlayer(winner));
            sleep(500);
            printf("！\n");
        }
    }
    getch();
    //system("pause");
}