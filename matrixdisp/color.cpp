#include "color.h"

Color::Color()
	: r(0),g(0),b(0)
{
}

Color::Color(unsigned char r,unsigned char g,unsigned char b)
	: r(r),g(g),b(b)
{
}

void Color::setColor(unsigned char r,unsigned char g,unsigned char b){
	this->r=r;
	this->g=g;
	this->b=b;
}

unsigned char Color::getElement(int rgb){
    switch(rgb){
    case 0:
        return r;
    case 1:
        return g;
    case 2:
        return b;
    default:
        return r;
    }
    return 0;
}

bool Color::operator == (const Color &c1){
        return (r==c1.r && g==c1.g && b==c1.b);
}

bool Color::operator != (const Color &c1){
		return !(r==c1.r && g==c1.g && b==c1.b);
}

Color &Color::operator =(const Color &c1){
    r = c1.r;
    g = c1.g;
    b = c1.b;
    return *this;
}
