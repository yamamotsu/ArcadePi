#include "matrixdisp/virtualdisp.h"
#include "matrixdisp/bmpcontainer.h"
#include "gamesystem.h"

#include "menu.h"

Menu::Menu(){
	page=0;
	selected_f = 0;
	
}

Menu::Menu(int pagenum,virtualDisp *canvas){
	page=0;
	this->canvas = canvas;
	this->pagenum = pagenum;
	info = new MenuInfo[pagenum];
	selected_f = 0;
	
	int i;
	
	for(i=0;i<pagenum;i++){
		info[i].page = -1;
		info[i].bmp = nullptr;
		info[i].internal_created_flag = 0;
	}
}

void Menu::setCanvas(virtualDisp *canvas){
	this->canvas = canvas;
}

void Menu::setPageNum(int pagenum){
	this->pagenum = pagenum;
	info = new MenuInfo[pagenum];
	int i;
	for(i=0;i<pagenum;i++){
		info[i].page = -1;
		info[i].bmp = nullptr;
		info[i].internal_created_flag = 0;
	}
}

void Menu::keyDecode(int keymap){
	switch(keymap){
		case InputNum::stk_right:
			if(page<(pagenum-1)){
				page++;
				show(page);
			}
			GameSystem::soundplayer->replay(2);
		break;
		case InputNum::stk_left:
			if(page>0){
				page--;
				show(page);
			}
			GameSystem::soundplayer->replay(2);
			break;
		case InputNum::btn_large:
			cout << "level selected" << endl;
			selected_f = 1;
			break;
		default:
		break;
	}
	
}

void Menu::show(int page){
	canvas->clear();
	info[page].bmp->put(0,0);
	canvas->show();
}

Menu::~Menu(){
	int i;
	for(i=0;i<pagenum;i++){
		if(info[i].internal_created_flag){
			delete info[i].bmp;
		}
	}
	delete info;
}

void Menu::setPage(int page,const char *bmp_filename){
	if(info[page].page==-1){
		return;
	}
	
	info[page].page = page;
	info[page].bmp = new BmpContainer(bmp_filename,canvas);
	info[page].internal_created_flag = 1;
	
	info[page].bmp->setCutFrame(0,0,12,16);
}

void Menu::setPage(const char *bmp_filename){
	int i;
	for(i=0;info[i].page != -1&&i < pagenum;i++);
	if(i==pagenum)
		return;
	
	info[i].page = i;
	info[i].bmp = new BmpContainer(bmp_filename,canvas);
	info[i].internal_created_flag = 1;
	
	info[i].bmp->setCutFrame(0,0,12,16);
}

void Menu::setPage(BmpContainer *bmp){
}

void Menu::setPage(int page,BmpContainer *bmp){
}

int Menu::isSelected(){
	return selected_f;
}

void Menu::reset(){
	page=0;
	selected_f = 0;
	show(0);
}


