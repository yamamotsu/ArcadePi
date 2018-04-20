#ifndef GAME_H
#define GAME_H

#include <vector>
#include "matrixdisp/matrixdisp.h"
#include "matrixdisp/virtualdisp.h"
#include "gamesystem.h"

using namespace std;

class Qbridge;
class SoundManager;
class Game :public GameSystem
{
private:
    //ここに使用したい変数を追加していく

    Qbridge *qbridge;
    int lv;

    //キー押下時に呼ばれるイベント
    void keyPressEvent(unsigned char keymap);
    //キーを離したときに呼ばれるイベント
    void keyReleaseEvent(unsigned char keymap);
    //一定時間ごとに呼ばれるイベント
    void RoutineProc();
public:
    Game();
    ~Game();

};

#endif // GAME_H
