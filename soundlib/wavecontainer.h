#ifndef WAVECONTAINER_H
#define WAVECONTAINER_H

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include "soundcontainer.h"
using namespace std;

typedef struct tagWaveHeader{
    //RIFF chunk
    char RIFF[4];           //'RIFF'の４文字
    uint32_t RiffChunkSize;  //総ファイルサイズ-8 (Byte)

    char WAVE[4];           //'WAVE'の４文字

    //format chunk
    char fmt_[4];           //'fmt 'の4文字
    uint32_t FormatSize;     //フォーマットサイズ　デフォルト値16

    //WaveFormatEx
    uint16_t FormatTag;      //フォーマットコード　非圧縮のＰＣＭフォーマットは1
    uint16_t Channels;       //チャンネル数　モノラルは1、ステレオは2
    uint32_t SamplePerSec;   //サンプリングレート
    uint32_t AvgBytesPerSec; //SamlpesPerSec*Channels*BitsPerSample/8
    uint16_t BlockAlign;     //ブロック境界　ステレオ16bitなら、16bit*2 = 32bit = 4byte
    uint16_t BitPerSample;   //量子化ビット数

    //data chunk
    char data[4];           //'data'の4文字
    uint32_t DataChunkSize;  //総ファイルサイズ-126(Byte)

} WaveHeader;


class WaveContainer : public SoundContainer
{
private:
    WaveHeader header;
public:
    WaveContainer(const char *filename);
    ~WaveContainer();
    int read(char *buf, size_t sample_num);
    void reload();
    int DecodeHeader(ifstream *stream, WaveHeader *out);

};


#endif // WAVECONTAINER_H
