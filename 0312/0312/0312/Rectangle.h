#pragma once
#include "Shape.h"
class Rectangle : public Shape
{
private:

public:
	float _width;
	float _height;
	//Rectangle(float x, float y, float w, float h) : Shape(x, y),
	//	_width(w), _height(h) {};
	Rectangle(float x, float y, float w=0, float h=0) : Shape(x, y)	
	{
		_width = w;
		_height = h;
	};
	~Rectangle();
	const void Draw();
};