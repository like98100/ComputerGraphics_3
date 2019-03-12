#pragma once
#include "Shape.h"
class Circle : public Shape
{
private:
	
public:
	float _radius;
	//Circle(float x, float y, float r) : Shape(x, y), _radius(r) {};
	Circle(float x, float y, float r=0) : Shape(x, y) 
	{
		_radius = r;
	};
	~Circle();
	const void Draw();
};