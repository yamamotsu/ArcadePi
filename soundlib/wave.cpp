#include <iostream>
#include <alsa/asoundlib.h>
#include <fstream>
#include <stdint.h>
using namespace std;

#include "wave.h"

Wave::Wave(char *filename)
{
    int i;
    this->filename = filename;
    stream.open(filename,ios::binary);
    errf=0;
    latency = 50000; //レイテンシを50msにする(コピペ)
    if(DecodeHeader(&stream,&header)){
        stat=1;

        data.resize(header.DataChunkSize);
        stream.read(&data[0],header.DataChunkSize);

        if(!stream==0){
            //PCMストリームを開く
            snd_pcm_open(&handle,DEF_ALSA_DEVICE,SND_PCM_STREAM_PLAYBACK,0);
            //出力パラメータを指定
            snd_pcm_set_params(handle,
                               SND_PCM_FORMAT_S16,              //符号付き16ビット
                               SND_PCM_ACCESS_RW_INTERLEAVED,   //インターリーブで動作(コピペ)
                               header.SamplePerSec,
                               header.Channels,
                               0,                               //ソフトリサンプリングを禁止
                               latency
                               );

        }

        stream.close();
    }
}

Wave::~Wave(){
}

int Wave::DecodeHeader(const ifstream *stream, WaveHeader *out){
    //int i;

    stream->read(out->RIFF,4);
    stream->read(&out->RiffChunkSize,4);
    stream->read(out->WAVE,4);
    stream->read(out->fmt_,4);
    stream->read(&out->FormatSize,4);
    stream->read(&out->FormatTag,2);
    stream->read(&out->Channels,2);
    stream->read(&out->SamplePerSec,4);
    stream->read(&out->AvgBytesPerSec,4);
    stream->read(&out->BlockAlign,2);
    stream->read(&out->BitPerSample,2);
    stream->read(out->data,4);
    stream->read(&out->DataChunkSize,4);

    if(!stream)
        return 0;

    return 1;
}
