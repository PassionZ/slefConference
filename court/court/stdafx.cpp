
// stdafx.cpp : 只包括标准包含文件的源文件
// court.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


char *ChangTextToUtf8(LPCTSTR szText,char* szTemp)				//改变文本格式为UTf8
{
	USES_CONVERSION;
	sprintf(szTemp,"%s",CT2A(szText));
	return szTemp;
}

TCHAR *ChangUtf8ToText(const char* szText,TCHAR *szTemp)				//改变文本格式由UTf8转回
{
    //CString sTemp = szText;
    //_tcscpy(szTemp, sTemp);
    //return szTemp;

	USES_CONVERSION;
	wsprintf(szTemp,_T("%s"),CA2W(szText));
	return szTemp;
}
CString GetExePath()
{
	TCHAR path[8192];
	HMODULE hModule = AfxGetInstanceHandle();
	int len = GetModuleFileName(hModule,path,8192);
	path[len]=0;
	TCHAR* ret = _tcsrchr(path,'\\');
	if(!ret)
		return _T("");
	int idxlen = (int)(ret - path + 1);
	path[idxlen]=0;
	return CString(path);
}