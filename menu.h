#ifndef MENU_H
#define MENU_H

#include <string>

//#include "gamesystem.h"
#include "matrixdisp/virtualdisp.h"
#include "matrixdisp/bmpcontainer.h"

using namespace std;

typedef struct tagMenuInfo{
	int page;
	BmpContainer *bmp;
	int internal_created_flag;
} MenuInfo;


class Menu{
	private:
		int selected_f;
		int page;
		int pagenum;
		//Gamesystem *sys;
		virtualDisp *canvas;
		MenuInfo *info;
	public:
		Menu();
		Menu(int pagenum,virtualDisp *canvas);
		~Menu();
		void keyDecode(int keymap);
		void show(int page);
		
		void setCanvas(virtualDisp *canvas);
		void setPageNum(int pagenum);
		void setPage(int page,BmpContainer *bmp);
		void setPage(BmpContainer *bmp);
		void setPage(int page,const char *bmp_filename);
		void setPage(const char *bmp_filename);
		
		int isSelected();
		void reset();
};

#endif
