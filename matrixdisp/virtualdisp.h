#ifndef VIRTUALDISP_H
#define VIRTUALDISP_H

/**
 * @file virtualdisp.h
 * @brief 仮想画面クラス
 * @author y.yamamoto
 * @date 2017/6/20
 */

#include "color.h"
#include "matrixdisp.h"
#include "virtualdisp.h"
#include <iostream>
#include <mutex>


class virtualDisp
{
private:
    Matrixdisp *ptr;
    //std::mutex *mtx;
    bool internal_created_flag;
public:
    /**
     * @brief virtualDispクラスのコンストラクタ
     *
     * virtualDispオブジェクトが生成されると、
     * ゲーム画面に対応する仮想画面がメモリ上に構成されます.
     * MatrixDispクラスのメンバ関数write()では1ドットごとに実際の画面が書き変わってしまい
     * 画面のちらつきが発生します.
     * このため、更新したい描画内容を一度メモリ上に保持しておき、
     * 一括で実際の画面を書き換える事でこれを防ぎます.<br>
     * 通常、画面の描画処理はこのクラスによって行うことが推奨されます.
     *
     * @param ptr_disp MatrixDispクラスへのポインタ
     */
    virtualDisp(Matrixdisp *ptr_disp);
    
    virtualDisp();

    ~virtualDisp();

    /**
     * @brief 画面情報を保持する配列
     *
     * 仮想画面上のドット情報を保持しているColorクラスのオブジェクトの配列
     * @sa Color
     *
     */
    Color pixel[12][16];

    /**
     * @brief 仮想画面の内容を実際の画面に適用する
     *
     * 現在仮想画面上に保持されている描画内容を実際の画面に適用します
     */
    void show();

    /**
     * @brief 仮想画面の内容をクリアする
     *
     * 仮想画面上に保持されている描画内容を破棄(全て"黒"のデータ)します.
     */
    void clear();

    /**
     * @brief 長方形の枠を指定した色で描画
     *
     * 長方形の左上の角の点を起点とし,幅'width',高さ'height'の長方形の枠を
     * 仮想画面上に描画します.<br>
     * 長方形が画面外にはみ出るような起点の位置や幅,高さを指定した場合描画されず0が返されます.
     * @param x0 左上点のx座標
     * @param y0 左上点のy座標
     * @param width 幅
     * @param height 高さ
     * @param color 色
     * @return　成功：1,失敗:0
     * @sa Color
     */
    int drawRect(int x0,int y0,int width,int height,Color &color);

    /**
     * @brief 長方形を指定した色で内側を塗りつぶして描画
     *
     * 長方形の左上の角の点を起点とし,幅'width',高さ'height'の長方形の枠を
     * 仮想画面上に描画します.内側も指定した色で塗りつぶされます.<br>
     * 長方形が画面外にはみ出るような起点の位置や幅,高さを指定した場合描画されず0が返されます.
     * @param x0 左上点のx座標
     * @param y0 左上点のy座標
     * @param width 幅
     * @param height 高さ
     * @param color 色
     * @return 成功:1 失敗:0
     * @sa Color
     */
    int fillRect(int x0,int y0,int width,int height,Color &color);

    /**
     * @brief 指定位置に1ドットの点を描画
     *
     * 仮想画面上の指定位置のドットを指定した色に変更します
     * @param x x座標
     * @param y y座標
     * @param color 色
     * @return 成功:1 失敗:0
     */
    int drawPoint(int x,int y,Color &color);

    /**
     * @brief 垂直線を描画
     * @param x x座標
     * @param y0 上端y座標
     * @param y1 下端y座標
     * @param color 色
     * @return 成功:1 失敗:0
     */
    int drawVerticalLine(int x,int y0,int y1,Color &color);

    /**
     * @brief 水平線を描画
     * @param y y座標
     * @param x0 左端x座標
     * @param x1　右端x座標
     * @param color 色
     * @return 成功:1 失敗:0
     */
    int drawHorizontalLine(int y,int x0,int x1,Color &color);
};

#endif // VIRTUALDISP_H
