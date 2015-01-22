#pragma once
#include <string>
using namespace std;
//#include "../CONTROLERHOOK/ontrolerConferenceEventChild.h"

class IControlerConference
{
public:
	IControlerConference() {}
	virtual ~IControlerConference(void) {};
	virtual void Release() = 0;
	virtual void EnableKeyBorad(BOOL bEnable) = 0;
};

class IControlerConferenceEvent
{
	public:
		IControlerConferenceEvent(){};
		virtual ~IControlerConferenceEvent(void){};
		//推出会议
		virtual void OnControlQuitConference() = 0;
		//模板调节
		virtual void OnControlTemplateAdjust() = 0;
		//视频调节
		virtual void OnControlVideoPreset() = 0;
		//广播视频
		virtual void OnControlVideoBroadcast() = 0;
		//会议白板
		virtual void OnControlWhiteBroad() = 0;
		//视频共享
		virtual void OnControlVideoShare() = 0;
		//会议屏幕
		virtual void OnControlScreen() = 0;
		//会议讨论
		virtual void OnControlVideoDiscussion() = 0;
		//录制所有
		virtual void OnControlRecordAll() = 0;
		//录制所有/停止
		virtual void OnControlRecordAllOrStop() = 0;
		//选择主屏
		virtual void OnControlSelectMainFrame(int iWin) = 0;

		virtual void OnPTZing() = 0;
	    
};

//创建实例
AFX_EXT_CLASS IControlerConference* CreateControlConference(IControlerConferenceEvent *pControlerConferenceEvent);