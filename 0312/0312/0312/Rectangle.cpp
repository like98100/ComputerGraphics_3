#include "Rectangle.h"

void Rectangle::Draw() const
{
	cout << "[RECTANGLE] position = ( " << _x << ", " << _y << " ), size = ( " <<
		 _width << ", " << _height << " )" << endl;
}