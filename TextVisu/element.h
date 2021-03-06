/*
** "THE BEER-WARE LICENSE" (Revision 42):
** <simon.mikuda@gmail.com> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#pragma once

#include <string>

#define SET_COLOR(r,g,b,a) color[0] = r; color[1] = g; color[2] = b; color[3] = a;

////////////////////////////////////////////////////////
class Element
{
public:
	GLfloat color[4];

    virtual void draw() = 0;

    int getHeight() { return _height; }
    int getWidth() { return _width; }

protected:
	int _height;
    int _width;
    int _padding;
};

////////////////////////////////////////////////////////
class TextE:
    public Element
{
public:
    TextE(int width, const std::string &text);
    virtual void draw();
private:
    void newLine();

    std::string _text;
    int _padding;
};