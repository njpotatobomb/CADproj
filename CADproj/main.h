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



//in pixels
//horizontal=width=x,vertical=height=y
#define SCREENWIDTH (1280)
#define SCREENHEIGHT (720)
#define CANVASWIDTH (1280)
#define CANVASHEIGHT (720)



void init();
void refreshScreen();



#endif
