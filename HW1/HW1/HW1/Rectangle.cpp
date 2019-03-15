#include "Rectangle.h"

void _Rectangle::Draw() const
{
	cout << "[RECTANGLE] position = ( " << _x << ", " << _y << " ), size = ( " <<
		 _width << ", " << _height << " )" << endl;
}