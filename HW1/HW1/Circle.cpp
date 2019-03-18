#include "Circle.h"

void _Circle::Draw(const HDC hdc, RECT rect) const
{
	//cout << "[CIRCLE] position = ( " << _x << ", " << _y << " ), radius = " <<
	//	_radius << endl;

	/*DrawText(hdc, "[CIRCLE] Position = ( _x, _y ) Radius = _radius", -1, &rect,
		DT_SINGLELINE);*/

	CString circle;
	circle.Format(_T("[RECTANGLE] position = (%.0f, %.0f) radius = %.0f"), _x, _y, _radius);
	DrawText(hdc, circle, -1, &rect,
		DT_SINGLELINE);
}