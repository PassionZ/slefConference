#pragma once

class CRightKeyUp
{
	public :
		CRightKeyUp() {};
		virtual HWND GetHwnd() = 0;
	virtual void OnRightKeyUp(CPoint point) = 0;
};