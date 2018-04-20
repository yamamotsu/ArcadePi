#ifndef ENVIROMENT_H
#define ENVIROMENT_H
#include <iostream>
#include "gamesystem.h"
#include "game.h"
#include "matrixdisp/bmpcontainer.h"
//#include "QBridge.h"

class Enviroment: public GameSystem
{
private:
	
	//ここに使用したい変数を追加していく
	int menu_select;
	const int menus = 2;
	//BmpContainer menu_imgs[2];
	std::vector<BmpContainer> menu_imgs;
	//BmpContainer menuimg;
	//キー押下時に呼ばれるイベント
    void keyPressEvent(unsigned char keymap);
    //キーを離したときに呼ばれるイベント
    void keyReleaseEvent(unsigned char keymap);
    //一定時間ごとに呼ばれるイベント
    void RoutineProc();
    
    int id_se;
public:
	Enviroment();
	~Enviroment();
};

#endif		//ENVIROMENT_H
