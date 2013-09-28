#pragma once

#include <vector>
#include "element.h"


////////////////////////////////////////////////////////
class Composite:
    public Element
{
public:
	Composite();
    Composite& add(Element &element);
    
    virtual void draw();

	virtual void update(Element &element) = 0;
	virtual void nextChild(Element &element) = 0;

protected:
	std::vector<Element*> children;
};



////////////////////////////////////////////////////////
class HorizontalC:
    public Composite
{
public:
	HorizontalC();
	void update(Element &element);
    void nextChild(Element &element);
private:
	int _elemHeight;
};

////////////////////////////////////////////////////////
class VerticalC:
    public Composite
{
public:
	VerticalC();
	void update(Element &element);
    void nextChild(Element &element);
private:
	int _elemWidth;
};