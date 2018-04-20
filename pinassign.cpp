#include <wiringPi.h>
#include "pinassign.h"



void setup_pinmode_disp(){
	
	pinMode(PIN_SERIALCLK,OUTPUT);
	pinMode(PIN_SERIALEN,OUTPUT);
	pinMode(PIN_SERIALS1,OUTPUT);
	pinMode(PIN_SERIALS2,OUTPUT);
	pinMode(PIN_ROWNUM_0,OUTPUT);
	pinMode(PIN_ROWNUM_1,OUTPUT);
	pinMode(PIN_ROWNUM_2,OUTPUT);
	pinMode(PIN_ROWNUM_3,OUTPUT);
	pinMode(PIN_ENABLE,OUTPUT);
	pinMode(PIN_RED,OUTPUT);
	pinMode(PIN_GREEN,OUTPUT);
	pinMode(PIN_BLUE,OUTPUT);
	
	pullUpDnControl(PIN_SERIALCLK,PUD_DOWN);
	pullUpDnControl(PIN_SERIALEN,PUD_DOWN);
	pullUpDnControl(PIN_SERIALS1,PUD_DOWN);
	pullUpDnControl(PIN_SERIALS2,PUD_DOWN);
	pullUpDnControl(PIN_ROWNUM_0,PUD_DOWN);
	pullUpDnControl(PIN_ROWNUM_1,PUD_DOWN);
	pullUpDnControl(PIN_ROWNUM_2,PUD_DOWN);
	pullUpDnControl(PIN_ROWNUM_3,PUD_DOWN);
	pullUpDnControl(PIN_ENABLE,PUD_DOWN);
	pullUpDnControl(PIN_RED,PUD_DOWN);
	pullUpDnControl(PIN_GREEN,PUD_DOWN);
	pullUpDnControl(PIN_BLUE,PUD_DOWN);
	
}

void setup_pinmode_input(){
    pinMode(PIN_JOYSTICK_UP,INPUT);
    pinMode(PIN_JOYSTICK_DOWN,INPUT);
    pinMode(PIN_JOYSTICK_RIGHT,INPUT);
    pinMode(PIN_JOYSTICK_LEFT,INPUT);
    pinMode(PIN_BUTTON_LARGE,INPUT);
    pinMode(PIN_BUTTON_SMALL1,INPUT);
    pinMode(PIN_BUTTON_SMALL2,INPUT);
    pinMode(PIN_BUTTON_SMALL3,INPUT);
    
    pullUpDnControl(PIN_JOYSTICK_UP,PUD_UP);
    pullUpDnControl(PIN_JOYSTICK_DOWN,PUD_UP);
    pullUpDnControl(PIN_JOYSTICK_RIGHT,PUD_UP);
    pullUpDnControl(PIN_JOYSTICK_LEFT,PUD_UP);
    pullUpDnControl(PIN_BUTTON_LARGE,PUD_UP);
    pullUpDnControl(PIN_BUTTON_SMALL1,PUD_UP);
    pullUpDnControl(PIN_BUTTON_SMALL2,PUD_UP);
    pullUpDnControl(PIN_BUTTON_SMALL3,PUD_UP);
    
}

