#pragma once

#include "cObject.h"
#include "Header.h"
#include "Input.h"

class cPeople
{
    float x, y; // up-left point
    int height, width; //
    int frame; //every movement has 8 frames
    string mode; //get mode (up, down, left, right) to read the right image
    //an people image file name contain: mode+frame
public:
   
    cPeople();
    void assignX(int); 
    void assignY(int);
    int getX();
    int getY();
    int getHeight();
    int getWidth();
    int getFrame();
    void newFrame();
    void setFrame(int x); 
    string getMode();
    void setMode(string a);
    
};

