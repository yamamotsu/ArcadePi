#ifndef COLOR_H
#define COLOR_H

/**
 * @file color.h
 * @brief Color Class
 * @author Y.Yamamoto
 * @date 2017/5/17
 */

class Color
{

	public:
	/**
	 * @brief カラークラスコンストラクタ
	 * 
	 * RGBの色情報を保持するクラス.<br>
	 * 24bit RGBの色情報を保持するクラス.<br>
	 * ファミコンなどで使用されるいわゆるデジタル8色を使用する場合は、
	 * あらかじめ8色がテンプレートとして格納されているPaletteクラスが
	 * 利用できます.
	 */
	Color();
	/**
	 * @brief カラークラスコンストラクタ
	 *
	 * 24bit RGBの色情報を保持するクラス.<br>
	 * ファミコンなどで使用されるいわゆるデジタル8色を使用する場合は、
	 * あらかじめ8色がテンプレートとして格納されているPaletteクラスが
	 * 利用できます.
	 * @param r 赤色成分
	 * @param g 緑
	 * @param b 青
	 * @sa Palette
	 */
	Color(unsigned char r,unsigned char g,unsigned char b);
	
	/**
	* @brief 色情報をセット
	* @param r 赤色成分
	* @param g 緑
	* @param b 青
	*
	*/
	void setColor(unsigned char R,unsigned char G,unsigned char B);
    
    /**
    * @brief 色情報を取得
    * 
    * 指定した色成分(r,g,b)の強さを取得します
    * 
    * @param rgb 取得する色成分のフラグ(r:0,g:1,b:2)
    * @return 色データ
    */
    unsigned char getElement(int rgb);

    //Color &digitalize(Color &);
    
    unsigned char r,g,b;

    bool operator == (const Color &c1);
    
    bool operator != (const Color &c1);
    
    Color &operator = (const Color &c1);

};

#endif //COLOR_H
