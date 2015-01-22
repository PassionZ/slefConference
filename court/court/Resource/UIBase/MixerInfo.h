#pragma once

// ***************************************************************
//  CMixerInfo   version:  1.0   ��  date: 2009/09/07
//  -------------------------------------------------------------
//  ����������Ϣ����
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 												By:	HHJ
// ***************************************************************

 #include <mmsystem.h>

class CMixerInfo
{
public:
	CMixerInfo(HWND hWnd,DWORD dwComponentType=4, DWORD dwMinValue = 0, DWORD dwMaxValue = 100);
	virtual ~CMixerInfo(void);

	CString GetDeviceName();				// ȡ�豸����

	// Volume
	DWORD GetVolumeValue();					// ȡ����ֵ
	void SetVolumeValue(DWORD dwValue);		// ������ֵ
	BOOL GetVolumeMute();					// �ж��Ƿ���	FALSE ����	TRUE ������
	void SetVolumeMute(BOOL bMute);			// ���þ���		FALSE ����	TRUE ������

private:
	void InitVolumeInfo(DWORD dwComponentType);					// ��ʼ����������Ϣ
	DWORD GetValue(DWORD dwComponentType);					// �õ���Ӧ���͵������Ĵ�С
	void SetValue(DWORD dwValue, DWORD dwComponentType);	// ������Ӧ���͵������Ĵ�С

	BOOL GetMute(DWORD dwComponentType);					// �õ���Ӧ�����Ƿ���	
	void SetMute(BOOL bMute, DWORD dwComponentType);		// ������Ӧ�����Ƿ���

private:
	HWND		m_hWnd;
	DWORD		m_dwMinValue;				// ��С������ֵ	
	DWORD		m_dwMaxValue;				// ��������ֵ					
	HMIXER		m_hMixer;					// ��ǰ������ľ��	
	CString     m_strDeviceName;			// �豸����
	DWORD		m_dwComponentType;			// Ӧ�õ�����
};
