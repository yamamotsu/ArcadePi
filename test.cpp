#include <wiringPi.h>
#include "matrixdisp/color.h"
#include "matrixdisp/palette.h"
#include "matrixdisp/matrixdisp.h"
#include "matrixdisp/virtualdisp.h"
#include <iostream>
using namespace std;
int main(void){
	int i,j,k,loop=0;
	Matrixdisp *disp = new Matrixdisp();
	virtualDisp *canvas = new virtualDisp(disp);
	
	Color color;
	k=0;
	color = palette->blue;
	
	
		
	while(1){
		
		canvas->clear();
		
		canvas->drawPoint(loop%12,loop%12,palette->red);
		
		canvas->show();
		delay(1000);
		
		loop++;
		if(loop==32){
			break;
		}
		
	}
	
	delete canvas;
	delete disp;
	return 0;
	
}
