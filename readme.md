# ArcadePi-RasPi 12x16 pixel arcade game library
大分高専電気電子工学科 2017年度・5年デザイン実習のグループ制作課題で3班が製作した
アーケードゲーム「MiracleDreamer」で使用したゲームエンジンのソースです.
RaspberryPi上で動作し,内部でwiringPiを用いています.
またサウンド再生機能のためにALSAを使用しています.

# howtouse
予めALSA と wiringpiをインストールしておきます.
```
$ sudo apt-get install libasound2 libasound2-dev
```
またgitやmake, gccなどをインストールしていない場合はしておきます.

```
$ git clone https://github.com/yamamotsu/ArcadePi
$ cd ./ArcadePi
$ make
```

# できること

* キー入力状態取得
* 3bitカラー（ディジタル8色)でのディスプレイ描画
* bmp画像読み込み&描画
* wav音源再生(ミキシングに対応)