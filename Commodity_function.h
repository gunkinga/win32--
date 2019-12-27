#ifndef __COMMODITY_FUNCTION__
#define __COMMODITY_FUNCTION__
#include"DATA.h"

BOOL add_information(int count,PCommodity Pc,PCommodity pc_copy);
BOOL del_information(TCHAR *szName);

int SeekSiteEnd(PCommodity Pc);
int SeekSiteStr(TCHAR *szNname);
int StrCharint(TCHAR *szBuffer);
int MemberCount(void);//返回字符串不为空的数量
void Initialize_Commodity(PCommodity Pc);
void OpenFileRead(void);
void OpenFileWrite(void);
void InitializeStr(TCHAR *szBuffer);



void InitializeStr(TCHAR *szBuffer)
{
	int lenght = lstrlen(szBuffer);

 	for (int i = 0; i < lenght; i++)
		szBuffer[i] = NULL;
}
BOOL add_information(int count, PCommodity Pc, PCommodity pc_copy)
{
	if (count == ERROR_COMMODITY)
		return FALSE;

	lstrcpy(Pc[count].Name, pc_copy->Name);
	lstrcpy(Pc[count].Class, pc_copy->Class);
	lstrcpy(Pc[count].Price, pc_copy->Price);
	return TRUE;
}

void Initialize_Commodity(PCommodity Pc)
{
	for (int i = 0; i < XinXi_MAX; i++)
	{
		Pc[i].Name[0] = NULL;
		Pc[i].Class[0] = NULL;
		Pc[i].Price[0] = NULL;
		Pc[i].Site = i;
	}
}

int SeekSiteEnd(PCommodity Pc)//查找尾部
{
	for (int i = 0; i < XinXi_MAX; i++)
	{
		if (Pc[i].Class[0] == NULL || Pc[i].Name[0] == NULL)
			return Pc[i].Site;
	}

	return ERROR_COMMODITY;
}
int SeekSiteStr(TCHAR *szNname)
{
	for (int i = 0; i < XinXi_MAX; i++)
	{
		if (lstrcmp(Xinxi[i].Name, szNname) == 0)
			return Xinxi[i].Site;
	}
	return ERROR_COMMODITY;
}
int StrCharint(TCHAR *szBuffer)
{
	int count = 0,num = 0;
	TCHAR *ch;
	ch = szBuffer;

	while (*(szBuffer++) != ' ')
		count++;
	if (count == 0)
		return 0;

	for (int i = 0; i < count; i++)
	{
		if (i == 0)
		{
			num = (int)(*ch) - 48;
			ch++;
			continue;
		}
		num = num * 10 + (int)((*ch++) - 48);
	}

	return num;
}
BOOL del_information(TCHAR *szName)
{
	int index;

	if ((index = SeekSiteStr(szName)) == ERROR_COMMODITY)
	{
		MessageBox(hwnd_del_win, TEXT("删除失败没有查找到用户名"), TEXT("提示"), MB_OK);
		SendMessage(hwnd_del_win, WM_DESTROY, NULL, NULL);
		return 0;
	}
	
	memset(Xinxi[index].Name, NULL, sizeof(Xinxi[index].Name));
	memset(Xinxi[index].Class, NULL, sizeof(Xinxi[index].Class));
	memset(Xinxi[index].Price, NULL, sizeof(Xinxi[index].Price));
	return 1;

}
int MemberCount(void)
{
	int count = 0;

	for (int i = 0; i < XinXi_MAX; i++)
	{
		if (lstrcmp(Xinxi[i].Name, TEXT("")) == 0 ||
			lstrcmp(Xinxi[i].Class, TEXT("")) == 0 ||
			lstrcmp(Xinxi[i].Price,TEXT("")) == 0)
			continue;

		count++;
	}


	return count;
}
void OpenFileRead(void)
{
	TCHAR Catalog[MAX_PATH];//目录
	TCHAR FileName[] = TEXT("\\information");
	TCHAR CatalongFileName[256];
	TCHAR *szBuffer,szTmep = NULL;
	DWORD Filesize;
	Commodity com;
	int count = 0,status = 0,status_cpy = 0,add_status = 0,lenght = 0;
	int index_Name = 0, index_Class = 0, index_Price = 0,index;
	GetCurrentDirectory(MAX_PATH, Catalog);
	lstrcpy(CatalongFileName, Catalog);
	lstrcat(CatalongFileName, FileName);

	InitializeStr(szTmepName);
	InitializeStr(szTmepClass);
	InitializeStr(szTmepPrice);

	HANDLE File = CreateFile(CatalongFileName, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (File == INVALID_HANDLE_VALUE)
	{
		MessageBox(Parent_window, TEXT("打开文件失败"), TEXT("提示"), MB_OK);
		SendMessage(Parent_window, WM_DESTROY, NULL, NULL);
	}

	Filesize = GetFileSize(File, NULL);

	if (Filesize == 0)
	{
		CloseHandle(File);
		return;
	}
		

	szBuffer = (TCHAR*)calloc(Filesize,sizeof(TCHAR) + XinXi_MAX);
	
	if(ReadFile(File, szBuffer, Filesize, &Filesize,NULL) == FALSE)
	{
		MessageBox(Parent_window, TEXT("读取内容失败"), TEXT("提示"), MB_OK);
		SendMessage(Parent_window, WM_DESTROY, NULL, NULL);
	}
	lenght = lstrlen(szBuffer);

	for (int i = 0; i < XinXi_MAX; i++)
	{
		while (count != lenght)
		{

			if (szTmep == (TCHAR)TEXT('\n'))
				break;

			else if (szTmep == (TCHAR)TEXT(' '))
				status += 1;

			if (status != status_cpy)
			{
				status_cpy = status;
				/*index = 0;*/
			}

            if (status == 0)
			{
				if (*(szBuffer + count) == (TCHAR)TEXT(' '))
				{
					szTmep = *(szBuffer + count);
					count++;
					continue;
				}
					
				szTmepName[index_Name] = *(szBuffer + count);
				szTmep = *(szBuffer + count);
				index_Name++;
			}
 			else if (status == 1)
			{
				if (*(szBuffer + count) == (TCHAR)TEXT(' '))
				{
					szTmep = *(szBuffer + count);
					count++;
					continue;
				}

				szTmepClass[index_Class] = *(szBuffer + count);
				szTmep = *(szBuffer + count);
				index_Class++;
			}
			else if (status == 2)
			{
				if (*(szBuffer + count) == (TCHAR)TEXT('\n'))
				{
					szTmep = *(szBuffer + count);
					count++;
					continue;
				}
				  
				szTmepPrice[index_Price] = *(szBuffer + count);
				szTmep = *(szBuffer + count);
				index_Price++;
			}
			add_status = 1;
			count++;
		}
		if (add_status == 1)
		{
			index = SeekSiteEnd(&Xinxi[0]);
			lstrcpy(Xinxi[index].Name, szTmepName);
			lstrcpy(Xinxi[index].Class, szTmepClass);
			lstrcpy(Xinxi[index].Price, szTmepPrice);
			szTmep = NULL;
			status = 0;
			status_cpy = 0;
			add_status = 0;
			index_Name = 0;
			index_Class = 0;
			index_Price = 0;
		}
		
	}

	free(szBuffer);
	CloseHandle(File);
}
void OpenFileWrite(void)
{
	TCHAR Catalog[MAX_PATH];//目录
	TCHAR FileName[] = TEXT("\\information");
	TCHAR CatalongFileName[256];
	//TCHAR *szBuffer;
	DWORD Filesize;
	TCHAR *szbuffer;
	GetCurrentDirectory(MAX_PATH, Catalog);
	lstrcpy(CatalongFileName, Catalog);
	lstrcat(CatalongFileName, FileName);

	HANDLE File = CreateFile(CatalongFileName, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (File == INVALID_HANDLE_VALUE)
	{
		MessageBox(Parent_window, TEXT("打开文件失败"), TEXT("提示"), MB_OK);
		SendMessage(Parent_window, WM_DESTROY, NULL, NULL);
	}
	szbuffer = (TCHAR*)calloc(XinXi_MAX, sizeof(Commodity) + XinXi_MAX);//给换行符 空格符 预留空间
	InitializeStr(szbuffer);

	for (int i = 0; i < SeekSiteEnd(Xinxi); i++)
	{
		if (i == 0)
		{
			lstrcpy(szbuffer, Xinxi[i].Name);
			lstrcat(szbuffer, TEXT(" "));
			lstrcat(szbuffer, Xinxi[i].Class);
			lstrcat(szbuffer, TEXT(" "));
			lstrcat(szbuffer, Xinxi[i].Price);
			lstrcat(szbuffer, TEXT("\n"));
			continue;
		}
		lstrcat(szbuffer, Xinxi[i].Name);
		lstrcat(szbuffer, TEXT(" "));
		lstrcat(szbuffer, Xinxi[i].Class);
		lstrcat(szbuffer, TEXT(" "));
		lstrcat(szbuffer, Xinxi[i].Price);
		lstrcat(szbuffer, TEXT("\n"));
	}


	if (WriteFile(File, szbuffer, lstrlen(szbuffer) * 2, &Filesize, NULL) == FALSE)
	{
		MessageBox(Parent_window, TEXT("读取内容失败"), TEXT("提示"), MB_OK);
		SendMessage(Parent_window, WM_DESTROY, NULL, NULL);
	}

	free(szbuffer);
	CloseHandle(File);
}






#endif