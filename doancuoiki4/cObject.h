#pragma once
#include"Header.h"

class cObject
{
protected:
    float x, y; //top-left point
    int width, height;
    string filename;
    //an object image file name contain: object+direction but direction is control by the lane class
public:
    cObject() {
        x = y = 0;
        width = height = 1;
        filename = "";
    };
   
    void assignX(int); 
    void assignY(int);
    void assignHeight(int); 
    void assignWidth(int);
    float getX(); 
    float getY();
    int getWidth();
    int getHeight();
    virtual string getObjectFileName() = 0;
};

