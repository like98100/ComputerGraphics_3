#pragma once
#include <iostream>
using namespace std;
class Shape
{
public:
	float _x;
	float _y;
	Shape(float x, float y) : _x(x), _y(y) {};
	~Shape() {};

	virtual void Draw() const;
};