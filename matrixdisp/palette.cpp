#include "color.h"
#include "palette.h"


Palette::Palette()
{
    red.setColor(1,0,0);       //赤
    green.setColor(0,1,0);     //緑
    blue.setColor(0,0,1);      //青
    yellow.setColor(1,1,0);    //黄
    aqua.setColor(0,1,1);      //水色
    purple.setColor(1,0,1);    //紫
    white.setColor(1,1,1);     //白
    black.setColor(0,0,0);     //黒
	
	colorset[0] = red;
	colorset[1] = green;
	colorset[2] = blue;
	colorset[3] = yellow;
	colorset[4] = aqua;
	colorset[5] = purple;
    colorset[6] = white;
    colorset[7] = black;
}

