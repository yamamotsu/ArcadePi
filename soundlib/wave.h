#ifndef WAVE_H
#define WAVE_H

#define WAVE_HEADER_SIZE    126
#define DEF_ALSA_DEVICE     "plughw:0,0"

//typedef unsigned char BYTE;
//typedef unsigned char *BYTES,BUFFER;
//typedef unsigned long   BYTE_4;
typedef struct tagWaveHeader{
    //RIFF chunk
    char RIFF[4];           //'RIFF'の４文字
    uint32_t RiffChunkSize;  //総ファイルサイズ-8 (byte)

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
    uint32_t DataChunkSize;  //総ファイルサイズ-126

} WaveHeader;

class Wave
{
private:
    int stat;
    int errf;
    ifstream stream;
    string filename;
    vector<unsigned char> data;
    WaveHeader header;
    snd_pcm_t *handle;
    uint32_t latency;
public:
    Wave(char *filename);
    static int DecodeHeader(const ifstream *stream,WaveHeader *out);
    //static int CheckHeader(const WaveHeader *header);
    ~Wave();
};

#endif // WAVE_H
