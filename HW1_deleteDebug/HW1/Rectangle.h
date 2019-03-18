#pragma once
#include "Shape.h"
class _Rectangle : public Shape
{
public:
	float _width;
	float _height;
	_Rectangle(float x, float y, float w, float h) : Shape(x, y), _width(w), _height(h) {};
	~_Rectangle() {};

	void Draw(const HDC hdc, RECT rect) const;
};