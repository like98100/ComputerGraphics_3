#include "Shape.h"
void Shape::Draw(const HDC hdc, RECT rect) const
{
	//cout << "[SHAPE] position = ( " << _x << ", " << _y << " )" << endl;

	/*DrawText(hdc, "[SHAPE] position = ( ", -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);*/
		/*char buff_x[100], buff_y[100];
		sprintf_s(buff_x, "%.0f", _x);
		LPCTSTR x = buff_x;
		sprintf_s(buff_y, "%.0f", _y);
		LPCTSTR y = buff_y;
		LPCTSTR comma = TEXT(", ");
		LPCTSTR end = TEXT(" )");
		LPCTSTR str = TEXT("[SHAPE] Position = ( "), TEXT(x), TEXT(comma), TEXT(y), TEXT(end);*/

		//DrawText(hdc, "[SHAPE] Position = ( _x, _y )", -1, &rect,
		//	DT_SINGLELINE);

	CString shape;
	shape.Format(_T("[SHAPE] position = (%.0f, %.0f)"), _x, _y);
	DrawText(hdc, shape, -1, &rect,
		DT_SINGLELINE);
}