#ifndef MATRIXDISP_H
#define MATRIXDISP_H

#include <thread>
#include <mutex>

class Matrixdisp
{
private:
    int endf;
    Color dot[12][16];
    std::thread *hnd;
    std::mutex *mtx;
    void serialout(int drawpins);
    void routine(void);
    void display_routine();
    //debug
    //int debug_f;
    

    friend class virtualDisp;
    friend void routine_start(Matrixdisp *ptr);
    //void show_singlecolor(const Color &color);
    //PwmDriver *pwmRed;
    //PwmDriver *pwmGreen;
    //PwmDriver *pwmBlue;
public:
    Matrixdisp();
    ~Matrixdisp();
    //void serialout(int drawpins);
    //virtualDisp *canvas;
    int write(int x,int y,const Color &color);
    int write_rowline(int x,const Color &color,int y0,int y1);
    void clear();
};

#endif // MATRIXDISP_H
