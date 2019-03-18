#pragma once
#include <windows.h>
#include <stdio.h>
#include <atlstr.h>
class Shape
{
public:
	float _x;
	float _y;
	Shape(float x, float y) : _x(x), _y(y) {};
	~Shape() {};

	virtual void Draw(const HDC hdc, RECT rect) const;
};