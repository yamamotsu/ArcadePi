#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <alsa/asoundlib.h>

#include "soundcontainer.h"
using namespace std;

#define DEF_PCM_FORMAT      SND_PCM_FORMAT_S16
#define DEF_CHANNELS        2                       //チャンネル数
#define DEF_SAMPLEPERSEC    44100                   //サンプリングレート
#define DEF_BITPERSAMPLE    16                      //量子化ビット数
#define DEF_LATENCY         50000                   //レイテンシ(こぴぺ)
#define DEF_SAMPLES         1024
#define DEF_SND_CONTAINS    32						//格納できる最大ファイル数
#define DEF_SND_MIXNUM      4						//最大同時再生数
#define DEF_ALSA_DEVICE     "plughw:sndrpihifiberry,0"

enum SndStat{
    empty = 0,
    contained,
    playing,
    paused,
    stopped
};

typedef struct tagSoundInfo{
    SndStat status;                 //ステータス
    int internal_created_flag;      //内部的に生成されたオブジェクトかどうかのフラグ
    int loopf;
} SoundInfo;

class SoundPlayer
{
private:
    int soundcnt;
    string device;
    int enable;
    int deathf;
    SoundInfo info[DEF_SND_CONTAINS];
    SoundContainer *container[DEF_SND_CONTAINS];      //音源オブジェクトへのポインタ
    snd_pcm_t *handle;
    thread *hnd;
    mutex *mtx;
public:
	/**
	*	@brief SoundPlayer Constructor
	* 	
	* 	Constructor of SoundPlayer class.
	* 
	*/ 
    SoundPlayer();
    
    /**
     * 	@brief SoundPlayer Destructor
     * 
     * 	Destructor of SoundPlayer class.
     * 
     */ 
    ~SoundPlayer();
    
    /**
     * 	@brief Play routine
     * 
     */
    void routine();
    
    /**
     * 	@brief Set sound object by wave file
     */ 
    int setSound(const char *wave_file_name);
    int setSound(SoundContainer *container);
    void setDevice(char *device_name);
   	
    void play(int id);
    void play(int id,int is_loop);
    void replay(int id);
    void pause(int id);
    void stop(int id);
    void wait();
    
    static void setVolume(double volume);
};

#endif // SOUNDPLAYER_H
