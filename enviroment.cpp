#include "enviroment.h"
#include "soundmanager.h"

Enviroment::Enviroment()
	:menu_select(0),
	menu_imgs(menus)
{
	menu_imgs[0].loadBMP("bmp/game.bmp");
	menu_imgs[0].setCutFrame(0,0,12,16);
	menu_imgs[1].loadBMP("bmp/power.bmp");
	menu_imgs[1].setCutFrame(0,0,12,16);

	//id_se = soundplayer->setSound("soundlib/wav/SE/hutuu.wav");

	menu_imgs[0].put(this->canvas,0,0);
	canvas->show();
	Delay_ms(3000);
	SoundManager::inst->Play(SoundManager::BGM_tfp);
}

Enviroment::~Enviroment()
{
}

void Enviroment::keyPressEvent(unsigned char keymap)
{
	switch (keymap)
	{
    case InputNum::btn_large:
		switch(menu_select)
		{
			case 0:
			SoundManager::inst->Play(SoundManager::SE_hutuu);
			canvas->clear();
			canvas->show();
			Game().Start();
			//canvas->clear();
			menu_imgs[0].put(this->canvas,0,0);
			canvas->show();
			break;
			case 1:
			End();
			break;
			default:
			break;
		}
        break;
    case InputNum::btn_smallA:  //赤
        break;
    case InputNum::btn_smallB:  //黄
        break;
    case InputNum::btn_smallC:  //青
        break;
    case InputNum::stk_up:

        break;
	case InputNum::stk_down:
		break;
	case InputNum::stk_right:
		if(menu_select < menus-1)
		{
			menu_select++;
			menu_imgs[menu_select].put(this->canvas,0,0);
			canvas->show();
		}
		//soundplayer->play((int)SoundName::SE_hutuu);
        SoundManager::inst->Play(SoundManager::SE_hutuu);
        break;
	case InputNum::stk_left:
		if(menu_select > 0)
		{
			menu_select--;
			menu_imgs[menu_select].put(this->canvas,0,0);
			canvas->show();
		}
		//soundplayer->play((int)SoundName::SE_hutuu);
        SoundManager::inst->Play(SoundManager::SE_hutuu);
        break;
    default:
        break;
    }
}

void Enviroment::keyReleaseEvent(unsigned char keymap)
{

}

void Enviroment::RoutineProc()
{

}
