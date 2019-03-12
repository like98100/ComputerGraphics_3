#pragma once
#include <iostream>
using namespace std;
class Shape
{
private:
	
public:
	float _x;
	float _y;
	//Shape(float x, float y) : _x(x), _y(y) {};
	Shape(float x=0, float y=0)
	{
		_x = x; _y = y;
	};
	~Shape();
	virtual const void Draw();
};
