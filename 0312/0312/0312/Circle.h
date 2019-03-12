#pragma once
#include "Shape.h"
class Circle : public Shape
{
public:
	float _radius;
	Circle(float x, float y, float r) : Shape(x, y), _radius(r) {};
	~Circle() {};

	void Draw() const;
};