#ifndef __MAIN_H
#define __MAIN_H



#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <tchar.h>
#include <string>
#include <atltypes.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <regex>





//in pixels
//horizontal=width=x,vertical=height=y
#define TEXTHEIGHT (24)
#define OUTLINEWIDTH (150)
#define CANVASWIDTH (1280)
#define CANVASHEIGHT (720)
#define SCREENWIDTH (CANVASWIDTH+OUTLINEWIDTH+1)
#define SCREENHEIGHT (CANVASHEIGHT+TEXTHEIGHT*2+2)




void init();
void refreshScreen();
void moveMouseTo(int px,int py);
void save();
void open();

#endif
