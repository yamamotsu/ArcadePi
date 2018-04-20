#ifndef QBRIDGE_H
#define QBRIDGE_H

#include <vector>
#include <iostream>
#include "matrixdisp/matrixdisp.h"
#include "matrixdisp/virtualdisp.h"
#include "matrixdisp/palette.h"
#include "matrixdisp/color.h"
#include "soundlib/soundplayer.h"
#include "soundlib/wavecontainer.h"
#include "gamesystem.h"
#include "game.h"

#include "soundmanager.h"

using namespace std;

const static struct tagBarSpeedLevel
{
	int slow = 30;
	int normal =  15;
	int fast = 0;
} BarSpeedLevel;
/*
//==========================================================
//--------------------- SoundManager -----------------------
//==========================================================

class SoundManager
{
private:
    //vector<WaveContainer*> sounds;
    SoundPlayer *soundPlayer;

public:
    enum SoundName
    {
        BGM_game = 0,
        BGM_tfp,
        SE_stop,
        SE_move,
        SE_miss,
        SE_cut,
        SE_fanfare,
        SE_hayai,
        SE_hutuu,
        SE_osoi
    };
    SoundManager();
    ~SoundManager();
    static SoundManager *inst;
    void Play(SoundName name);
    void Play(SoundName name, bool loop);
    void PlayOverWrite(SoundName name);
    void Stop(SoundName name);
    void Pause(SoundName name);
};

SoundManager *SoundManager::inst = NULL;

SoundManager::SoundManager()
{
    //soundPlayer = new SoundPlayer();
    soundPlayer = GameSystem::soundplayer;
    cout << "SoundID:" << to_string(soundPlayer->setSound("soundlib/wav/BGM/game.wav")) << endl;
    soundPlayer->setSound("soundlib/wav/BGM/bgm_tfp.wav");
    soundPlayer->setSound("soundlib/wav/SE/enter.wav");
    soundPlayer->setSound("soundlib/wav/SE/move.wav");
    soundPlayer->setSound("soundlib/wav/SE/miss.wav");
    soundPlayer->setSound("soundlib/wav/SE/cut.wav");
    soundPlayer->setSound("soundlib/wav/SE/fanfare.wav");
    soundPlayer->setSound("soundlib/wav/SE/hayai.wav");
    soundPlayer->setSound("soundlib/wav/SE/hutuu.wav");
    soundPlayer->setSound("soundlib/wav/SE/osoi.wav");
}

SoundManager::~SoundManager()
{
    //int i;
    //for(i = 0; i < (int)sounds.size(); i++)
    //    delete sounds[i];
}


void SoundManager::Play(SoundName name)
{
    soundPlayer->play((int)name);
}

void SoundManager::Play(SoundName name, bool loop)
{
    soundPlayer->play((int)name, loop);
}

void SoundManager::Stop(SoundName name)
{
    soundPlayer->stop((int)name);
}

void SoundManager::PlayOverWrite(SoundName name)
{
    Stop(name);
    Play(name);
}

void SoundManager::Pause(SoundName name)
{
    soundPlayer->pause((int)name);
}
*/

//==========================================================
//------------------------ Rect ----------------------------
//==========================================================
class Rect
{
private:
    void InitEdgeLength(int x, int y, int height, int width);
    void InitDiagonalPoint(int x0, int y0, int x1, int y1);

public:
    int x;      //X座標
    int y;      //Y座標
    int width;  //横幅
    int height; //高さ

    int x0();   //(x0,y0)    (x1,y0)
    int y0();   //　　□□□□□□□□□
    int x1();   //　　□□□□□□□□□
    int y1();   //(x0,y1)　　　　(x1,y1)

    Rect();
    Rect(int x, int y, int width, int height);
    Rect(int x, int y, int a, int b, bool useEdgeLength);
    Rect Trim();    //描画範囲から飛び出した分をカット
    Rect Cut(Rect effectiveRect);     //有効範囲内をカット
};

Rect::Rect(){}

Rect::Rect(int x, int y, int width, int height)
{
    InitEdgeLength(x,y,width,height);
}

Rect::Rect(int x, int y, int a, int b, bool useEdgeLength)
{
    if(useEdgeLength)
        InitEdgeLength(x,y,a,b);
    else
        InitDiagonalPoint(x,y,a,b);
}

int Rect::x0() { return x;} //この関数に意味はない
int Rect::y0() { return y;} //この関数に意味はない
int Rect::x1() { return x + (width - 1);}
int Rect::y1() { return y + (height - 1);}

void Rect::InitEdgeLength(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Rect::InitDiagonalPoint(int x0, int y0, int x1, int y1)
{
    this->x = x0;
    this->y = y0;
    this->width = x1 - x0;
    this->height = y1 - y0;
}

Rect Rect::Trim()
{
    Rect trimedRect;
    if(x0() < 0)
    {
        trimedRect.x = 0;
        trimedRect.width = width + x0();
    }
    else if(x1() > 11)
    {
        trimedRect.x = x0();
        trimedRect.width = 12 - x0();
    }
    else
    {
        trimedRect.x = x;
        trimedRect.width = width;
    }

    trimedRect.y = y;
    trimedRect.height = height;

    return trimedRect;
}

Rect Rect::Cut(Rect effectiveRect)
{
    Rect cutRect;

    cutRect.x =     x0() > effectiveRect.x0() ? x0() : effectiveRect.x0();
    cutRect.width = x1() < effectiveRect.x1() ? x1() - cutRect.x0() + 1 : effectiveRect.x1() - cutRect.x0() + 1;
    cutRect.y = y;
    cutRect.height = height;

    return cutRect;
}

//==========================================================
//-------------------- TmpDisp -----------------------------
//==========================================================

class TmpDisp
{
private:
    virtualDisp* canvas;
    Color tmpDisp[12][16];
    bool isPlayAnim;
public:
    static TmpDisp *inst;

    TmpDisp(virtualDisp *canvas);
    void SetTmpDisp();
    void DrawTmpDisp(Color color, int delay);
    void DrawTmpDisp(Color color);
    void StopAnim();
};

TmpDisp *TmpDisp::inst = NULL;

TmpDisp::TmpDisp(virtualDisp* canvas)
{
    this->canvas = canvas;
}

void TmpDisp::SetTmpDisp()
{
int x,y;

    for(y = 0; y < 16; y++)
    {
        for(x = 0; x < 12; x++)
        {
                tmpDisp[x][y] = canvas->pixel[x][y];
        }
    }
}

void TmpDisp::DrawTmpDisp(Color color, int dalay)
{
    int x,y;
    isPlayAnim = true;

    for(y = 15; y >= 0 && isPlayAnim; y--)
    {
        for(x = 0; x < 12 && isPlayAnim; x++)
        {
            if(tmpDisp[x][y] != palette->black)
                canvas->drawPoint(x, y, color);
            else
                canvas->drawPoint(x, y, palette->black);
            canvas->show();
            GameSystem::Delay_ms(dalay);
        }
    }
    isPlayAnim = false;
}

void TmpDisp::StopAnim()
{
    isPlayAnim = false;
}

void TmpDisp::DrawTmpDisp(Color color)
{
    int x,y;

    for(y = 15; y >= 0; y--)
    {
        for(x = 0; x < 12; x++)
        {
            if(tmpDisp[x][y] != palette->black)
                canvas->drawPoint(x, y, color);
            else
                canvas->drawPoint(x, y, palette->black);
        }
    }
    canvas->show();
}

//==========================================================
//------------------------- Bar ----------------------------
//==========================================================
class Bar
{
public:
    enum MoveMode   //移動モード
    {
        ThroughtLeft = 0,   //左から一方向
        ThroughtRight,  //右から一方向
        PingPongLeft,   //左から往復
        PingPongRight,  //右から往復
        AnimToLeft,     //左へ行くアニメーション
        AnimToRight     //右へ行くアニメーション
    };

    Bar(virtualDisp* canvas, int stageNum, int width, int height, int waitTick, MoveMode mode, Color);
    Bar(virtualDisp *canvas, Rect rect, int waitTick, MoveMode mode, Color color);
    void Update();
    void Init();
    void Activate();
    bool GetActive();
    bool IsPlayAnim();
    void Stop();
    Rect Cut(Rect effectiveRect);
    Rect GetRect();

private:
    virtualDisp* canvas;
    Rect rect;      //座標データ
    Rect cutRect;   //カットされた後
    int waitTick;   //待ちTick
    MoveMode mode;  //移動モード
    Color color;    //色
    //Bar* leftAnimBar;    //アニメーション用
    //Bar* rightAnimBar;   //アニメーション用
    //Bar* animBar[2];   //アニメーション用

    int direction; //移動方向
    bool isActive = false; //移動中か
    bool isAnimate; //アニメーション中か

    int currentTick;    //経過Tick

    void InitRect();
    void Move();
    void SetDirection();
    void CutAnim();
};


///
/// \brief コンストラクタ(初期化)
/// \param stageNum 段数
/// \param width 幅
/// \param height 高さ
/// \param waitTick 待ちTick
/// \param mode 移動モード
///
Bar::Bar(virtualDisp *canvas,int stageNum, int width, int height, int waitTick, MoveMode mode, Color color)
{
    this->canvas = canvas;
    rect.y = 15 - stageNum - (height - 1);
    rect.width = width;
    rect.height = height;
    this->color = color;
    this->waitTick = waitTick;
    this->mode = mode;
    Init();
}

Bar::Bar(virtualDisp *canvas, Rect rect, int waitTick, MoveMode mode, Color color)
{
    this->canvas = canvas;
    this->rect = rect;
    this->color = color;
    this->waitTick = waitTick;
    this->mode = mode;
    Init();
}

void Bar::Init()
{
    //cout << "Debug-Bar::Init()" << endl;
    switch (mode)
    {
    case ThroughtLeft:
    case PingPongLeft:
        rect.x = -rect.width;
        direction = 1;
        break;

    case ThroughtRight:
    case PingPongRight:
        rect.x = 12;
        direction = -1;
        break;
    case AnimToLeft:
        direction = -1;
        break;
    case AnimToRight:
        direction = 1;
        break;
    }
}

void Bar::Move()
{
    rect.x += direction;

    switch (mode)
    {
    case ThroughtLeft:
        if(rect.x0() > 11)
            rect.x = -rect.width;
        break;
    case ThroughtRight:
        if(rect.x1() < 0)
            rect.x = 12;
        break;
    case PingPongLeft:
    case PingPongRight:
        if(rect.x0() > 11 || rect.x1() < 0)
            direction *= -1;
        break;
    case AnimToLeft:
        if(rect.x1() < 0)
            isActive = false;
    case AnimToRight:
        if(rect.x0() > 11)
            isActive = false;
    }

    //SoundManager::inst->PlayOverWrite(SoundManager::SoundName::SE_move);

    Rect bar = rect.Trim();

    canvas->fillRect(0, bar.y, 12, bar.height, palette->black);
    canvas->fillRect(bar.x, bar.y, bar.width, bar.height, color);
    canvas->show();

    //cout << "direction:" << direction << endl;
    //cout << "------------------" << endl;
}

void Bar::Update()
{
    //int i;
    Rect tmpRect;
    if(isActive)
    {
        currentTick++;
        if(currentTick % waitTick == 0)
            Move();
    }
    else
        currentTick = 0;
}

bool Bar::GetActive()
{
    return isActive;
}

void Bar::Activate()
{
    isActive = true;
    
    if(/*waitTick <= 35 &&*/ waitTick > BarSpeedLevel.slow)
    	SoundManager::inst->Play(SoundManager::SE_osoi,true);
    else if(waitTick <= BarSpeedLevel.slow && waitTick > BarSpeedLevel.normal)
    	SoundManager::inst->Play(SoundManager::SE_hutuu,true);
    else if(waitTick <= BarSpeedLevel.normal && waitTick >= BarSpeedLevel.fast)
    	SoundManager::inst->Play(SoundManager::SE_hayai,true);
}

void Bar::Stop()
{
    SoundManager::inst->Play(SoundManager::SE_stop);
    
    SoundManager::inst->Stop(SoundManager::SE_osoi);
    SoundManager::inst->Stop(SoundManager::SE_hutuu);
    SoundManager::inst->Stop(SoundManager::SE_hayai);
    isActive = false;
}

Rect Bar::Cut(Rect effectiveRect)
{
    if(effectiveRect.height == 0)
    {
        cutRect = rect;
        effectiveRect.height = rect.height;
    }
    else
        cutRect = rect.Cut(effectiveRect);

    cutRect = cutRect.Trim();

	if(cutRect.width > 0)
    	CutAnim();

    canvas->fillRect(0, cutRect.y, 12, cutRect.height, palette->black);
    canvas->fillRect(cutRect.x, cutRect.y, cutRect.width, cutRect.height, palette->green);
    canvas->show();

    TmpDisp::inst->SetTmpDisp();

    return cutRect;
}

void Bar::CutAnim()
{
    int i;
    //TmpDisp::inst->SetTmpDisp();
    Rect *leftRect = new Rect(rect.x0(),rect.y0(),cutRect.x0() - rect.x0(), rect.height);
    Rect *rightRect = new Rect(cutRect.x1() + 1, cutRect.y0(), rect.x1() - cutRect.x1(), rect.height);

    *leftRect = leftRect->Trim();
    *rightRect = rightRect->Trim();

    if(leftRect->width > 0 || rightRect->width > 0)
    {
        for(i = 0; i < 7; i++)
        {
            TmpDisp::inst->DrawTmpDisp(palette->green);
            canvas->fillRect(cutRect.x, cutRect.y, cutRect.width, cutRect.height, palette->yellow);
            if(i % 2 == 0)
            {
                canvas->fillRect(leftRect->x, leftRect->y, leftRect->width, leftRect->height, palette->red);
                canvas->fillRect(rightRect->x, rightRect->y, rightRect->width, rightRect->height, palette->red);
            }
            canvas->show();
            GameSystem::Delay_ms(100);
        }
        SoundManager::inst->Play(SoundManager::SE_cut);

        while(leftRect->y0() < 16 || rightRect->y0() < 16)
        {
            TmpDisp::inst->DrawTmpDisp(palette->green);
            canvas->fillRect(cutRect.x, cutRect.y, cutRect.width, cutRect.height, palette->yellow);
            canvas->fillRect(leftRect->x, leftRect->y, leftRect->width, leftRect->height, palette->red);
            canvas->fillRect(rightRect->x, rightRect->y, rightRect->width, rightRect->height, palette->red);
            canvas->show();
            GameSystem::Delay_ms(100);
            leftRect->y++;
            rightRect->y++;
        }
    }
    TmpDisp::inst->DrawTmpDisp(palette->green);
    canvas->fillRect(cutRect.x, cutRect.y, cutRect.width, cutRect.height, palette->yellow);
    canvas->show();
    GameSystem::Delay_ms(100);
}

Rect Bar::GetRect()
{
    return rect;
}

bool Bar::IsPlayAnim()
{
    return isAnimate;
}

//==========================================================
//-------------------- Qbridge ----------------------------
//==========================================================
class Qbridge
{
private:
    virtualDisp* canvas;
    std::vector<Bar*> bars;

    int stageCount;
    Rect effectiveRect; //有効範囲
    bool isPlay = false;
    bool isGameOver = false;
    bool isPlayAnim = false;
    int lv;

    void Init();
    void GameOverAnim();
    void GameOver();
    void GameClear();
    void ClearAnim();
    
    void InitBar();
public:
    Qbridge(virtualDisp *canvas);
     ~Qbridge();
    void Play(int lv);
    void Update();
    void ActiveBar(int);
    void OnButtonDown(unsigned char keymap);

    bool GetPlay();
};



Qbridge::Qbridge(virtualDisp *canvas)
{
    this->canvas = canvas;
    this->lv = lv;
    //Init();
    InitBar();
    TmpDisp::inst = new TmpDisp(canvas);
}

Qbridge::~Qbridge()
{
        unsigned int i;
        for(i = 0; i < bars.size(); i++)
                delete bars[i];
}

void Qbridge::InitBar()
{
    /*
    int i;
    for(i = 0; i < bars.size(); i++)
            delete bars[i];
            
    bars.clear();
    switch (lv) {
    case 0:
	*/
	/*
        bars.push_back(new Bar(canvas,0,10,1,50, Bar::ThroughtLeft, palette->blue));
        bars.push_back(new Bar(canvas,1,8,2,40, Bar::ThroughtRight, palette->blue));
        bars.push_back(new Bar(canvas,3,7,1,35, Bar::PingPongLeft, palette->blue));
        bars.push_back(new Bar(canvas,4,7,2,30, Bar::PingPongRight, palette->yellow));
        bars.push_back(new Bar(canvas,6,5,4,20, Bar::ThroughtLeft, palette->yellow));
        bars.push_back(new Bar(canvas,10,6,2,25, Bar::ThroughtRight, palette->yellow));
        bars.push_back(new Bar(canvas,12,7,1,25, Bar::PingPongLeft, palette->red));
        bars.push_back(new Bar(canvas,13,5,2,20, Bar::PingPongRight, palette->red));
        bars.push_back(new Bar(canvas,15,2,1,20, Bar::PingPongRight, palette->red));
        //break;
	*/	
	/*
    case 1:
	*/
	/*
        bars.push_back(new Bar(canvas,0,10,1,50, Bar::ThroughtLeft, palette->blue));
        bars.push_back(new Bar(canvas,1,8,1,40, Bar::ThroughtRight, palette->blue));
        bars.push_back(new Bar(canvas,2,6,2,40, Bar::PingPongLeft, palette->blue));
        bars.push_back(new Bar(canvas,4,5,1,30, Bar::PingPongRight, palette->yellow));
        bars.push_back(new Bar(canvas,5,5,1,30, Bar::ThroughtLeft, palette->yellow));
        bars.push_back(new Bar(canvas,6,4,3,50, Bar::PingPongLeft, palette->blue));
        bars.push_back(new Bar(canvas,9,5,2,35, Bar::ThroughtRight, palette->yellow));
        bars.push_back(new Bar(canvas,11,8,1,20, Bar::ThroughtLeft, palette->red));
        bars.push_back(new Bar(canvas,12,4,3,25, Bar::PingPongRight, palette->red));
        bars.push_back(new Bar(canvas,15,1,1,15, Bar::ThroughtRight, palette->purple));
	*/
	/*	
	//break;
    case 2:
        bars.push_back(new Bar(canvas,0,10,1,70, Bar::PingPongLeft, palette->blue));
        bars.push_back(new Bar(canvas,1,8,1,50, Bar::ThroughtLeft, palette->blue));
        bars.push_back(new Bar(canvas,2,7,1,40, Bar::ThroughtRight, palette->blue));
        bars.push_back(new Bar(canvas,3,7,1,30, Bar::PingPongRight, palette->yellow));
        bars.push_back(new Bar(canvas,4,5,1,45, Bar::PingPongLeft, palette->blue));
        bars.push_back(new Bar(canvas,5,6,1,30, Bar::ThroughtLeft, palette->yellow));
        bars.push_back(new Bar(canvas,6,7,1,25, Bar::ThroughtRight, palette->red));
        bars.push_back(new Bar(canvas,7,4,1,35, Bar::PingPongRight, palette->yellow));
        bars.push_back(new Bar(canvas,8,6,1,40, Bar::PingPongLeft, palette->blue));
        bars.push_back(new Bar(canvas,9,7,1,20, Bar::ThroughtLeft, palette->red));
        bars.push_back(new Bar(canvas,10,5,1,30, Bar::ThroughtRight, palette->yellow));
        bars.push_back(new Bar(canvas,11,4,1,30, Bar::PingPongRight, palette->yellow));
        bars.push_back(new Bar(canvas,12,3,1,60, Bar::PingPongLeft, palette->blue));
        bars.push_back(new Bar(canvas,13,1,1,30, Bar::ThroughtLeft, palette->purple));
        bars.push_back(new Bar(canvas,14,1,1,25, Bar::ThroughtRight, palette->purple));
        bars.push_back(new Bar(canvas,15,1,1,20, Bar::PingPongRight, palette->purple));
        break;
        */

    	//TFP完全再現
                bars.push_back(new Bar(canvas,0,10,1,45, Bar::PingPongRight, palette->yellow));
                bars.push_back(new Bar(canvas,1,9,1,45, Bar::PingPongRight, palette->yellow));
                bars.push_back(new Bar(canvas,2,8,1,40, Bar::ThroughtRight, palette->yellow));
                bars.push_back(new Bar(canvas,3,7,1,30, Bar::ThroughtLeft, palette->yellow));
                bars.push_back(new Bar(canvas,4,6,1,30, Bar::ThroughtRight, palette->yellow));
                bars.push_back(new Bar(canvas,5,5,4,25, Bar::PingPongRight, palette->yellow));
                bars.push_back(new Bar(canvas,9,4,1,25, Bar::PingPongRight, palette->yellow));
                bars.push_back(new Bar(canvas,10,12,2,18, Bar::ThroughtRight, palette->yellow));
                bars.push_back(new Bar(canvas,12,2,3,18, Bar::PingPongRight, palette->yellow));
                bars.push_back(new Bar(canvas,15,1,1,13, Bar::PingPongRight, palette->yellow));
	
	/*
        bars.push_back(new Bar(canvas,0,5,1,50, Bar::PingPongLeft, palette->blue));
        bars.push_back(new Bar(canvas,1,4,1,45, Bar::ThroughtLeft, palette->blue));
        bars.push_back(new Bar(canvas,2,3,1,40, Bar::ThroughtRight, palette->blue));
        bars.push_back(new Bar(canvas,3,2,1,35, Bar::PingPongRight, palette->yellow));
        bars.push_back(new Bar(canvas,4,1,1,30, Bar::PingPongLeft, palette->blue));
        bars.push_back(new Bar(canvas,5,2,1,25, Bar::ThroughtLeft, palette->yellow));
        bars.push_back(new Bar(canvas,6,3,1,20, Bar::ThroughtRight, palette->red));
        bars.push_back(new Bar(canvas,7,4,1,15, Bar::PingPongRight, palette->yellow));
        bars.push_back(new Bar(canvas,8,5,1,10, Bar::PingPongLeft, palette->blue));
        bars.push_back(new Bar(canvas,9,4,1,15, Bar::ThroughtLeft, palette->red));
        bars.push_back(new Bar(canvas,10,3,1,20, Bar::ThroughtRight, palette->yellow));
        bars.push_back(new Bar(canvas,11,2,1,25, Bar::PingPongRight, palette->yellow));
        bars.push_back(new Bar(canvas,12,1,1,30, Bar::PingPongLeft, palette->blue));
        bars.push_back(new Bar(canvas,13,1,1,25, Bar::ThroughtLeft, palette->purple));
        bars.push_back(new Bar(canvas,14,1,1,20, Bar::ThroughtRight, palette->purple));
        bars.push_back(new Bar(canvas,15,1,1,15, Bar::PingPongRight, palette->purple));
       
    }*/
}

void Qbridge::Play(int lv)
{
    if(!isPlay)
    {
        this->lv = lv;
        SoundManager::inst->Play(SoundManager::BGM_tfp, true);
        Init();
        isPlay = true;
    }
}

void Qbridge::Init()
{
    int i;
    isGameOver = false;
    isPlay = false;

    effectiveRect.height = 0;
    stageCount = 0;

    //InitBar();
    for(i = 0; i < (int)bars.size(); i++)
         bars[i]->Init();

    canvas->clear();
    canvas->show();
    TmpDisp::inst->SetTmpDisp();
}

void Qbridge::Update()
{
    if(!isGameOver && isPlay)
    {
        bars[stageCount]->Update();
    }
}

void Qbridge::OnButtonDown(unsigned char keymap)
{
    if(!isPlay)
        return;

    if(stageCount < (int)bars.size())
    {
        Bar* bar = bars[stageCount];
        switch (keymap) {
            case InputNum::btn_large:
            	//cout << "TestNow" << endl;
                if(!bar->GetActive())
                    bar->Activate();    //アクティブ状態に
                else
                {
                    bar->Stop();
                    effectiveRect = bar->Cut(effectiveRect);

                    if(effectiveRect.width <= 0)
                        GameOver();     //ゲームオーバー
                    else
                    {                   //続行
                        stageCount ++;
                        OnButtonDown(InputNum::btn_large);  //疑似ボタン押し
                    }
                }
                break;
            case InputNum::btn_smallA:	//赤
                TmpDisp::inst->StopAnim();
            break;
            case InputNum::btn_smallC:	//青
            	//GameClear();
            break;
        }
    }
    else
    {
        GameClear(); //クリア
    }
}

bool Qbridge::GetPlay()
{
    cout << "State:Test" << endl;
    return isPlay;
}

void Qbridge::GameOver()
{
    cout << "State:GameOver" << endl;
    isGameOver = true;
    //SoundManager::inst->Stop(SoundManager::BGM_game);
    SoundManager::inst->Stop(SoundManager::BGM_tfp);
    SoundManager::inst->Play(SoundManager::SE_miss);

    GameOverAnim();
    isPlay = false;
}

void Qbridge::GameOverAnim()
{
    int y;
    Rect missRect = bars[stageCount]->GetRect().Trim();

    canvas->fillRect(0, missRect.y0(), 12, missRect.height, palette->black);
    canvas->fillRect(missRect.x0(), missRect.y0(), missRect.width, missRect.height, palette->red);
    canvas->show();

    TmpDisp::inst->SetTmpDisp();
	
    GameSystem::Delay_ms(500);
    isPlayAnim = true;
    for(y = 15; y >= 0 && isPlayAnim; y--)
    {
        canvas->fillRect(0, y, 12, 1, palette->red);
        canvas->show();

        GameSystem::Delay_ms(100);
    }
    
    TmpDisp::inst->DrawTmpDisp(palette->red,10);
    isPlayAnim = false;
}

void Qbridge::GameClear()
{
	cout << "Clear!!" << endl;
    //SoundManager::inst->Stop(SoundManager::BGM_game);
    SoundManager::inst->Stop(SoundManager::BGM_tfp);
    SoundManager::inst->Play(SoundManager::SE_fanfare);
    ClearAnim();
    isPlay = false;
}

void Qbridge::ClearAnim()
{
    int dirX = 1;
    int dirY = 0;

    int x  =  0, y  =  0;		//現在の座標
	int x0 = -1, y0 =  0;		//左上の座標
	int x1 = 11, y1 = 15;		//右下の座標
	
    TmpDisp::inst->SetTmpDisp();
	
    isPlayAnim = true;
    while (y1 - y0 >= 0 && x1 - x0 >= 0 && isPlayAnim)
    {   
    	cout << "X:" << x << " Y:" << y << endl;
    	cout << y1 - y0 << "  " << x1 - x0 << endl;
    	
        canvas->drawPoint(x, y, palette->aqua);
        canvas->show();
        
        x += dirX;
        y += dirY;
        
		if(x >= x1 && dirX == 1)
		{
			dirX = 0;
			dirY = 1;
			
			x0++;
		}
		if(y >= y1 && dirY ==1)
		{
			dirX = -1;
			dirY = 0;
			
			y0++;
		}
		if(x <= x0 && dirX == -1)
		{
			dirX = 0;
			dirY = -1;
			
			x1--;
		}
		if(y <= y0 && dirY == -1)
		{
			dirX = 1;
			dirY = 0;
			
			y1--;
		}
        GameSystem::Delay_ms(10);
    }
    
    TmpDisp::inst->DrawTmpDisp(palette->green,10);
    
    isPlayAnim = false;
}

#endif // QBRIDGE_H
