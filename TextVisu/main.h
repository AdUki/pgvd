/*
** "THE BEER-WARE LICENSE" (Revision 42):
** <simon.mikuda@gmail.com> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#pragma once

#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#define DRAW_TEXT
#define BOX_3D
#define SCALE 0.002

class Element;

#ifdef BOX_3D
#	define HORIZONTAL_COLOR(order) SET_COLOR( 1.0, 0.5 + order*0.1, 0.5 + order*0.1, 1.0 )
#	define VERTICAL_COLOR(order)   SET_COLOR( 0.5 + order*0.1, 1.0 , 0.5 + order*0.1, 1.0 )
#	define TEXT_BG_COLOR(order)    SET_COLOR( 0.1, 0.1, 0.9, 1.0 )
#else
#	define HORIZONTAL_COLOR(order) SET_COLOR( 1.0, 0.5, 0.5, 0.6 )
#	define VERTICAL_COLOR(order)   SET_COLOR( 0.5, 1.0 , 0.5, 0.6 )
#	define TEXT_BG_COLOR(order)    SET_COLOR( 0.1, 0.1, 0.9, 1.0 )
#endif


extern unsigned long long globalTime;
extern GLfloat globalDepth;
extern unsigned globalSize;

extern void DrawRectangle(int width, int height, GLfloat depth);
extern void DrawRotatingLetter(char letter);
extern void DrawLetter(char letter);
extern void DrawBox(int width, int height, GLfloat depth);