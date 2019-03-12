#pragma once
#include "Shape.h"
class Rectangle : public Shape
{
public:
	float _width;
	float _height;
	Rectangle(float x, float y, float w, float h) : Shape(x, y), _width(w), _height(h) {};
	~Rectangle() {};

	void Draw() const;
};