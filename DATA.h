#ifndef __DATA__
#define __DATA__
#include<Windows.h>


#define EDIT_ID_NAME 1
#define EDIT_ID_PASSWORD 2
#define BUTTON_ID 3
#define STATIC_ID_NAME 4
#define STATIC_ID_PASSWORD 5
#define BUTTON_ID_ADD 10
#define BUTTON_ID_DEL 11
#define BUTTON_ID_CHANGE 12
#define BUTTON_ID_SEEK 13
#define BUTTON_ID_ALL 14
#define ERROR_COMMODITY 7749
#define XinXi_MAX 100//数组形式的最多添加100个

typedef struct tagCommodity
{
	TCHAR Name[20];//商品名字不超过20个字节
	TCHAR Class[10];//商品的类别
	TCHAR  Price[10];//价格
	int	 Site;//位置用于查找

}Commodity, *PCommodity;



static TCHAR sz_input_win[] = TEXT("输入信息");
static TCHAR sz_seek_win[] = TEXT("查看信息");
static TCHAR sz_del_win[] = TEXT("删除信息");
static TCHAR sz_User_Name[] = TEXT("123456789");
static TCHAR sz_PassWord[] = TEXT("123456789");
static TCHAR szChildNmae[] = TEXT("XinXiGuanLi");
static TCHAR sz_change_win[] = TEXT("更改信息");
static TCHAR sz_all_win[] = TEXT("所有信息");

static HWND hButton_add, hButton_del, hbutton_change, hbutton_examine,hbutton_all;//子窗口控件句柄
static HWND hwnd_input_win,hwnd_seek_win,hwnd_del_win,hwnd_change_win,hwnd_all_win;//信息框句柄
static HWND Hedit_Name, Hedit_Password, Hbutton_Ok, Hstatic_Name, Hstatic_Passwrod, HchildHwnd;//父窗口控件句柄
static HWND Parent_window;
static WNDPROC upProc;
static Commodity Xinxi[XinXi_MAX];
static TCHAR szTmepName[20], szTmepClass[10], szTmepPrice[10];

//static int IdFocus = 0;













#endif