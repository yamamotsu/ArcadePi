#ifndef PIN_ASSIGN_H
#define PIN_ASSIGN_H

//画面表示関連アサイン		  使用するピンとその動作
#define PIN_SERIALEN	7	//シリアルイネーブルピン
#define PIN_SERIALCLK	11	//シリアルクロックピン
#define PIN_SERIALS1	15	//シリアルデータ(上位8ビット)出力ピン
#define PIN_SERIALS2	16	//シリアルデータ(下位8ビット)出力ピン
#define PIN_ROWNUM_0	18	//列番号指定データ(最下位ビット)出力ピン
#define PIN_ROWNUM_1	19	//↓
#define PIN_ROWNUM_2	21	//↓
#define PIN_ROWNUM_3	22	//列番号指定データ(最上位ビット)
#define PIN_ENABLE	23		//描画イネーブルピン
#define PIN_RED		24		//赤色データPWM出力ピン
#define PIN_GREEN	26		//緑
#define PIN_BLUE	27		//青

//入力関連
#define PIN_JOYSTICK_RIGHT      33      //ジョイスティック上
#define PIN_JOYSTICK_UP         36      //下
#define PIN_JOYSTICK_DOWN    	37      //右
#define PIN_JOYSTICK_LEFT       38      //左
#define PIN_BUTTON_LARGE        3       //ボタン大
#define PIN_BUTTON_SMALL1       5       //ボタン小(1)
#define PIN_BUTTON_SMALL2       31      //ボタン小(2)
#define PIN_BUTTON_SMALL3       32      //ボタン小(3)


void setup_pinmode_disp();
void setup_pinmode_input();


#endif	//PIN_ASSIGN_H
