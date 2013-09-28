#include "main.h"
#include "composite.h"
#include <iostream>

unsigned currentDepth = 0;

////////////////////////////////////////////////////////
// Composite class
//
Composite::Composite()
{
	_padding = 100;
	_width = 0;
	_height = 0;
	SET_COLOR(1,0.5,0.5,0.3);
}

Composite& Composite::add(Element &element)
{
	update(element);
    children.push_back(&element);
    return *this;
}

void Composite::draw()
{
	glPushMatrix();
	for (int i = 0; i < children.size(); i++)
    {
    	if (currentDepth < globalSize) {
	    	// Draw big bounding box
	    	glPushMatrix();
			    glColor4f(color[0], color[1], color[2], color[3]);
			    glTranslatef(_padding*SCALE, -_padding*SCALE, 0);
			    
			    #ifdef BOX_3D
			    	DrawBox(children[i]->getWidth(), -children[i]->getHeight(), globalDepth);
			    #else
			    	DrawRectangle(children[i]->getWidth(), -children[i]->getHeight(), globalDepth);
			    #endif
		    
		    glPopMatrix();
	    }


	    // Draw children
	    glPushMatrix();
	    	currentDepth++;
		    if (currentDepth <= globalSize) 
		    	glTranslatef(_padding*SCALE, -_padding*SCALE, globalDepth);
	        children[i]->draw();
	        currentDepth--;
        glPopMatrix();

        nextChild(*children[i]);
    }
    glPopMatrix();
}

////////////////////////////////////////////////////////
// HorizontalC class
//
HorizontalC::HorizontalC() : 
	Composite(),
	_elemHeight(0)
{
	HORIZONTAL_COLOR(0)
}

void HorizontalC::update(Element &element)
{
    if (_elemHeight < element.getHeight()) _elemHeight = element.getHeight();

    _width += element.getWidth() + 2*_padding;
    _height = 2*_padding + _elemHeight;
}

void HorizontalC::nextChild(Element &element)
{
	glTranslatef((2*_padding + element.getWidth()) * SCALE, 0, 0);
}

////////////////////////////////////////////////////////
// VerticalC class
//
VerticalC::VerticalC() : 
	Composite(),
	_elemWidth(0)
{
	_height = -2*_padding;
	VERTICAL_COLOR(0)
}

void VerticalC::update(Element &element)
{
    if (_elemWidth < element.getWidth()) _elemWidth = element.getWidth();

    _height += element.getHeight() + 3*_padding;
    _width = 2*_padding + _elemWidth;
}

void VerticalC::nextChild(Element &element)
{
	glTranslatef(0, -(2*_padding + element.getHeight()) * SCALE, 0);
}
