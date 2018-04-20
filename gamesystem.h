#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <thread>
#include <mutex>

#include "menu.h"
#include "soundlib/soundplayer.h"

/**
 * @brief The GameSystem class
 * @author Y.Yamamoto
 * @date 2017/6/25
 */

//void GS_routine_start(GameSystem *ptr);


//入力部品のナンバー対応
/**
 * @brief 入力フラグ用列挙体
 *
 * 入力キーを判定するためのフラグビットとエイリアスの対応
 */
enum InputNum{
    btn_large=1,  //ボタン大(メインボタン)
    btn_smallA=2, //ボタン小A
    btn_smallB=4, //B
    btn_smallC=8, //C
    stk_up=16,     //ジョイスティック↑
    stk_down=32,   //ジョイスティック↓
    stk_right=64,  //→
    stk_left=128    //←
};

enum EventNum{
    nothing = 0,
    key_pressed = 1,
    key_released = 2
};

class GameSystem
{


private:
    char keycheck();
    int deathf;
    int menuf;
    static void routine_start(GameSystem *ptr);
    std::thread *hnd;
    int endf;
    int evstatus;
    int mslooptime;
    int tick;    
    unsigned char keymap;
    bool EventDetector();
    std::mutex *mtx;
protected:
    virtual void RoutineProc()=0;
    virtual void keyPressEvent(unsigned char keymap)=0;
    virtual void keyReleaseEvent(unsigned char keymap)=0;
     
public:
    //Matrixdisp *disp;
    
    /**
     * @brief GameSystemコンストラクタ
     *
     * GameSystemはゲーム全体を管理するクラス.
     * ゲームの描画オブジェクト，仮想画面オブジェクト，キー入力監視関数などを生成します.
     *
     */
    GameSystem();
    ~GameSystem();

    /**
     * @brief 指定した時間(マイクロ秒)待つ
     * @param count 待機する時間(us)
     */
    static void Delay_us(int count);

    /**
     * @brief 指定した時間(ミリ秒)待つ
     * @param count 待機する時間(ms)
     */
    static void Delay_ms(int count);

    /**
     * @brief 指定したキーが押されているか調べる
     *
     * input_numに指定した値に対応する入力部品が押されているか調べ，
     * 押されているとき1,そうでないときは0を返します.<br>
     * 引数のinput_numには列挙体InputNumのエイリアスが利用できます
     * @param input_num 押下を判定する入力部品番号
     * @return 押されている:1 押されていない:0
     * @sa InputNum
     */
    bool isPress(char input_num);

    /**
     * @brief ゲームのメインループを開始する
     *
     * メインループ(無限ループ)を開始します.
     * ループは指定した時間(デフォルト1ms)ごとに繰り返され，
     * イベント検出関数EventDetector()とループ処理関数RoutineProc()
     * が呼び出されます．
     * 通常メインループ内の処理はRoutineProc()関数内に記述してください<br>
     * また，Start()内はEnd()関数が呼ばれるまで無限ループするため
     * 一度Start()を実行するとRoutineProc内などでEnd()関数を実行しない限り
     * その後の処理が実行されません.
     */
    void Start();

    /**
     * @brief ゲームのメインループを終了する
     *
     * メインループを終了します.
     */
    void End();

    /**
     * @brief メインループ開始後のループ数(tick数)を取得する
     *
     * Start()によりメインループが開始されてから何ループしたか(これをtickと定義)を返します.
     * Start()が実行されていないとき-1を返します.
     * @return tick数
     */
    int getTick();

    /**
     * @brief メインループのループ周期を設定する
     *
     * 1msごとに設定でき，デフォルトは1msです
     * @param ms_looptime ループ周期(ms)
     */
     void setLoopTime(int ms_looptime);
     
     void callMenu();
     
     static virtualDisp *canvas;
     static SoundPlayer *soundplayer;
     //static Menu *menu;
     
     
     //使用上公開メンバ関数だが
     //外部から呼び出し禁止
     void EventRoutine();     
};

#endif // GAMESYSTEM_H
