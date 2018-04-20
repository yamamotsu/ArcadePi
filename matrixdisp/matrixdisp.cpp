#include <wiringPi.h>
#include <iostream>

#include <thread>
#include <mutex>
#include "color.h"
#include "palette.h"
#include "../pinassign.h"
//#include "pwmdriver.h"

#include "matrixdisp.h"


using namespace std;


void routine_start(Matrixdisp *ptr)
{
    ptr->routine();
}


Matrixdisp::Matrixdisp()
{
    endf=0;
	wiringPiSetupPhys();
	setup_pinmode_disp();
        mtx = new mutex;
        hnd = new thread(routine_start,this);
}

Matrixdisp::~Matrixdisp()
{
	mtx->lock();
	endf=0;
	mtx->unlock();
    hnd->detach();

	digitalWrite(PIN_RED,0);
	digitalWrite(PIN_BLUE,0);
	digitalWrite(PIN_GREEN,0);
	digitalWrite(PIN_SERIALEN,0);
	digitalWrite(PIN_ENABLE,1);
    delete hnd;
    delete mtx;
}

void Matrixdisp::serialout(int drawpins)
{
	int i;
	for(i=0;i<8;i++)
	{
            digitalWrite(PIN_SERIALS1,(drawpins>>i)&1);
            digitalWrite(PIN_SERIALS2,(drawpins>>(8+i))&1);
            digitalWrite(PIN_SERIALCLK,1);
            //5V動作のとき500ns以上待つ必要があるので一応(74HC595の仕様)
            delayMicroseconds(1);
            digitalWrite(PIN_SERIALCLK,0);
	}
}

void Matrixdisp::display_routine(){
	int drawpins;
	int i,j,stat=0;
	int dtime;
	//同時にdotの中身が変わらないように排他処理
    
	for(stat=0;stat<3;stat++){
		switch(stat){
		case 0:
			digitalWrite(PIN_RED,1);
			digitalWrite(PIN_GREEN,0);
			digitalWrite(PIN_BLUE,0);
			//色ごとに輝度が違うので遅延時間を調整する
                        dtime=90;
			break;
		case 1:
			digitalWrite(PIN_RED,0);
			digitalWrite(PIN_GREEN,1);
			digitalWrite(PIN_BLUE,0);
                        dtime=200;
			break;
		case 2:
			digitalWrite(PIN_RED,0);
			digitalWrite(PIN_GREEN,0);
			digitalWrite(PIN_BLUE,1);
						dtime=180;
			break;
		}
		
		for(i=0;i<12;i++){
            drawpins=0;
        	mtx->lock();            
		    for(j=0;j<16;j++){
				if(dot[11-i][j].getElement(stat)){
					drawpins |= (1<<j);
				}
            }
		    mtx->unlock();  			
				digitalWrite(PIN_SERIALEN,0);
				serialout(drawpins);


				digitalWrite(PIN_ENABLE,1);		//現在の描画を消去

				digitalWrite(PIN_SERIALEN,1);
				
				digitalWrite(PIN_ROWNUM_0,i&1);
				digitalWrite(PIN_ROWNUM_1,i&2);
				digitalWrite(PIN_ROWNUM_2,i&4);
				digitalWrite(PIN_ROWNUM_3,i&8);
				
				digitalWrite(PIN_ENABLE,0);		//描画
				delayMicroseconds(dtime);
               }
			delayMicroseconds(500);
        }
}

int Matrixdisp::write(int x,int y,const Color &color)
{
	
	if(x>=12&&x<0){
		return -1;
	}
	if(y>=16&&y<0){
		return -1;
	}
	mtx->lock();
	dot[x][y] = color;
	mtx->unlock();
	return 0;
}

int Matrixdisp::write_rowline(int x,const Color &color,int y0,int y1){
	int i;
	
	if(x>=12&&x<0){
		return -1;
	}
	
	if(y1>=16&&y1<0){
		return -1;
	}
	
	if(y0>=16&&y0<0){
		return -1;
	}
	
	if(y1<=y0){
		return -1;
	}
	
	mtx->lock();
	for(i=0;i<(y1-y0);i++){
		dot[x][i+y0] = color;
	}
	mtx->unlock();
	
	return 0;
}

void Matrixdisp::clear()
{
	int i,j;
	
	mtx->lock();
	for(i=0;i<12;i++){
		for(j=0;j<16;j++){
        	dot[i][j] = palette->black;
		}
	}
	mtx->unlock();
	
}

void Matrixdisp::routine(void)
{
        //仕様上routineは公開メンバ関数なので
        //最初の一度しか呼べないように排他処理する
        mtx->lock();
        if(!endf){
            mtx->unlock();
            endf=1;
            while(1){
                this->display_routine();
                
                mtx->lock();
                if(endf==0){
                    mtx->unlock();
                    this->clear();
			this->display_routine();
			digitalWrite(PIN_ENABLE,1);		//現在の描画を消去
                    break;
                }
                mtx->unlock();
            
            }
        }else{
            mtx->unlock();
        }
	
}
