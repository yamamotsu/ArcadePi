/*
 * 3bit Color Palette Class
 * Created on 2017/05/17 by y.yamamoto
*/

#ifndef PALETTE_H
#define PALETTE_H

/**
 * @file palette.h
 * @brief デジタル8色パレットクラス
 * @author y.yamamoto
 * @date 2017/05/17
 */

class Palette
{
    public:

    /**
    * @brief パレットクラス
    */
    Palette();

    /**
     * @brief 赤
     */
    Color red;         //赤

    /**
     * @brief 緑
     */
    Color green;       //緑

    /**
     * @brief 青
     */
    Color blue;        //青

    /**
     * @brief 黄色
     */
    Color yellow;      //黄

    /**
     * @brief 水色
     */
    Color aqua;        //水色

    /**
     * @brief 紫
     */
    Color purple;      //紫

    /**
     * @brief 白
     */
    Color white;

    /**
     * @brief 黒
     */
    Color black;

    /**
     * @brief カラーセット
     *
     * 赤,緑,青,黄,水色,紫,白,黒
     * の順に格納されています
     */
    Color colorset[8];			//上記8色を配列化
	
};

//標準で利用できるパレットオブジェクト
static Palette *palette = new Palette();

#endif //PALETTE_H
