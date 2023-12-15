#include "cPeople.h"

cPeople::cPeople()
{
	height = 102;
	width = 47;
	mode = "D";
	x = 0;
	y = 795;
}
void cPeople::assignX(int X)
{
	x = X;
}
void cPeople::assignY(int Y)
{
	y = Y;
}

int cPeople::getX()
{
	return x;
}

int cPeople::getY()
{
	return y;
}
int cPeople::getHeight()
{
	return height;
}
int cPeople::getWidth()
{
	return width;
}


int cPeople::getFrame() {
    return frame;
}
void cPeople::newFrame() {

    frame += 1;
    if (frame == 8) {
        frame = 1;
    }
}
void cPeople::setFrame(int x) {
    frame = x;
}
string cPeople::getMode() {
    return mode;
}
void cPeople::setMode(string a) {
    mode = a;
}
