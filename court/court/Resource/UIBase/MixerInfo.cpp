#include "StdAfx.h"
#include ".\MixerInfo.h"
 #include <mmsystem.h>

CMixerInfo::CMixerInfo(HWND hWnd,DWORD dwComponentType, DWORD dwMinValue, DWORD dwMaxValue)
{
	m_hWnd					= hWnd;
	m_dwMinValue			= dwMinValue;
	m_dwMaxValue			= dwMaxValue;			
	m_hMixer				= NULL;								
	m_strDeviceName			= _T("");

	switch(dwComponentType)
	{
	case MIXERLINE_COMPONENTTYPE_DST_SPEAKERS:
		m_dwComponentType=MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
		InitVolumeInfo(MIXERLINE_COMPONENTTYPE_DST_SPEAKERS);
		break;
	case MIXERLINE_COMPONENTTYPE_DST_WAVEIN:
		m_dwComponentType=MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE;
		InitVolumeInfo(MIXERLINE_COMPONENTTYPE_DST_WAVEIN);
		break;
	}
}

CMixerInfo::~CMixerInfo(void)
{
	m_hWnd = NULL;
	if (m_hMixer != NULL)
	{	
		//�رջ����
		::mixerClose(m_hMixer);
		m_hMixer = NULL;
	}
}

CString CMixerInfo::GetDeviceName()
{
	return m_strDeviceName;
}

DWORD CMixerInfo::GetVolumeValue()
{
	return GetValue(m_dwComponentType);
}

void CMixerInfo::SetVolumeValue(DWORD dwValue)
{
	SetValue(dwValue, m_dwComponentType);
}

BOOL CMixerInfo::GetVolumeMute()							// �ж��Ƿ���
{
	return GetMute(m_dwComponentType);
}

void CMixerInfo::SetVolumeMute(BOOL bMute)				// ���þ���
{
	SetMute(bMute, m_dwComponentType);
}

/*	BOOL bResult = FALSE;
	try
	{
		int mixerNum = (int)mixerGetNumDevs();
		for(int i = 0; i < mixerNum; i ++)
		{
			DWORD dwSource = 0;
			HMIXER m_hMixer = NULL;   
			MMRESULT mr = NULL;
			//��Mixer�豸   
			if(mixerOpen(&m_hMixer, i, 0, 0, MIXER_OBJECTF_MIXER) != MMSYSERR_NOERROR)
				continue;  

			MIXERLINE MixerLine;   
			//�ṹ��Ĵ�С   
			MixerLine.cbStruct = sizeof(MixerLine);   
			//¼���豸����   
			MixerLine.dwComponentType   =   MIXERLINE_COMPONENTTYPE_DST_WAVEIN;   
			//�õ�¼�������е�������   
			if(mixerGetLineInfo((HMIXEROBJ)m_hMixer, &MixerLine,
				MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE) != MMSYSERR_NOERROR)
				continue;  

			//������������   
			DWORD dwConnections = MixerLine.cConnections;   
			//׼����ȡ��˷��豸��ID   
			DWORD dwLineID = 0;   
			for(DWORD i = 0; i < dwConnections; i++ )   
			{   
				//ö��ÿһ���豸����Source��ID���ڵ�ǰ�ĵ�������   
				MixerLine.dwSource = i;   
				//����SourceID������ӵ���Ϣ   
				if(mixerGetLineInfo((HMIXEROBJ)m_hMixer, &MixerLine,   
					MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_SOURCE) != MMSYSERR_NOERROR) 
					//�жϺ���ִ�д���   
					break;   

				//�����ǰ�豸��������˷磬������ѭ����   
				if(MixerLine.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE)   
				{   
					dwLineID = MixerLine.dwLineID;
					dwSource = MixerLine.dwSource;
					break;   
				}   
			}

			//���û���ҵ�������ʧ�ܡ�   
			if(dwLineID == 0)   
				continue;    

			//get line id of destination line   
			MIXERLINE lineinfo_Dest;   
			::ZeroMemory(&lineinfo_Dest, sizeof(MIXERLINE));   
			lineinfo_Dest.cbStruct = sizeof(MIXERLINE);   
			lineinfo_Dest.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;   
			if(::mixerGetLineInfo(   
				(HMIXEROBJ)m_hMixer,   
				&lineinfo_Dest,   
				MIXER_OBJECTF_HMIXER   |     
				MIXER_GETLINEINFOF_COMPONENTTYPE) != MMSYSERR_NOERROR)
				continue;   

			//get id of specified connector   
			MIXERLINE lineinfo_Connector;   
			::ZeroMemory(&lineinfo_Connector, sizeof(MIXERLINE));   

			lineinfo_Connector.cbStruct = sizeof(MIXERLINE);   
			lineinfo_Connector.dwDestination = lineinfo_Dest.dwLineID;   
			lineinfo_Connector.dwSource = dwSource;   
			if(::mixerGetLineInfo(   
				(HMIXEROBJ)m_hMixer,   
				&lineinfo_Connector,     
				MIXER_GETLINEINFOF_SOURCE) != MMSYSERR_NOERROR)
				continue;   

			MIXERCONTROL mxc;   
			MIXERLINECONTROLS mxlc;   
			mxlc.cbStruct = sizeof(MIXERLINECONTROLS);   
			mxlc.dwLineID = lineinfo_Connector.dwLineID;   
			mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;   
			mxlc.cControls = 1;   
			mxlc.cbmxctrl = sizeof(MIXERCONTROL);   
			mxlc.pamxctrl = &mxc;   
			if(::mixerGetLineControls(   
				reinterpret_cast<HMIXEROBJ>(m_hMixer),   
				&mxlc,   
				MIXER_OBJECTF_HMIXER|MIXER_GETLINECONTROLSF_ONEBYTYPE)!= MMSYSERR_NOERROR)
				continue;   

			//get volume value range now   
			MIXERCONTROLDETAILS_UNSIGNED mxcdVolume;   
			MIXERCONTROLDETAILS mxcd;   
			mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);   
			mxcd.dwControlID = mxc.dwControlID;   
			mxcd.cChannels = 1;   
			mxcd.cMultipleItems = 0;   
			mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);   
			mxcd.paDetails = &mxcdVolume;   
			if(mixerGetControlDetails(   
				reinterpret_cast<HMIXEROBJ>(m_hMixer),   
				&mxcd,   
				MIXER_GETCONTROLDETAILSF_VALUE)!= MMSYSERR_NOERROR)
				continue;   

			//set volume   
			MIXERCONTROLDETAILS_UNSIGNED mxcdVolume_Set = { mxc.Bounds.dwMaximum * dwValue / 100 };   
			MIXERCONTROLDETAILS mxcd_Set;   
			mxcd_Set.cbStruct = sizeof(MIXERCONTROLDETAILS);   
			mxcd_Set.dwControlID = mxc.dwControlID;   
			mxcd_Set.cChannels = 1;   
			mxcd_Set.cMultipleItems = 0;   
			mxcd_Set.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);   
			mxcd_Set.paDetails = &mxcdVolume_Set;   
			if(mixerSetControlDetails(reinterpret_cast<HMIXEROBJ>(m_hMixer),   
				&mxcd_Set,   
				MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
				continue;    

			::mixerClose(m_hMixer);
			m_hMixer = NULL;
			bResult = TRUE;;
		}
	}
	catch(...){ return; }*/

void CMixerInfo::InitVolumeInfo(DWORD dwComponentType)
{	
	UINT		uNumMixers;				// �����������											
	MIXERCAPS	MixerCaps;				// ��ǰ����������ܲ���	

	uNumMixers = ::mixerGetNumDevs();	//��ʼ������ȡ��ǰ����豸���� 
	::ZeroMemory(&MixerCaps, sizeof(MIXERCAPS));
	if(uNumMixers !=0)
	{	
		for(int i = 0; i < uNumMixers; i ++)
		{
			// �򿪻���豸
			if (::mixerOpen(&m_hMixer, i, (DWORD)m_hWnd, NULL, /*MIXER_OBJECTF_MIXER |*/ CALLBACK_WINDOW) != MMSYSERR_NOERROR)
				continue ;

			MIXERLINE MixerLine;   
			//�ṹ��Ĵ�С   
			MixerLine.cbStruct = sizeof(MixerLine);   
			//¼���豸����   
			MixerLine.dwComponentType   =   dwComponentType;   
			//�õ�¼�������е�������   
			if(mixerGetLineInfo((HMIXEROBJ)m_hMixer, &MixerLine,
				MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE) != MMSYSERR_NOERROR)
				continue; 
			else
				break;
		}

		// ȷ���������豸������
		if (::mixerGetDevCaps((UINT)m_hMixer, &MixerCaps, sizeof(MIXERCAPS)) != MMSYSERR_NOERROR)
			return ;
	}

	m_strDeviceName.Format(_T("%s"), MixerCaps.szPname);
}

DWORD CMixerInfo::GetValue(DWORD dwComponentType)
{
	//��û������Ϣ
	MIXERLINE mxl;
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = dwComponentType;
	if (::mixerGetLineInfo((HMIXEROBJ)m_hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE)!= MMSYSERR_NOERROR)
		return  101;

	MIXERCONTROL mxc;
	MIXERLINECONTROLS mxlc;
	mxlc.cbStruct		= sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID		= mxl.dwLineID;
	mxlc.dwControlType	= MIXERCONTROL_CONTROLTYPE_VOLUME;
	mxlc.cControls		= 1;
	mxlc.cbmxctrl		= sizeof(MIXERCONTROL);
	mxlc.pamxctrl		= &mxc;

	//��û�����߿ؼ�
	if (::mixerGetLineControls((HMIXEROBJ)m_hMixer, &mxlc, MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE)!= MMSYSERR_NOERROR)
		return 101;

	//��ȡ��ǰ����
	DWORD NewVolume = 0;	
	MIXERCONTROLDETAILS_UNSIGNED mxcdVolume;
	MIXERCONTROLDETAILS mxcd;

	mxcd.cbStruct		= sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID	= mxc.dwControlID;
	mxcd.cChannels		= 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails		= sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails		= &mxcdVolume;

	//��ȡָ��������ؼ� 
	if (::mixerGetControlDetails((HMIXEROBJ)m_hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
		return 101;

	NewVolume = (mxcdVolume.dwValue*m_dwMaxValue)/mxc.Bounds.dwMaximum;

	return NewVolume;
}

void  CMixerInfo::SetValue(DWORD dwValue, DWORD dwComponentType)
{
	//��û������Ϣ
	MIXERLINE mxl;
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = dwComponentType;
	if (::mixerGetLineInfo((HMIXEROBJ)m_hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE)!= MMSYSERR_NOERROR)
		return;

	MIXERCONTROL mxc;
	MIXERLINECONTROLS mxlc;
	mxlc.cbStruct		= sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID		= mxl.dwLineID;
	mxlc.dwControlType	= MIXERCONTROL_CONTROLTYPE_VOLUME;
	mxlc.cControls		= 1;
	mxlc.cbmxctrl		= sizeof(MIXERCONTROL);
	mxlc.pamxctrl		= &mxc;

	//��û�����߿ؼ�
	if (::mixerGetLineControls((HMIXEROBJ)m_hMixer, &mxlc, MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE)!= MMSYSERR_NOERROR)
		return;

	//��������
	MIXERCONTROLDETAILS_UNSIGNED NewmxcdVolume = { (dwValue*mxc.Bounds.dwMaximum)/m_dwMaxValue };
	MIXERCONTROLDETAILS mxcd;

	mxcd.cbStruct		= sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID	= mxc.dwControlID;
	mxcd.cChannels		= 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails		= sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails		= &NewmxcdVolume;

	//���û�����ؼ� 
	if (::mixerSetControlDetails((HMIXEROBJ)m_hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
		return ;
}

BOOL CMixerInfo::GetMute(DWORD dwComponentType)
{
	//��û������Ϣ
	MIXERLINE mxl;
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = dwComponentType;
	if (::mixerGetLineInfo((HMIXEROBJ)m_hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE)!= MMSYSERR_NOERROR)
		return FALSE;

	MIXERCONTROL mxc;
	MIXERLINECONTROLS mxlc;
	mxlc.cbStruct		= sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID		= mxl.dwLineID;
	mxlc.dwControlType	= MIXERCONTROL_CONTROLTYPE_MUTE;
	mxlc.cControls		= 1;
	mxlc.cbmxctrl		= sizeof(MIXERCONTROL);
	mxlc.pamxctrl		= &mxc;

	//��û�����߿ؼ�
	if (::mixerGetLineControls((HMIXEROBJ)m_hMixer, &mxlc, MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE)!= MMSYSERR_NOERROR)
		return FALSE;


	MIXERCONTROLDETAILS mxcd;
	MIXERCONTROLDETAILS_BOOLEAN mxcMute;

	mxcd.cbStruct		= sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID	= mxc.dwControlID;
	mxcd.cChannels		= 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails		= sizeof(MIXERCONTROLDETAILS_BOOLEAN);
	mxcd.paDetails		= &mxcMute;

	//��ȡָ��������ؼ� 
	if (::mixerGetControlDetails((HMIXEROBJ)m_hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
		return FALSE;

	return !mxcMute.fValue;
}

void CMixerInfo::SetMute(BOOL bMute, DWORD dwComponentType)
{
	//��û������Ϣ
	MIXERLINE mxl;
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = dwComponentType;
	if (::mixerGetLineInfo((HMIXEROBJ)m_hMixer, &mxl, MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE)!= MMSYSERR_NOERROR)
		return;

	MIXERCONTROL mxc;
	MIXERLINECONTROLS mxlc;
	mxlc.cbStruct		= sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID		= mxl.dwLineID;
	mxlc.dwControlType	= MIXERCONTROL_CONTROLTYPE_MUTE;
	mxlc.cControls		= 1;
	mxlc.cbmxctrl		= sizeof(MIXERCONTROL);
	mxlc.pamxctrl		= &mxc;

	//��û�����߿ؼ�
	if (::mixerGetLineControls((HMIXEROBJ)m_hMixer, &mxlc, MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE)!= MMSYSERR_NOERROR)
		return;


	MIXERCONTROLDETAILS mxcd;
	MIXERCONTROLDETAILS_BOOLEAN mxcMute;

	mxcd.cbStruct		= sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID	= mxc.dwControlID;
	mxcd.cChannels		= 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails		= sizeof(MIXERCONTROLDETAILS_BOOLEAN);
	mxcd.paDetails		= &mxcMute;

	mxcMute.fValue      = !bMute;

	//���û�����ؼ� 
	if (::mixerSetControlDetails((HMIXEROBJ)m_hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
		return ;
}