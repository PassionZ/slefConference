
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// court.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


char *ChangTextToUtf8(LPCTSTR szText,char* szTemp)				//�ı��ı���ʽΪUTf8
{
	USES_CONVERSION;
	sprintf(szTemp,"%s",CT2A(szText));
	return szTemp;
}

TCHAR *ChangUtf8ToText(const char* szText,TCHAR *szTemp)				//�ı��ı���ʽ��UTf8ת��
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