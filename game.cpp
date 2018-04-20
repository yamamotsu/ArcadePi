#include "matrixdisp/color.h"
#include "matrixdisp/palette.h"
#include "matrixdisp/matrixdisp.h"
#include "matrixdisp/virtualdisp.h"
#include "QBridge.h"
#include "gamesystem.h"
#include "game.h"

Game::Game()
{
        //ゲーム初期化時の処理
        qbridge = new Qbridge(canvas);
       // SoundManager::inst = new SoundManager();
       qbridge->Play(0);
}

Game::~Game(){
    delete qbridge;
}

//keyPressEvent
//何かしらのボタンが押されたときに呼ばれる処理
//case文の中にInputNum::～ を書くとそれに対応するボタンやスティックの
//入力判定をする．
/*
        //入力部品のナンバー対応は以下のとおり
	enum InputNum{
	    btn_large=1,  //ボタン大(メインボタン)
	    btn_smallA=2, //ボタン小A
	    btn_smallB=4, //B
	    btn_smallC=8, //C
	    stk_up=16,    //ジョイスティック↑
	    stk_down=32,  //ジョイスティック↓
	    stk_right=64, //→
	    stk_left=128  //←
	};
*/
void Game::keyPressEvent(unsigned char keymap){
        qbridge->OnButtonDown(keymap);

        switch (keymap) {
        case InputNum::btn_large:
            break;
        case InputNum::btn_smallA:  //赤
            qbridge->Play(0);
            break;
        case InputNum::btn_smallB:  //黄
            break;
        case InputNum::btn_smallC:  //青
        	End();
            break;
        case InputNum::stk_up:
            break;
        default:
            break;
        }
}


void Game::keyReleaseEvent(unsigned char keymap){

}

void Game::RoutineProc(){
        qbridge->Update();
}
