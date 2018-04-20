#include "color.h"
#include "matrixdisp.h"
#include "virtualdisp.h"
#include <iostream>
#include <mutex>

using namespace std;

virtualDisp::virtualDisp(Matrixdisp *ptrdisp)
{
	int i,j;
	for(i=0;i<12;i++){
		for(j=0;j<16;j++){
			pixel[i][j] = Color(0,0,0);
		}
	}
	
	internal_created_flag = 0;
    ptr = ptrdisp;
}

virtualDisp::virtualDisp(){
	int i,j;
	for(i=0;i<12;i++){
		for(j=0;j<16;j++){
			pixel[i][j] = Color(0,0,0);
		}
	}
	
	ptr = new Matrixdisp();
	internal_created_flag = 1;
}

virtualDisp::~virtualDisp(){
	if(internal_created_flag){
		delete ptr;
	}
}

void virtualDisp::show(){
    int i,j;
    
    #ifdef _DISPLAY_DEBUG_COMMENT_
	//debug
	string debug("");
	for(j=0;j<16;j++){
		for(i=0;i<12;i++){
					debug += to_string(pixel[i][j].getElement(0)|pixel[i][j].getElement(1)|pixel[i][j].getElement(2)) + ",";	
		}
		debug += "\n";
	}
	cout << debug << endl;
	//debug end
	#endif //_DISPLAY_DEBUG_COMMENT_
	
	for(i=0;i<12;i++){
		ptr->mtx->lock();
		for(j=0;j<16;j++){
			ptr->dot[i][j] = pixel[i][j];
		}
		ptr->mtx->unlock();
	}
    
}

void virtualDisp::clear(){
    int i,j;
    //mtx->lock();
    for(i=0;i<12;i++){
        for(j=0;j<16;j++){
            pixel[i][j] = Color(0,0,0);
        }
    }
    //mtx->unlock();
}

int virtualDisp::drawRect(int x0, int y0, int width, int height,Color &color){
    int x,y;
    if(x0>=0&&x0<12&&y0>=0&&y0<16&&width>0&&width<=(12-x0)&&height>0&&height<=(16-y0)){
        //mtx->lock();
        for(x=0;x<width;x++){
            pixel[x+x0][y0] = color;
            pixel[x+x0][y0+height-1] = color;
        }
        for(y=0;y<height;y++){
            pixel[x0][y+y0] = color;
            pixel[x0+width-1][y+y0] = color;
        }
        //mtx->unlock();
    }else{
        return 0;
    }
    return 1;
}

int virtualDisp::fillRect(int x0, int y0, int width, int height, Color &color){
    int x,y;
    if(x0>=0&&x0<12&&y0>=0&&y0<16&&width>0&&width<=(12-x0)&&height>0&&height<=(16-y0)){
        //mtx->lock();
        for(x=0;x<width;x++){
            for(y=0;y<height;y++){
                pixel[x+x0][y+y0] = color;
            }
        }
        //mtx->unlock();
    }else{
        return 0;
    }
    return 1;
}

int virtualDisp::drawPoint(int x, int y, Color &color){
    if(x>=0&&x<12&&y>=0&&y<16){
        //mtx->lock();
        pixel[x][y] = color;
        //mtx->unlock();
    }else{
        return 0;
    }
    return 1;
}

int virtualDisp::drawVerticalLine(int x, int y0, int y1, Color &color){
    int y;
    if(x>=0&&x<12&&y0>=0&&y0<16&&y1>0&&y1<16&&y0<=y1){
        //mtx->lock();
        for(y=0;y<=y1-y0;y++){
            pixel[x][y+y0]=color;
        }
        //mtx->unlock();
    }else{
        return 0;
    }
    return 1;
}

int virtualDisp::drawHorizontalLine(int y, int x0, int x1, Color &color){
    int x;
    if((y>=0)&&(y<16)&&(x0>=0)&&(x0<12)&&(x1>0)&&(x1<12)&&(x0<=x1)){
        //mtx->lock();
        for(x=0;x<=x1-x0;x++){
            pixel[x+x0][y]=color;
        }
        //mtx->unlock();
    }else{
        return 0;
    }
    return 1;
}
