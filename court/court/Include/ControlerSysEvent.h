#pragma once
#include <string>
using namespace std;
class IControlerSYS
{
public:
	IControlerSYS() {};
	virtual ~IControlerSYS() {};
	virtual void Release() = 0;
	virtual void EnableKeyBorad(BOOL bEnable) = 0;
};

class IControlerSYSEvent
{
public:
	IControlerSYSEvent(){};
	virtual~IControlerSYSEvent(){};
	//����
	//virtual void OnControlHelp() = 0;
	//�˵�
	virtual void OnControlMenu() = 0;
	//����
	virtual void OnControlFriend() = 0;
	//�������
	virtual void OnControlConference() = 0;
	//��Ƶ����
	virtual void OnControlVideoAdjust() = 0;
	//��Ƶ����
	virtual void OnControlAudioAdjust() = 0;
	//ѡ��
	virtual void OnControlOptions() = 0;
	//��Զ
	//virtual void OnControlZoomOut() = 0;
	//����
	//virtual void OnControlZoomIn() = 0;
	//��������
	virtual void OnControlNetworkSetting() = 0;
    //�˳�ϵͳ
	virtual void OnControlQuitSystem() = 0;
	//����
	virtual void OnCallPhone() = 0;
	//�Ҷ�
	virtual void OnShutPhone() = 0;
	//MIC UP
	virtual void OnMicVolumeUp() = 0;
	//MIC DOWN
	virtual void OnMicVolumeDown() = 0;
	//AVCON����/��ʾ
	virtual void OnAvconHideShow() = 0;
	virtual void OnPTZing() = 0;
	virtual void OnShutOpenMic1() = 0;
};
AFX_EXT_CLASS IControlerSYS* CreateControlSYS(IControlerSYSEvent *pControlerSYSEvent);
