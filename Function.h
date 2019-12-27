#ifndef __XINXIGUANLI__
#define __XINXIGUANLI__
#include"DATA.h"


//static int Button_Status;

HWND CreateButton(TCHAR *szButtonName, HWND hwnd, int button_id);
HWND CreateTag(TCHAR *szTagName, HWND hwnd, int static_id);
HWND CreateEdit(HWND hwnd, int edit_id);
HWND CreateIputBox(TCHAR *szWindowClassName, TCHAR *szWindowName,HWND hwnd);
BOOL StrNull(TCHAR *szBuffer);//判断字符串是否为空
BOOL StreQuality(TCHAR *str1, TCHAR *str2);//判断字符串是否正确
void MoveSite(HWND hwnd,int x, int y, int button_x, int button_y);

HWND CreateButton(TCHAR *szButtonName,HWND hwnd,int button_id)
{

	return CreateWindow(TEXT("button"), szButtonName,
		WS_CHILD | WS_VISIBLE | BS_CENTER | BS_PUSHLIKE, 0, 0, 0, 0, hwnd, (HMENU)button_id,
		((HINSTANCE)(GetWindowLong(hwnd, GWL_HINSTANCE))), NULL);
}
HWND CreateTag(TCHAR *szTagName, HWND hwnd, int static_id)
{
	return CreateWindow(TEXT("static"), szTagName,
		WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 0, 0, 0, hwnd, (HMENU)static_id,
		((HINSTANCE)(GetWindowLong(hwnd, GWL_HINSTANCE))), NULL);
}
HWND CreateEdit(HWND hwnd, int edit_id)
{
	return CreateWindow(TEXT("edit"), NULL,
		WS_CHILD | WS_VISIBLE | ES_LEFT, 0, 0, 0, 0, hwnd, (HMENU)edit_id,
		((HINSTANCE)(GetWindowLong(hwnd, GWL_HINSTANCE))), NULL);
}
HWND CreateBox(TCHAR *szWindowClassName, TCHAR *szWindowName, HWND hwnd)
{
	return CreateWindow(szWindowClassName, szWindowName,
		WS_OVERLAPPEDWINDOW, 0, 0, 0, 0,
		hwnd, NULL,
		((HINSTANCE)(GetWindowLong(hwnd, GWL_HINSTANCE))), NULL);
}
void MoveSite(HWND hwnd, int x, int y, int button_x, int button_y)
{
	MoveWindow(hwnd, x, y, button_x, button_y, FALSE);
}
BOOL StrNull(TCHAR *szBuffer)
{
	if (lstrlen(szBuffer) <= 0)
		return FALSE;
	return TRUE;
}

BOOL StreQuality(TCHAR *str1, TCHAR *str2)
{
	while ((*str2) != '\0')
	{
		if ((*str1) != (*str2))
			return FALSE;
		str2++;
		str1++;
	}
	if (lstrlen(str1) == lstrlen(str2))
		return TRUE;
	else
		return FALSE;
}


#endif
