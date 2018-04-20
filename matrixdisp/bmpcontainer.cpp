#include <iostream>
#include <fstream>
#include "string"
#include "color.h"
#include "virtualdisp.h"

using namespace std;

#include "bmpcontainer.h"
#define _LE_LONG(PTR) (*PTR|(*(PTR+1)<<8)|(*(PTR+2)<<16)|(*(PTR+3)<<24))
#define _LE_SHORT(PTR) (*PTR|(*(PTR+1)<<8))

BmpContainer::BmpContainer()
{
	buf = nullptr;
}

BmpContainer::BmpContainer(const char *filename, virtualDisp *canvas)
{
    int i,j;

    this->canvas = canvas;
    this->filename = filename;
    fs.open(filename,ios::in|ios::binary);

    if(!fs){
	    cout << "Unable to open bmp file." <<endl;
	    return;
    }
    DecodeHeader();

    //bitmap チェックシーケンスは省略　めんどいので
    cout << "decoded" << endl;

    buf = nullptr;
    if(infoheader.bi_width*infoheader.bi_height*3 < BITMAP_MAX_SIZE){
        buf = new Color**[infoheader.bi_width];
        for(i=0;i<infoheader.bi_width;i++){
            buf[i] = new Color*[infoheader.bi_height];
            for(j=0;j<infoheader.bi_height;j++){
                buf[i][j] = new Color();
            }
        }

        load();
        digitalize();
    }else{
        cout << "error: too big file" << endl;
    }

}

BmpContainer::~BmpContainer(){
    cout << "Bitmap Container shutdown..." << endl;
    if(buf!=nullptr){
        int i,j;
        for(i=0;i<infoheader.bi_width;i++){
            for(j=0;j<infoheader.bi_height;j++){
                delete buf[i][j];
            }
            delete buf[i];
        }
        delete buf;
    }
}

void BmpContainer::loadBMP(const char *filename)
{
	int i,j;
    this->filename = filename;
    fs.open(filename,ios::in|ios::binary);

    if(!fs){
	    cout << "Unable to open bmp file." <<endl;
	    return;
    }
    DecodeHeader();

    //bitmap チェックシーケンスは省略　めんどいので
    cout << "decoded" << endl;

    buf = nullptr;
    if(infoheader.bi_width*infoheader.bi_height*3 < BITMAP_MAX_SIZE){
        buf = new Color**[infoheader.bi_width];
        for(i=0;i<infoheader.bi_width;i++){
            buf[i] = new Color*[infoheader.bi_height];
            for(j=0;j<infoheader.bi_height;j++){
                buf[i][j] = new Color();
            }
        }

        load();
        digitalize();
    }else{
        cout << "error: too big file" << endl;
    }
}


int BmpContainer::load(){
    int i,j;
    //int pads = 4 - (infoheader.bi_width*3)%4;
    //cout << "pads:" << to_string(pads) << endl;

    fs.clear();
    fs.seekg(fileheader.bf_offset,ios::beg);
    for(i=0;i<infoheader.bi_height;i++){
        for(j=0;j<infoheader.bi_width;j++){
            fs.read((char *)&(buf[j][infoheader.bi_height-i-1]->b),1);
            fs.read((char *)&(buf[j][infoheader.bi_height-i-1]->g),1);
            fs.read((char *)&(buf[j][infoheader.bi_height-i-1]->r),1);
        }
        //画像データの1行データは4byte単位でそろえられているので余る部分にパッドが入っているので捨てる.
        //なんかいらんっぽい
        //fs.seekg(pads,ios_base::cur);
    }

    return 1;
}

void BmpContainer::digitalize(){
    int i,j;
    for(i=0;i<infoheader.bi_width;i++){
        for(j=0;j<infoheader.bi_height;j++){
            buf[i][j]->r = (buf[i][j]->r > 127 ? 1:0);
            buf[i][j]->g = (buf[i][j]->g > 127 ? 1:0);
            buf[i][j]->b = (buf[i][j]->b > 127 ? 1:0);
        }
    }
}

int BmpContainer::DecodeHeader(){
	int i;
	char fhTemp[14];
	char ihTemp[40];
	fs.read((char *)&fhTemp,14);
	fs.read((char *)&ihTemp,40);

	fileheader.bf_type[0] = fhTemp[0];
	fileheader.bf_type[1] = fhTemp[1];
	fileheader.bf_size = _LE_LONG(&fhTemp[2]);
	fileheader.bf_reserved1 = _LE_SHORT(&fhTemp[6]);
	fileheader.bf_reserved2 = _LE_SHORT(&fhTemp[8]);
	fileheader.bf_offset = _LE_LONG(&fhTemp[10]);

	infoheader.bi_size = _LE_LONG(&ihTemp[0]);
	infoheader.bi_width = _LE_LONG(&ihTemp[4]);
	infoheader.bi_height = _LE_LONG(&ihTemp[8]);
	infoheader.bi_planes = _LE_SHORT(&ihTemp[12]);
	infoheader.bi_bits = _LE_SHORT(&ihTemp[14]);
	infoheader.bi_compression = _LE_LONG(&ihTemp[16]);
	infoheader.bi_size_image = _LE_LONG(&ihTemp[20]);


/*
    fs.read((char *)&fileheader.bf_type,2);
    fs.read((char *)&fileheader.bf_size,4);
    fs.read((char *)&fileheader.bf_reserved1,2);
    fs.read((char *)&fileheader.bf_reserved2,2);
    fs.read((char *)&fileheader.bf_offset,4);

    fs.read((char *)&infoheader.bi_size,4);
    fs.read((char *)&infoheader.bi_width,4);
    fs.read((char *)&infoheader.bi_height,4);
    fs.read((char *)&infoheader.bi_planes,2);
    fs.read((char *)&infoheader.bi_bits,2);
    fs.read((char *)&infoheader.bi_compression,4);
    fs.read((char *)&infoheader.bi_size_image,4);
    fs.read((char *)&infoheader.bi_x_dpm,4);
    fs.read((char *)&infoheader.bi_y_dpm,4);
    fs.read((char *)&infoheader.bi_color_used,4);
    fs.read((char *)&infoheader.bi_color_important,4);
*/

    cout << "filename:" << filename.data() << endl;
    cout << "BMPTYPE:" << fileheader.bf_type << endl;
    cout << "filesize:" << to_string(fileheader.bf_size) << " Byte" << endl;
    cout << "color bits:" << to_string(infoheader.bi_bits) << endl;
    cout << "width:" << to_string(infoheader.bi_width) << endl;
    cout << "height:" << to_string(infoheader.bi_height) << endl;

    if(!fs){
        return 0;
    }
    return 1;

}

void BmpContainer::setCutFrame(int x0, int y0, int width, int height){
    cf_x = x0;
    cf_y = y0;
    cf_width = width;
    cf_height = height;
}

void BmpContainer::put(int x, int y){
    int i,j;
    for(i=0;i<cf_width;i++){
        for(j=0;j<cf_height;j++){
            canvas->drawPoint(x+i,y+j,*(buf[cf_x+i][cf_y+j]));
        }
    }
}

void BmpContainer::put(virtualDisp *canvas,int x,int y)
{
	int i,j;
    for(i=0;i<cf_width;i++){
        for(j=0;j<cf_height;j++){
            canvas->drawPoint(x+i,y+j,*(buf[cf_x+i][cf_y+j]));
        }
    }
}
