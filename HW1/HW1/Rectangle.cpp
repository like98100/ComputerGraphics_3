#include "Rectangle.h"
void _Rectangle::Draw(const HDC hdc, RECT rect) const
{
	//cout << "[RECTANGLE] position = ( " << _x << ", " << _y << " ), size = ( " <<
	//	_width << ", " << _height << " )" << endl;
	//DrawText(hdc, "[RECTANGLE] position = ( ", -1, &rect,
	//	DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	/*char buff_x[100], buff_y[100], buff_w[100], buff_h[100];
	sprintf_s(buff_x, "%.0f", _x);
	LPCTSTR x = buff_x;
	sprintf_s(buff_y, "%.0f", _y);
	LPCTSTR y = buff_y;
	sprintf_s(buff_w, "%.0f", _width);
	LPCTSTR w = buff_w;
	sprintf_s(buff_h, "%.0f", _height);
	LPCTSTR h = buff_h;
	LPCTSTR comma = TEXT(", ");
	LPCTSTR size = TEXT("size = ");
	LPCTSTR start = TEXT("( ");
	LPCTSTR end = TEXT(" )");
	LPCTSTR str = TEXT("[RECTANGLE] Position = ( ");*/
	//DrawText(hdc, "[RECTANGLE] Position = ( _x, _y ) Size = ( _width, _height )", -1, &rect,
	//	DT_SINGLELINE);

	CString rectangle;
	rectangle.Format(_T("[RECTANGLE] position = (%.0f, %.0f) size = (%.0f, %.0f)"), _x, _y, _width, _height);
	DrawText(hdc, rectangle, -1, &rect,
		DT_SINGLELINE);

}