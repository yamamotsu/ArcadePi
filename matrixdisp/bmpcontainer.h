#ifndef BMPCONTAINER_H
#define BMPCONTAINER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

#include "color.h"
#include "matrixdisp.h"
#include "virtualdisp.h"

#define BITMAP_MAX_SIZE     10000000


typedef struct tagBMPFileHeader{
    char bf_type[2];                //file type
    unsigned long bf_size;          //file size
    unsigned short bf_reserved1;    //reserved 1
    unsigned short bf_reserved2;    //reserved 2
    unsigned long bf_offset;        //data offset
} BMPFileHeader;

typedef struct tagBMPInfoHeader{
    unsigned long bi_size;          //bitmap info size
    long bi_width;                  //bitmap width
    long bi_height;                 //bitmap height
    unsigned short bi_planes;       //planes (always 1)
    unsigned short bi_bits;         //color bits
    unsigned long bi_compression;   //compression type(0~3)
    unsigned long bi_size_image;    //image size(Byte)
    long bi_x_dpm;                  //horizontal dot per meter
    long bi_y_dpm;                  //vertical dot per meter
    unsigned long bi_color_used;    //color used num
    unsigned long bi_color_important;//important color num
} BMPInfoHeader;

class BmpContainer
{
private:
    Color ***buf;
    BMPFileHeader fileheader;
    BMPInfoHeader infoheader;
    virtualDisp *canvas;
    string filename;
    ifstream fs;

    int cf_x,cf_y;
    int cf_width,cf_height;

    int DecodeHeader();
    int load();
    void digitalize();
public:
	BmpContainer();
	BmpContainer(const char *filename, virtualDisp *canvas);
    ~BmpContainer();
	void loadBMP(const char *filename);

    static long LEToLong(void *buf);
    static short LEToShort(void *buf);
    void setCutFrame(int x0,int y0,int width,int height);
    void put(int x,int y);
	void put(virtualDisp *canvas,int x,int y);
};

#endif // BMPCONTAINER_H
