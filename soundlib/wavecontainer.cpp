#include <iostream>
#include <alsa/asoundlib.h>
#include <time.h>
#include <fstream>
#include <stdint.h>
#include <vector>
using namespace std;

#include "soundcontainer.h"
#include "wavecontainer.h"

WaveContainer::WaveContainer(const char *filename)
{
    int errf;
    this->filename = filename;
    stream.open(filename,ios::in|ios::binary);
    errf = !DecodeHeader(&stream,&header);

    if(!errf){
        //debug
        cout << "filename:" << filename << endl;
        cout << "bit:" << to_string(header.BitPerSample) << endl;
        cout << "sampling rate:" << to_string(header.SamplePerSec) << endl;
        cout << "channels:" << to_string(header.Channels) << endl;
        cout << "BlockAlign:" << to_string(header.BlockAlign) << endl;
        cout << "file size:" << to_string(header.DataChunkSize + 126) << "Bytes" << endl;

        info.Channels = header.Channels;
        info.SamplePerSec = header.SamplePerSec;
        info.AvgBytesPerSec = header.AvgBytesPerSec;
        info.BlockAlign = header.BlockAlign;
        info.BitPerSample = header.BitPerSample;
        info.PcmSize = header.DataChunkSize;
    }else{
        cout << filename << ":load error" << endl;
    }
}

WaveContainer::~WaveContainer(){
}

int WaveContainer::read(char *buf, size_t sample_num){
	//cout << "called read" << endl;
    return (!stream.read(buf,sample_num*header.BlockAlign));
}

void WaveContainer::reload(){
    //ヘッダファイルサイズ:126Byte
    stream.clear();
    if(!stream.seekg(126,ios::beg)){
        cout << "seek failed" << endl;
    }
}

int WaveContainer::DecodeHeader(ifstream *stream, WaveHeader *out){
    //int i;


    stream->read((char *)out->RIFF,4);
    stream->read((char *)&out->RiffChunkSize,4);
    stream->read((char *)out->WAVE,4);
    stream->read((char *)out->fmt_,4);
    stream->read((char *)&out->FormatSize,4);
    stream->read((char *)&out->FormatTag,2);
    stream->read((char *)&out->Channels,2);
    stream->read((char *)&out->SamplePerSec,4);
    stream->read((char *)&out->AvgBytesPerSec,4);
    stream->read((char *)&out->BlockAlign,2);
    stream->read((char *)&out->BitPerSample,2);
    stream->read((char *)out->data,4);
    stream->read((char *)&out->DataChunkSize,4);

    if(!stream)
        return 0;

    return 1;
}
