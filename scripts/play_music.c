//play_music.c
//tcc_out=/build/play_music.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=

//2015/04/06 雪星(997596439@qq.com)
//创建

//    题目
//　　A(n)=sin(1–sin(2+sin(3–sin(4+...sin(n))...)
//　　S(n)=(...(A1+n)A2+n-1)A3+...+2)An+1


#include <stdio.h>

void play_music(char *filename) /*filename为音乐文件名格式见上*/
{
FILE *fp;
int rate;
char sound_high[3];
float sound_long;
register int i=0,j;
int sign=0;
float str[1000][2];
if ((fp=fopen(filename,"r"))==NULL)
{
printf("Open file music.doc Errors!\n");
exit(1);
}
fscanf(fp,"%d",&rate);
while(!feof(fp)&&!sign)
{
fscanf(fp,"%s%f",&sound_high,&sound_long);
str[i][1]=rate*sound_long;
switch(sound_high[0])
{
case 'h':
switch(sound_high[1])
{
case '1':
str[i++][0]=1046.5;
break;
case '2':
str[i++][0]=1174.7;
break;
case '3':
str[i++][0]=1318.5;
break;
case '4':
str[i++][0]=1396.9;
break;
case '5':
str[i++][0]=1568;
break;
case '6':
str[i++][0]=1760;
break;
case '7':
str[i++][0]=1975.5;
break;
default: printf("\n Error Music.doc\n");
break;
}
break;
case 'm':
switch(sound_high[1])
{
case '1':
str[i++][0]=523.3;
break;
case '2':
str[i++][0]=587.3;
break;
case '3':
str[i++][0]=659.3;
break;
case '4':
str[i++][0]=698.5;
break;
case '5':
str[i++][0]=784.0;
break;
case '6':
str[i++][0]=880;
break;
case '7':
str[i++][0]=987.8;
break;
default: printf("\n Error music.doc.\n");
break;
}
break;
case 'l':
switch(sound_high[1])
{
case '1':
str[i++][0]=262;
break;
case '2':
str[i++][0]=296;
break;
case '3':
str[i++][0]=329.6;
break;
case '4':
str[i++][0]=349.2;
break;
case '5':
str[i++][0]=392;
break;
case '6':
str[i++][0]=440;
break;
case '7':
str[i++][0]=493.9;
break;
default: printf("\n Error music.doc.\n");
break;
}
break;
case '*':
switch(sound_high[1])
{
case '1':
str[i++][0]=131;
break;
case '2':
str[i++][0]=147;
break;
case '3':
str[i++][0]=165;
break;
case '4':
str[i++][0]=176;
break;
case '5':
str[i++][0]=196;
break;
case '6':
str[i++][0]=220;
break;
case '7':
str[i++][0]=247;
break;
default: printf("\n Error music.doc\n");
break;
}
break;
case '#':
if (sound_high[1]=='#') sign=1;
break;
case 'x':
if (sound_high[1]=='0') str[i++][0]=20;
break;
default:printf("\n ERRor music.doc\n");
exit(1);
}
}
for(j=0;j<=i-1;j++)
{
sound(str[j][0]);
delay(str[j][1]);
}
nosound();
}

