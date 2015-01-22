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
		//�Ƴ�����
		virtual void OnControlQuitConference() = 0;
		//ģ�����
		virtual void OnControlTemplateAdjust() = 0;
		//��Ƶ����
		virtual void OnControlVideoPreset() = 0;
		//�㲥��Ƶ
		virtual void OnControlVideoBroadcast() = 0;
		//����װ�
		virtual void OnControlWhiteBroad() = 0;
		//��Ƶ����
		virtual void OnControlVideoShare() = 0;
		//������Ļ
		virtual void OnControlScreen() = 0;
		//��������
		virtual void OnControlVideoDiscussion() = 0;
		//¼������
		virtual void OnControlRecordAll() = 0;
		//¼������/ֹͣ
		virtual void OnControlRecordAllOrStop() = 0;
		//ѡ������
		virtual void OnControlSelectMainFrame(int iWin) = 0;

		virtual void OnPTZing() = 0;
	    
};

//����ʵ��
AFX_EXT_CLASS IControlerConference* CreateControlConference(IControlerConferenceEvent *pControlerConferenceEvent);