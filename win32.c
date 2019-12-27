#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include"Commodity_function.h"
#include"Function.h"
#pragma comment(lib,"User32.lib")
#pragma comment(lib, "winmm.lib")

LRESULT CALLBACK Wndproc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndproc(HWND, UINT, WPARAM, LPARAM);
//对话框消息循环
LRESULT CALLBACK inputproc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK delproc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK changeproc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Seekproc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK EditTab(HWND, UINT, WPARAM, LPARAM);//切换聚焦
LRESULT CALLBACK ALL_XianShi(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, PSTR szCmdLine, int iCmdshow)
{
	static TCHAR szAppName[] = TEXT("DengLu");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	/*初始化窗口类-----------------------------------------*/
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //窗口风格
	wndclass.lpfnWndProc = Wndproc;			  //窗口消息处理函数
	wndclass.cbClsExtra = 0;				  //窗口扩展
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hlnstance;			  //程序句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//程序图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//鼠标图标
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW + 2;//背景颜色
	wndclass.lpszMenuName = NULL; //菜单名字
	wndclass.lpszClassName = szAppName;//窗口类名
	/*------------------------------------------------------*/

	/*注册窗口类*/
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This Program requies windows 10!"), szAppName, MB_ICONERROR);
		return 0;
	}

	wndclass.lpfnWndProc = ChildWndproc;
	wndclass.lpszClassName = szChildNmae;//窗口类名
	RegisterClass(&wndclass);

	wndclass.lpszClassName = sz_input_win;
	wndclass.lpfnWndProc = inputproc;
	RegisterClass(&wndclass);

	wndclass.lpszClassName = sz_seek_win;
	wndclass.lpfnWndProc = Seekproc;
	RegisterClass(&wndclass);

	wndclass.lpszClassName = sz_del_win;
	wndclass.lpfnWndProc = delproc;
	RegisterClass(&wndclass);

	wndclass.lpszClassName = sz_change_win;
	wndclass.lpfnWndProc = changeproc;
	RegisterClass(&wndclass);

	wndclass.lpszClassName = sz_all_win;
	wndclass.lpfnWndProc = ALL_XianShi;
	RegisterClass(&wndclass);

	/*创建窗口类*/
	hwnd = CreateWindow(szAppName,	//窗口类名
		TEXT("登录系统"),	//窗口标题
		WS_OVERLAPPEDWINDOW,		//窗格格式
		CW_USEDEFAULT,              //水平位置
		CW_USEDEFAULT,				//垂直位置
		CW_USEDEFAULT,				//窗口宽度
		CW_USEDEFAULT,				//窗口高度
		NULL,						//父窗口句柄
		NULL,						//窗口菜单句柄
		hlnstance,					//程序实例句柄
		NULL,						//创建参数
		);
	ShowWindow(hwnd, iCmdshow);//指定窗口如何显示
	UpdateWindow(hwnd);		   //指示窗口自我更新

	while (GetMessage(&msg, NULL, 0, 0))//消息循环
	{
		TranslateMessage(&msg);//获取键盘消息转换为字符消息然后发送到消息队列中
		DispatchMessage(&msg); //将消息调度到窗口过程
	}






	return msg.wParam;
}
LRESULT CALLBACK Wndproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR szUserName[MAX_PATH], szPassWord[MAX_PATH];
	static RECT rect;//矩形结构
	HDC hdc;//设备句柄
	PAINTSTRUCT ps;//绘图结构
	int Length;
	Parent_window = hwnd;
	switch (message)
	{
	case WM_CREATE:

		Hedit_Name = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER, 0, 0, 0, 0, hwnd, (HMENU)EDIT_ID_NAME,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);
		Hedit_Password = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER | ES_PASSWORD, 0, 0, 0, 0, hwnd, (HMENU)EDIT_ID_NAME,
			((HINSTANCE)(GetWindowLong(hwnd, GWL_HINSTANCE))), NULL);
		Hstatic_Name = CreateWindow(TEXT("static"), NULL,
			WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 0, 0, 0, hwnd, (HMENU)STATIC_ID_NAME,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);
		Hstatic_Passwrod = CreateWindow(TEXT("static"), NULL,
			WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 0, 0, 0, hwnd, (HMENU)STATIC_ID_PASSWORD,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);
		Hbutton_Ok = CreateWindow(TEXT("button"), NULL,
			WS_CHILD | WS_VISIBLE | BS_CENTER | BS_PUSHLIKE, 0, 0, 0, 0, hwnd, (HMENU)BUTTON_ID,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);
		MoveWindow(hwnd, 500, 500, 400, 300, TRUE);
		upProc = SetWindowLong(Hedit_Name, GWL_WNDPROC, (WNDPROC)EditTab);
		SetWindowLong(Hedit_Password, GWL_WNDPROC, (WNDPROC)EditTab);
		SetWindowText(Hstatic_Name, TEXT("用户名:"));
		SetWindowText(Hstatic_Passwrod, TEXT("密码:"));
		SetWindowText(Hbutton_Ok, TEXT("登录"));
		Initialize_Commodity(&Xinxi);
		OpenFileRead();
		

		return 0;
	case WM_SIZE:
		rect.right = LOWORD(lParam);
		rect.bottom = HIWORD(lParam);
		rect.left = 0;
		rect.top = 0;

		MoveWindow(Hstatic_Name, rect.left + 30, rect.top + 50, rect.right / 7, rect.bottom / 12, FALSE);
		MoveWindow(Hstatic_Passwrod, rect.left + 30, rect.top + 100, rect.right / 7, rect.bottom / 12, FALSE);
		MoveWindow(Hedit_Name, rect.left + 100, rect.top + 50, rect.right / 2 + 30, rect.bottom / 12, FALSE);
		MoveWindow(Hedit_Password, rect.left + 100, rect.top + 100, rect.right / 2 + 30, rect.bottom / 12, FALSE);
		MoveWindow(Hbutton_Ok, rect.left + 230, rect.top + 170, rect.right / 3, rect.bottom / 12, FALSE);
		return 0;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			Length = GetWindowTextLength(Hedit_Name) + 1;
			GetWindowText(Hedit_Name, szUserName,Length);
			Length = GetWindowTextLength(Hedit_Password) + 1;
			GetWindowText(Hedit_Password, szPassWord, Length);

			if (StrNull(szUserName) && StrNull(szPassWord))
			{
				if (StreQuality(szUserName, sz_User_Name) && StreQuality(szPassWord, sz_PassWord))
				{
					MessageBox(hwnd, TEXT("登录成功!!"), TEXT("提示"), MB_OK);
					ShowWindow(hwnd, SW_HIDE);

				HchildHwnd = CreateWindow(szChildNmae, TEXT("商店管理系统"),
						WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
						hwnd, NULL,((HINSTANCE)(GetWindowLong(hwnd, GWL_HINSTANCE))), NULL);
					ShowWindow(HchildHwnd, SW_SHOW);
				}
				else
				{
					MessageBox(hwnd, TEXT("账号或者密码输入错误"), TEXT("提示"), MB_OK);
				}
			}
			else
			{
				MessageBox(hwnd, TEXT("账号或者密码没有输入"), TEXT("提示"), MB_OK);
			}

		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}


	return DefWindowProc(hwnd, message, wParam, lParam);
}
LRESULT CALLBACK EditTab(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_TAB)
			if (IdFocus == 0)
				IdFocus = 1;
			else if (IdFocus == 1)
				IdFocus = 0;
		if(wParam == VK_LBUTTON)
			if (IdFocus == 0)
				IdFocus = 1;
			else if (IdFocus == 1)
				IdFocus = 0;
		
	case WM_SETFOCUS:
		if (IdFocus == 0)
		{
			SetFocus(Hedit_Name);
		}
		else if (IdFocus == 1)
		{
			SetFocus(Hedit_Password);
		}
	}*/




	return CallWindowProc(upProc, hwnd, message, wParam, lParam);
}
LRESULT CALLBACK ChildWndproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		hButton_add = CreateButton(TEXT("添加商品"), hwnd, BUTTON_ID_ADD);
		hButton_del	= CreateButton(TEXT("删除商品"), hwnd, BUTTON_ID_DEL);
	    hbutton_change =CreateButton(TEXT("更改商品"), hwnd, BUTTON_ID_CHANGE);
		hbutton_examine	= CreateButton(TEXT("查找商品"), hwnd, BUTTON_ID_SEEK);
		hbutton_all = CreateButton(TEXT("全部商品"), hwnd, BUTTON_ID_ALL);

		hwnd_input_win = CreateBox(sz_input_win, TEXT("输入信息"), hwnd);
		hwnd_seek_win = CreateBox(sz_seek_win, TEXT("查找信息"), hwnd);
		hwnd_del_win = CreateBox(sz_del_win, TEXT("删除信息"), hwnd);
		hwnd_change_win = CreateBox(sz_change_win, TEXT("更改信息"), hwnd);
		hwnd_all_win = CreateBox(sz_all_win, TEXT("全部商品"), hwnd);

	case WM_SIZE:
		MoveWindow(hwnd, 400, 400, 450, 500,FALSE); 
		MoveSite(hButton_add, 70, 70, 100, 50);
		MoveSite(hButton_del, 270, 70, 100, 50);
		MoveSite(hbutton_change, 70, 270, 100, 50);
		MoveSite(hbutton_examine, 270,270, 100, 50);
		MoveSite(hbutton_all, 170, 170, 100, 50);
		return 0;

	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			if(LOWORD(wParam) == BUTTON_ID_ADD)
			{ 
				ShowWindow(hwnd, SW_HIDE);
				hwnd_input_win = CreateBox(sz_input_win, TEXT("输入信息"), hwnd);
				ShowWindow(hwnd_input_win, SW_SHOW);
			}
			else if(LOWORD(wParam) == BUTTON_ID_SEEK)
			{
				ShowWindow(hwnd, SW_HIDE);
				hwnd_seek_win = CreateBox(sz_seek_win, TEXT("查找信息"), hwnd);
				ShowWindow(hwnd_seek_win, SW_SHOW);
			}
			else if (LOWORD(wParam) == BUTTON_ID_DEL)
			{
				ShowWindow(hwnd, SW_HIDE);
				hwnd_del_win = CreateBox(sz_del_win, TEXT("删除商品"), hwnd);
				ShowWindow(hwnd_del_win, SW_SHOW);
			}
			else if (LOWORD(wParam) == BUTTON_ID_CHANGE)
			{
				ShowWindow(hwnd, SW_HIDE);
				hwnd_change_win = CreateBox(sz_change_win, TEXT("更改商品"), hwnd);
				ShowWindow(hwnd_change_win, SW_SHOW);
			}
			else if (LOWORD(wParam) == BUTTON_ID_ALL)
			{
				ShowWindow(hwnd, SW_HIDE);
				hwnd_all_win = CreateBox(sz_all_win, TEXT("全部商品"), hwnd);
				ShowWindow(hwnd_all_win, SW_SHOW);
			}

		}
		return 0;
	case WM_DESTROY:
		OpenFileWrite();
		PostQuitMessage(0);
		return 0;
	}



	return DefWindowProc(hwnd, message, wParam, lParam);
}
LRESULT CALLBACK inputproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	int Length;
	int index;
	static HWND input_tag1, input_tag2, input_tagg3,input_edit1,input_edit2,input_edit3,input_button;
	TCHAR szCommodityName[_MAX_PATH], szCommodityClass[_MAX_PATH], szCommodityPrice[_MAX_PATH];
	TCHAR ss[256];
	Commodity com;
	switch (message)
	{
	case WM_CREATE:
		input_tag1 = CreateTag(TEXT("商品名字:"), hwnd, 1);
		input_tag2 = CreateTag(TEXT("商品类型:"), hwnd, 2);
		input_tagg3 = CreateTag(TEXT("商品价格:"), hwnd, 3);
		input_edit1 = CreateEdit(hwnd, 4);
		input_edit2 = CreateEdit(hwnd, 5);
		input_edit3 = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER, 0, 0, 0, 0, hwnd, (HMENU)EDIT_ID_NAME,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);
		input_button = CreateButton(TEXT("确认"), hwnd, 4);

		MoveSite(hwnd, 300, 300, 500, 500);
		MoveSite(input_tag1, 70, 50, 70, 20);
		MoveSite(input_tag2, 70, 160, 70, 20);
		MoveSite(input_tagg3, 70, 290, 70, 20);
		MoveSite(input_edit1, 150, 50, 200, 20);
		MoveSite(input_edit2, 150, 160, 200, 20);
		MoveSite(input_edit3, 150, 290, 200, 20);
		MoveSite(input_button, 350, 370, 100, 40);
		return 0;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			if (LOWORD(wParam) == 4)
			{
				{
					Length = GetWindowTextLength(input_edit1) + 1;
					GetWindowText(input_edit1, szCommodityName, Length);
					Length = GetWindowTextLength(input_edit2) + 1;
					GetWindowText(input_edit2, szCommodityClass, Length);
					Length = GetWindowTextLength(input_edit3) + 1;
					GetWindowText(input_edit3, szCommodityPrice, Length);

					if ((index = SeekSiteStr(szCommodityName)) == ERROR_COMMODITY)
					{
						if (szCommodityName[0] == '\0' || szCommodityClass[0] == '\0' || szCommodityPrice[0] == '\0')
						{
							MessageBox(hwnd, TEXT("请填写完整信息"), TEXT("提示"), MB_OK);
							return 0;
						}
					
						lstrcpy(com.Name, szCommodityName);
						lstrcpy(com.Class, szCommodityClass);
						lstrcpy(com.Price, szCommodityPrice);

						if (add_information(SeekSiteEnd(&Xinxi),&Xinxi, &com) != TRUE)
						{
							MessageBox(hwnd, TEXT("内存已满"), TEXT("提示"), MB_OK);
							ShowWindow(hwnd, SW_HIDE);
							ShowWindow(HchildHwnd, SW_SHOW);
							return 0;
						}

						SetWindowText(input_edit1, NULL);
						SetWindowText(input_edit2, NULL);
						SetWindowText(input_edit3, NULL);
						MessageBox(hwnd, TEXT("添加成功"), TEXT("提示"), MB_OK);
						ShowWindow(hwnd, SW_HIDE);
						ShowWindow(HchildHwnd, SW_SHOW); 
					}
					else
						MessageBox(hwnd, TEXT("商品名已经重复"), TEXT("提示"), MB_OK);

					
				}
			}
		}
		return 0;
	case WM_DESTROY:
		/*ShowWindow(hwnd, SW_HIDE);
		ShowWindow(HchildHwnd, SW_SHOW);*/
		ShowWindow(HchildHwnd, SW_SHOW);
		DestroyWindow(hwnd);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
LRESULT CALLBACK Seekproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND Seek_tag1, Seek_tag2, Seek_tag3, Seek_tag4,Seek_edit,Seek_button;
	TCHAR szBuffer[256];
	TCHAR szName[256] = TEXT("商品名字:");
	TCHAR szClass[256] = TEXT("商品类型:");
	TCHAR szPrice[256] = TEXT("商品价格:");
	int Length;
	int index;
	switch (message)
	{
		case WM_CREATE:
			Seek_tag1 = CreateTag(TEXT(" "), hwnd, 1);
			Seek_tag2 = CreateTag(TEXT(" "), hwnd, 2);
			Seek_tag3 = CreateTag(TEXT(" "), hwnd, 3);
			Seek_tag4 = CreateTag(TEXT("输入要查找的商品名"), hwnd, 5);
			Seek_button = CreateButton(TEXT("查找"), hwnd, 6);
			Seek_edit = CreateEdit(hwnd, 4);

			MoveSite(hwnd, 300, 300, 500, 300);
			MoveSite(Seek_tag4, 70, 20, 300, 20);
			MoveSite(Seek_edit, 70, 50, 300, 20);
			MoveSite(Seek_button, 70, 100, 300, 20);
			MoveSite(Seek_tag1, 70, 150, 300, 20);
			MoveSite(Seek_tag2, 70, 180, 300, 20);
			MoveSite(Seek_tag3, 70, 210, 300, 20);
			return 0;

		case WM_COMMAND:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				if (LOWORD(wParam) == 6)
				{
					Length = GetWindowTextLength(Seek_edit) + 1;
					GetWindowText(Seek_edit, szBuffer, Length);
					if (lstrcmp(szBuffer, TEXT("")) == 0)
					{
						MessageBox(hwnd, TEXT("没有输入用户名"), TEXT("提示"), MB_OK);
						return 0;
					}
					if ((index = SeekSiteStr(szBuffer)) != ERROR_COMMODITY)
					{
						SetWindowText(Seek_tag1, lstrcat(szName, Xinxi[index].Name));
						SetWindowText(Seek_tag2, lstrcat(szClass, Xinxi[index].Class));
						SetWindowText(Seek_tag3, lstrcat(szPrice, Xinxi[index].Price));
					}
					else
					{
						SetWindowText(Seek_tag1, TEXT("没有查找到商品名"));
						SetWindowText(Seek_tag2,NULL);
						SetWindowText(Seek_tag3,NULL);
					}

				}
			}
			return 0;
		case WM_DESTROY:
			/*ShowWindow(hwnd, SW_HIDE);
			ShowWindow(HchildHwnd, SW_SHOW);*/
			ShowWindow(HchildHwnd, SW_SHOW);
			DestroyWindow(hwnd);
			return 0;

	}



	return DefWindowProc(hwnd, message, wParam, lParam);
}
LRESULT CALLBACK delproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND del_edit, del_button, del_tag;
	int status,Length;
	TCHAR szBuffer[256];

	switch (message)
	{
	case WM_CREATE:
		del_edit = CreateEdit(hwnd,1);
		del_button = CreateButton(TEXT("删除"), hwnd, 2);
		del_tag = CreateTag(TEXT("请输入你要删除的商品名"), hwnd, 3);
	case WM_SIZE:
		MoveSite(hwnd, 300, 300, 300, 200);
		MoveSite(del_tag, 50, 30,170,20);
		MoveSite(del_edit, 50, 60, 200, 20);
		MoveSite(del_button, 50, 90, 200, 20);
		return 0;
	case WM_COMMAND:
		if(HIWORD(wParam) == BN_CLICKED)
			if (LOWORD(wParam) == 2)
			{
			Length = GetWindowTextLength(del_edit) + 1;
			GetWindowText(del_edit, szBuffer, Length);
			if (lstrcmp(szBuffer, TEXT("")) == 0)
			{
				MessageBox(hwnd, TEXT("没有输入用户名"), TEXT("提示"), MB_OK);
				return 0;
			}
			if ((status = MessageBox(hwnd, TEXT("是否真的要删除"), TEXT("提示"), MB_YESNO)) == IDYES)
			{
				del_information(szBuffer);
				MessageBox(hwnd, TEXT("删除成功"), TEXT("提示"), MB_OK);
				return 0;
			}
			}
			return 0;
	case WM_DESTROY:
		ShowWindow(HchildHwnd, SW_SHOW);
		DestroyWindow(hwnd);
		return 0;
	}


	return DefWindowProc(hwnd, message, wParam, lParam);
}
LRESULT CALLBACK changeproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND change_button1, change_button2, change_button3;
	static HWND change_tag1, change_tag2, change_tag3, change_tag4;
	static HWND change_edit1, change_edit2, change_edit3, change_edit4;
	TCHAR szBuffer_edit[100], szBuffer_Name[100], szBuffer_Class[100], szBuffer_Price[100];
	int Length = 0, index = 0;
	Commodity com;

	switch (message)
	{
	case WM_CREATE:
		change_button1 = CreateButton(TEXT("搜索"), hwnd, 1);
		change_button2 = CreateButton(TEXT("取消"), hwnd, 2);
		change_button3 = CreateButton(TEXT("确认"), hwnd, 3);
		change_tag1 = CreateTag(TEXT("要搜索的商品名字:"), hwnd, 4);
		change_tag2 = CreateTag(TEXT("要更改的商品名字:"), hwnd, 5);
		change_tag3 = CreateTag(TEXT("要更改的类型名字:"), hwnd, 6);
		change_tag4 = CreateTag(TEXT("要更改的商品价格:"), hwnd, 7);
		change_edit1 = CreateEdit(hwnd, 8);
		change_edit2 = CreateEdit(hwnd, 9);
		change_edit3 = CreateEdit(hwnd, 10);
		change_edit4 = CreateEdit(hwnd, 11);
	case WM_SIZE:
		MoveSite(hwnd, 300, 300, 300, 500);

		MoveSite(change_button1, 170, 60, 50, 20);
		MoveSite(change_edit1, 20, 60, 130, 20);
		MoveSite(change_tag1, 20, 30, 130, 20);

		MoveSite(change_tag2, 20, 140, 130, 20);
		MoveSite(change_edit2, 20, 170, 130, 20);

		MoveSite(change_tag3, 20, 200, 130, 20);
		MoveSite(change_edit3, 20, 230, 130, 20);

		MoveSite(change_tag4, 20, 260, 130, 20);
		MoveSite(change_edit4, 20, 290, 130, 20);

		MoveSite(change_button2, 50, 400, 50, 20);
		MoveSite(change_button3, 150, 400, 50, 20);
		return 0;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			if (LOWORD(wParam) == 1)
			{
				Length = GetWindowTextLength(change_edit1) + 1;
				GetWindowText(change_edit1, szBuffer_edit, Length);
				if (Length == 0)
				{
					MessageBox(hwnd, TEXT("没有输入用户名"), TEXT("提示"), MB_OK);
					return 0;
				}
				if (((index = SeekSiteStr(szBuffer_edit)) == ERROR_COMMODITY))
				{
					MessageBox(hwnd, TEXT("失败没有查找到用户名"), TEXT("提示"), MB_OK);
					return 0;
				}
				SetWindowText(change_edit2, Xinxi[index].Name);
				SetWindowText(change_edit3, Xinxi[index].Class);
				SetWindowText(change_edit4, Xinxi[index].Price);
			}
			else if (LOWORD(wParam) == 3)
			{
				Length = GetWindowTextLength(change_edit1) + 1;
				GetWindowText(change_edit1, szBuffer_edit, Length);
				if (Length == 0)
				{
					MessageBox(hwnd, TEXT("没有输入用户名"), TEXT("提示"), MB_OK);
					return 0;
				}
				if (((index = SeekSiteStr(szBuffer_edit)) == ERROR_COMMODITY))
				{
					MessageBox(hwnd, TEXT("请勿更改不存在的商品"), TEXT("提示"), MB_OK);
					return 0;
				}
					
				Length = GetWindowTextLength(change_edit2) + 1;
				GetWindowText(change_edit2, szBuffer_Name, Length);

				Length = GetWindowTextLength(change_edit3) + 1;
				GetWindowText(change_edit3, szBuffer_Class, Length);

				Length = GetWindowTextLength(change_edit4) + 1;
				GetWindowText(change_edit4, szBuffer_Price, Length);

				if (lstrcmp(szBuffer_Name, TEXT("")) == 0 ||
					lstrcmp(szBuffer_Class, TEXT("")) == 0 ||
					lstrcmp(szBuffer_Price, TEXT("")) == 0)
				{
					MessageBox(hwnd, TEXT("信息没有输入完整请重新输入"), TEXT("提示"), MB_OK);
					return 0;
				}

				lstrcpy(com.Name, szBuffer_Name);
				lstrcpy(com.Class, szBuffer_Class);
				lstrcpy(com.Price, szBuffer_Price);
				add_information(index, &Xinxi, &com);
				MessageBox(hwnd, TEXT("更改成功"), TEXT("提示"), MB_OK);
				SendMessage(hwnd, WM_DESTROY, NULL, NULL);

			}
			else
				SendMessage(hwnd, WM_DESTROY, NULL, NULL);

		}
		return 0;
	case WM_DESTROY:
		ShowWindow(HchildHwnd, SW_SHOW);
		DestroyWindow(hwnd);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK ALL_XianShi(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	static HWND List;
	TCHAR szBuffer[256];
	int count = 0;
	int error = 0;
	switch (message)
	{
	case WM_CREATE:
		List = CreateWindow(TEXT("listbox"), NULL,
			WS_CHILD | WS_VISIBLE | LBS_STANDARD, 0, 0, 0, 0,
			hwnd, (HMENU)BUTTON_ID_ALL, ((HINSTANCE)(GetWindowLong(hwnd, GWL_HINSTANCE))), NULL);
		MoveSite(hwnd, 500, 500, 500, 500);
		MoveSite(List, 20, 20, 450, 430);
		count = MemberCount();
		for (int i = 0; i < count; i++)
		{
			wsprintf(szBuffer, TEXT("商品名:%ws 商品类型:%ws 商品价格:%ws"), &Xinxi[i].Name, &Xinxi[i].Class, &Xinxi[i].Price);
			error = SendMessage(List, LB_ADDSTRING, 0, (LPARAM)szBuffer);
		}
		return 0;
	case WM_SIZE:
		MoveSite(hwnd, 500, 500, 500, 500);
		MoveSite(List, 20, 20, 450, 430);
		return 0;
	case WM_DESTROY:
		ShowWindow(HchildHwnd, SW_SHOW);
		DestroyWindow(hwnd);
		return 0;
	}


	return DefWindowProc(hwnd, message, wParam, lParam);
}