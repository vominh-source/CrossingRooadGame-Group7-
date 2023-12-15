#include "cObject.h"

void cObject::assignX(int X)
{
	x = X;
}
void cObject::assignY(int Y)
{
	y = Y;
}
void cObject::assignWidth(int W)
{
	width = W;
}
void cObject::assignHeight(int H)
{
	height = H;
}
float cObject::getX()
{
	return x;
}
float cObject::getY()
{
	return y;
}
int cObject::getWidth()
{
	return width;
}
int cObject::getHeight()
{
	return height;
}

