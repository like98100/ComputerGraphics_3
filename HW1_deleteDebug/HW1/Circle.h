#pragma once
#include "Shape.h"
class _Circle : public Shape
{
public:
	float _radius;
	_Circle(float x, float y, float r) : Shape(x, y), _radius(r) {};
	~_Circle() {};

	void Draw(const HDC hdc, RECT rect) const;
};