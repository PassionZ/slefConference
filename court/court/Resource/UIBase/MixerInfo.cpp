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
		//关闭混合器
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

BOOL CMixerInfo::GetVolumeMute()							// 判断是否静音
{
	return GetMute(m_dwComponentType);
}

void CMixerInfo::SetVolumeMute(BOOL bMute)				// 设置静音
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
			//打开Mixer设备   
			if(mixerOpen(&m_hMixer, i, 0, 0, MIXER_OBJECTF_MIXER) != MMSYSERR_NOERROR)
				continue;  

			MIXERLINE MixerLine;   
			//结构体的大小   
			MixerLine.cbStruct = sizeof(MixerLine);   
			//录制设备总线   
			MixerLine.dwComponentType   =   MIXERLINE_COMPONENTTYPE_DST_WAVEIN;   
			//得到录制总线中的连接数   
			if(mixerGetLineInfo((HMIXEROBJ)m_hMixer, &MixerLine,
				MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE) != MMSYSERR_NOERROR)
				continue;  

			//将连接数保存   
			DWORD dwConnections = MixerLine.cConnections;   
			//准备获取麦克风设备的ID   
			DWORD dwLineID = 0;   
			for(DWORD i = 0; i < dwConnections; i++ )   
			{   
				//枚举每一个设备，当Source的ID等于当前的迭代记数   
				MixerLine.dwSource = i;   
				//根据SourceID获得连接的信息   
				if(mixerGetLineInfo((HMIXEROBJ)m_hMixer, &MixerLine,   
					MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_SOURCE) != MMSYSERR_NOERROR) 
					//判断函数执行错误   
					break;   

				//如果当前设备类型是麦克风，则跳出循环。   
				if(MixerLine.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE)   
				{   
					dwLineID = MixerLine.dwLineID;
					dwSource = MixerLine.dwSource;
					break;   
				}   
			}

			//如果没有找到，返回失败。   
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
	UINT		uNumMixers;				// 混合器的数量											
	MIXERCAPS	MixerCaps;				// 当前混合器的性能参数	

	uNumMixers = ::mixerGetNumDevs();	//初始化，获取当前混合设备数量 
	::ZeroMemory(&MixerCaps, sizeof(MIXERCAPS));
	if(uNumMixers !=0)
	{	
		for(int i = 0; i < uNumMixers; i ++)
		{
			// 打开混合设备
			if (::mixerOpen(&m_hMixer, i, (DWORD)m_hWnd, NULL, /*MIXER_OBJECTF_MIXER |*/ CALLBACK_WINDOW) != MMSYSERR_NOERROR)
				continue ;

			MIXERLINE MixerLine;   
			//结构体的大小   
			MixerLine.cbStruct = sizeof(MixerLine);   
			//录制设备总线   
			MixerLine.dwComponentType   =   dwComponentType;   
			//得到录制总线中的连接数   
			if(mixerGetLineInfo((HMIXEROBJ)m_hMixer, &MixerLine,
				MIXER_OBJECTF_HMIXER | MIXER_GETLINEINFOF_COMPONENTTYPE) != MMSYSERR_NOERROR)
				continue; 
			else
				break;
		}

		// 确定混音器设备的能力
		if (::mixerGetDevCaps((UINT)m_hMixer, &MixerCaps, sizeof(MIXERCAPS)) != MMSYSERR_NOERROR)
			return ;
	}

	m_strDeviceName.Format(_T("%s"), MixerCaps.szPname);
}

DWORD CMixerInfo::GetValue(DWORD dwComponentType)
{
	//获得混合器信息
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

	//获得混合器线控件
	if (::mixerGetLineControls((HMIXEROBJ)m_hMixer, &mxlc, MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE)!= MMSYSERR_NOERROR)
		return 101;

	//获取当前音量
	DWORD NewVolume = 0;	
	MIXERCONTROLDETAILS_UNSIGNED mxcdVolume;
	MIXERCONTROLDETAILS mxcd;

	mxcd.cbStruct		= sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID	= mxc.dwControlID;
	mxcd.cChannels		= 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails		= sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails		= &mxcdVolume;

	//获取指定混合器控件 
	if (::mixerGetControlDetails((HMIXEROBJ)m_hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
		return 101;

	NewVolume = (mxcdVolume.dwValue*m_dwMaxValue)/mxc.Bounds.dwMaximum;

	return NewVolume;
}

void  CMixerInfo::SetValue(DWORD dwValue, DWORD dwComponentType)
{
	//获得混合器信息
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

	//获得混合器线控件
	if (::mixerGetLineControls((HMIXEROBJ)m_hMixer, &mxlc, MIXER_OBJECTF_HMIXER | MIXER_GETLINECONTROLSF_ONEBYTYPE)!= MMSYSERR_NOERROR)
		return;

	//设置音量
	MIXERCONTROLDETAILS_UNSIGNED NewmxcdVolume = { (dwValue*mxc.Bounds.dwMaximum)/m_dwMaxValue };
	MIXERCONTROLDETAILS mxcd;

	mxcd.cbStruct		= sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID	= mxc.dwControlID;
	mxcd.cChannels		= 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails		= sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails		= &NewmxcdVolume;

	//放置混合器控件 
	if (::mixerSetControlDetails((HMIXEROBJ)m_hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
		return ;
}

BOOL CMixerInfo::GetMute(DWORD dwComponentType)
{
	//获得混合器信息
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

	//获得混合器线控件
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

	//获取指定混合器控件 
	if (::mixerGetControlDetails((HMIXEROBJ)m_hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_GETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
		return FALSE;

	return !mxcMute.fValue;
}

void CMixerInfo::SetMute(BOOL bMute, DWORD dwComponentType)
{
	//获得混合器信息
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

	//获得混合器线控件
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

	//放置混合器控件 
	if (::mixerSetControlDetails((HMIXEROBJ)m_hMixer, &mxcd, MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE) != MMSYSERR_NOERROR)
		return ;
}