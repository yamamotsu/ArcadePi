#ifndef SOUNDCONTAINER_H
#define SOUNDCONTAINER_H


#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

typedef struct tagPCM_INFO_ {
    uint16_t Channels;       //チャンネル数　モノラルは1、ステレオは2
    uint32_t SamplePerSec;   //サンプリングレート
    uint32_t AvgBytesPerSec; //SamlpesPerSec*Channels*BitsPerSample/8
    uint16_t BlockAlign;     //ブロック境界　ステレオ16bitなら、16bit*2 = 32bit = 4byte
    uint16_t BitPerSample;   //量子化ビット数
    uint32_t PcmSize;        //データ部サイズ
} PCM_INFO;

class SoundContainer
{
protected:
    string filename;
    ifstream stream;
    vector<char> *buffer;    //バッファへのポインタ
    PCM_INFO info;

public:
    SoundContainer();
    //~SoundContainer();
    virtual int read(char *buf, size_t sample_num);
    virtual void reload();
    virtual void setParam();
    PCM_INFO getPcmInfo();
    virtual const char *getFilename();
};

#endif // SOUNDCONTAINER_H
