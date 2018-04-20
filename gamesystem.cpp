#include <wiringPi.h>
#include <thread>
#include <mutex>
#include <iostream>
#include "matrixdisp/color.h"
#include "matrixdisp/palette.h"
#include "matrixdisp/matrixdisp.h"
#include "matrixdisp/virtualdisp.h"
#include "pinassign.h"
#include "menu.h"
#include "gamesystem.h"

using namespace std;


GameSystem::GameSystem()
{
    keymap = 0;
    //disp = new Matrixdisp();
    //canvas = new virtualDisp(disp);
    
    //メニュー関連の設定
    
    /*menuf = 0;
    
    menu->setCanvas(canvas);
    menu->setPageNum(3);
    
    menu->setPage("bmp/lv1.bmp");
    menu->setPage("bmp/lv2.bmp");
    menu->setPage("bmp/lv3.bmp");
    menu->show(0);
    */
    
    setup_pinmode_input();
    mtx = new mutex();
    endf = 0;
    deathf = 1;
    evstatus = EventNum::nothing;
    mslooptime=1;
    tick = -1;
    hnd = new thread(GameSystem::routine_start,this);
    
}

GameSystem::~GameSystem(){
    cout << "gamesystem shutdown..." << endl;
    mtx->lock();
    deathf = 1;
    mtx->unlock();
    hnd->join();
    

    cout << "thread closed." << endl;
    delete mtx;
    delete hnd;
    delete soundplayer;
    //delete menu;
    delete canvas;
}

SoundPlayer *GameSystem::soundplayer = new SoundPlayer();
//Menu *GameSystem::menu = new Menu();
virtualDisp *GameSystem::canvas = new virtualDisp();

char GameSystem::keycheck(){
    char temp=0;
    temp = temp|(digitalRead(PIN_BUTTON_LARGE));
    temp = temp|(digitalRead(PIN_BUTTON_SMALL1)<<1);
    temp = temp|(digitalRead(PIN_BUTTON_SMALL2)<<2);
    temp = temp|(digitalRead(PIN_BUTTON_SMALL3)<<3);
    temp = temp|(digitalRead(PIN_JOYSTICK_UP)<<4);
    temp = temp|(digitalRead(PIN_JOYSTICK_DOWN)<<5);
    temp = temp|(digitalRead(PIN_JOYSTICK_RIGHT)<<6);
    temp = temp|(digitalRead(PIN_JOYSTICK_LEFT)<<7);
    //cout << to_string(temp) << endl;
    if(temp){
        return temp;
    }
    return 0;
}


//void GameSystem::keyPressEvent(unsigned char keymap)=0;

//void GameSystem::keyReleaseEvent(unsigned char keymap)=0;

void GameSystem::Delay_us(int count){
    delayMicroseconds(count);
}

void GameSystem::Delay_ms(int count){
    delay(count);
}

void GameSystem::Start(){
    tick=0;
    while(!endf){
		
		EventDetector();
		RoutineProc();
		tick++;
		
		Delay_ms(mslooptime);
    }
    cout << "end" << endl;
}

void GameSystem::End(){
    endf=1;
}

//void GameSystem::RoutineProc()=0;

int GameSystem::getTick(){
    return tick;
}

void GameSystem::setLoopTime(int ms_looptime){
    mslooptime = ms_looptime;
}

bool GameSystem::isPress(char input_num){
    //int evtemp=0;
    char keytemp;
    mtx->lock();
    keytemp = keycheck();
    mtx->unlock();

    if(keytemp&input_num){
        return true;
    }
    return false;
}

bool GameSystem::EventDetector(){
    int evtemp,keytemp;
    mtx->lock();
    evtemp = evstatus;
    keytemp = keymap;
    mtx->unlock();

    switch(evtemp){
    case EventNum::nothing:
        return false;
        break;
    case EventNum::key_pressed:
		//if(menuf){
		//	cout << "menu mode" << endl;
		//	menu->keyDecode(keytemp);
		//	if(menu->isSelected()){
		//		keyPressEvent(keytemp);
		//		menuf = 0;
		//	}
		//}else{
		//	cout << "game mode" << endl;
			keyPressEvent(keytemp);
		//}
		cout << "key pressed" << to_string(keytemp) << endl;
        break;
    case EventNum::key_released:
		//if(menuf){
			//現在未実装
			
		//}else{
			keyReleaseEvent(keytemp);
		//}
        break;
    default:
        return false;
        break;
    }

    mtx->lock();
    evstatus = EventNum::nothing;
    mtx->unlock();
    return true;
}

void GameSystem::EventRoutine(){
	if(deathf){
	deathf=0;
    	unsigned char temp0=0,temp1,diff;
        cout << "routine started" << endl;
	while(1){
            mtx->lock();
            temp1 = keycheck();
            mtx->unlock();
            diff = temp1^temp0;
            //入力に変化があるか
            if(diff){
            	//押されたか離されたか
            	if(diff&temp1){
                    mtx->lock();
                    keymap = diff&temp1;
                    evstatus = EventNum::key_released;
                    mtx->unlock();
                    //keyPressEvent(diff&temp1);
            	}
            	if(diff&temp0){
                    mtx->lock();
                    keymap = diff&temp0;
                    evstatus = EventNum::key_pressed;
                    mtx->unlock();
                    //keyReleaseEvent(diff&temp0);
            	}
            }
	    
            
            mtx->lock();
            if(deathf){
                mtx->unlock();
                break;
            }
            mtx->unlock();
	    
			//チャタリング防止
            delay(50);
	    temp0 = temp1;
        }
    }
}

/*
void GameSystem::callMenu(){
	cout << "return Menu" << endl;
	menu->reset();
	//menu->show(0);
	menuf = 1;
}*/

void GameSystem::routine_start(GameSystem *ptr){
    ptr->EventRoutine();
}
