#ifndef __RSMSGDEFINE_H
#define __RSMSGDEFINE_H

#include "../DataDefine/DataDefine.h"

#define		COUNTOFONCE		400
// ����ID���壨���֣�

// ֻ�ϴ����ϲ�MCU���������ݣ�
#define 	CONF_COMMAND_FETCHMCUINFO						0x0001	// ȡ��MCU��Ϣ
#define 	CONF_COMMAND_FETCHMCUINFOEND					0x0002	// ȡ��MCU��Ϣ����
#define     CONF_COMMAND_FETCHCONFERENCEBASEINFO			0x0003  // ȡ�û��������Ϣ
#define     CONF_COMMAND_FETCHCONFERENCEBASEINFOEND			0x0004  // ȡ�û��������Ϣ����
// �ϴ�������MCU
#define 	CONF_COMMAND_USERLOGIN							0x0005	// �û���¼
#define     CONF_COMMAND_FETCHCONFERENCEUSERINFO			0x0006  // ȡ�û����û���Ϣ					// temp

#define 	CONF_COMMAND_CHANGENAME							0x0007	// �ı��û����ƣ����ã�
#define 	CONF_COMMAND_CHANGEPASSWORD						0x0008	// �ı��û����루���ã�

#define 	CONF_COMMAND_CHANGECONFERENCETEMPLET			0x0009	// �ı����ģ�壨���飩
#define 	CONF_COMMAND_ALLOWKINESCOPE						0x000A	// ����¼�񣨻���͸��ˣ�
#define 	CONF_COMMAND_FORBIDKINESCOPE					0x000B	// ������¼�񣨻���͸��ˣ�
#define 	CONF_COMMAND_ALLOWCONTROL						0x000C	// ������ƣ�����͸��ˣ�
#define 	CONF_COMMAND_FORBIDCONTROL						0x000D	// ��������ƣ�����͸��ˣ�
#define 	CONF_COMMAND_SETTALK							0x000E	// �������ã�����͸��ˣ�
#define 	CONF_COMMAND_ISSUEBULL							0x000F	// �򿪹��棨���飩
#define 	CONF_COMMAND_CLOSEBULL							0x0010	// �رչ��棨���飩
#define 	CONF_COMMAND_SETBULL							0x0011	// ���ù������ݣ����飩

#define 	CONF_COMMAND_ALLOWSPEAK							0x0012	// �����ݽ�
#define 	CONF_COMMAND_CLOSESPEAK							0x0013	// �ر��ݽ�
#define 	CONF_COMMAND_ASKSPEAK							0x0014	// �����ݽ�

#define 	CONF_COMMAND_CHANGUSERMICVIDEOINFO				0x0015	// �ı�����Ƶ��ʽ�����ˣ�

#define		CONF_COMMAND_INCEPTVIDEO						0x0016  // ������Ƶ
#define		CONF_COMMAND_CLOSEVIDEO							0x0017  // �ر���Ƶ
#define		CONF_COMMAND_SETBROADCASTVIDEO					0x0018  // �㲥��Ƶ
#define		CONF_COMMAND_CLOSEBROADCASTVIDEO				0x0019  // �رչ㲥��Ƶ
#define		CONF_COMMAND_INCEPTSOUND						0x001A  // ������Ƶ
#define		CONF_COMMAND_CLOSEINCEPTSOUND					0x001B  // �ر���Ƶ
#define		CONF_COMMAND_SETBROADCASTSOUND					0x001C  // �㲥��Ƶ
#define		CONF_COMMAND_CLOSEBROADCASTSOUND				0x001D  // �رչ㲥��Ƶ

#define		CONF_COMMAND_SOUNDDRIVERITEM					0x001E  // ��Ƶ�豸����ˣ�
#define		CONF_COMMAND_VIDEODRIVERITEM					0x001F  // ��Ƶ�豸����ˣ�

#define		CONF_COMMAND_FRAMENO							0x0020	// ��ʾ�����������飩

#define		CONF_COMMAND_OPENTALKOVER						0x0021	// ������
#define		CONF_COMMAND_CLOSETALKOVER						0x0022	// �ر�����
#define		CONF_COMMAND_BROADCASTWB						0x0023  // �㲥�װ�
#define		CONF_COMMAND_CLOSEWB							0x0024  // �رհװ�
#define		CONF_COMMAND_BROADCASTDESKTOP					0x0025  // �㲥����
#define		CONF_COMMAND_CLOSEDESKTOP						0x0026  // �ر�����

#define		CONF_COMMAND_FULLWIN							0x0027  // ��������
#define		CONF_COMMAND_CONTROLCOMMAND						0x0028	// ��̨����
#define		CONF_COMMAND_CONTROLSPEED						0x0029	// ��̨�ٶ�
#define		CONF_COMMAND_SWAPPOSITION						0x002A	// ��������
#define		CONF_COMMAND_VIDEOORDER							0x002B	// ��ƵԤ��
#define		CONF_COMMAND_ASKTOPROLOCUTOR					0x002C	// �����Ϊ������
#define		CONF_COMMAND_INVITEUSER							0x002D	// �����ѵ�½����Ա�λ�

#define 	CONF_COMMAND_ALLOWUSEWHITEBOARD					0x002E	// ����ʹ�ðװ壨����͸��ˣ�
#define 	CONF_COMMAND_FORBIDUSEWHITEBOARD				0x002F	// ������ʹ�ðװ壨����͸��ˣ�
 
#define 	CONF_COMMAND_OPENFLOATWIN						0x0030	// �򿪸����������飩
#define 	CONF_COMMAND_CLOSEFLOATWIN						0x0031	// �رո����������飩
#define 	CONF_COMMAND_SETFLOATWINRECT					0x0032	// ���ø�����λ�ã����飩

#define 	CONF_COMMAND_SETBANDWIDTH						0x0033	// ���ƵĴ������飩

#define     CONF_COMMAND_FETCHCONFERENCESYNCHRONIZATION		0x0034  // ȡ�û���ͬ����Ϣ��ֻ�ϴ����ϲ�MCU���������ݣ�

#define 	CONF_COMMAND_SETWATCHUSER						0x0035	// ������Ա�����飩
#define 	CONF_COMMAND_CLOSEWATCHUSER						0x0036	// �رռ����Ա�����飩
#define		CONF_COMMAND_ALLOWWATCHUSERCONTROL				0x0037	// ������Ա���ƣ����飩
#define		CONF_COMMAND_FORBIDWATCHUSERCONTROL				0x0038	// ��������Ա���ƣ����飩

#define 	CONF_COMMAND_SETFULLSCREEN						0x0039	// �蹲����Ļȫ�������飩
#define 	CONF_COMMAND_CLOSEFULLSCREEN					0x003A	// �ر�ȫ����Ļ�����飩

#define 	CONF_COMMAND_TESTMCUBANDWIDTHSTART				0x003B	// �����������ʼ
#define 	CONF_COMMAND_TESTMCUBANDWIDTHDATA				0x003C	// ���������������
#define 	CONF_COMMAND_TESTMCUBANDWIDTHEND				0x003D	// ��������������

#define 	CONF_COMMAND_SPURNSOMEBODY						0x003E	// ����
#define		CONF_COMMAND_ISENABLECONFERENCETOPIC			0x003F	// �Ƿ���ʾ�������
#define		CONF_COMMAND_ISALLOWENTERCONFERENCE				0x0040	// �Ƿ�����������
#define		CONF_COMMAND_ISENABLEASKTOPROLOCUTOR			0x0041	// �Ƿ���ʾ���뷢����
#define		CONF_COMMAND_ISENABLEFLOATWIN					0x0042	// �Ƿ����긡������
#define		CONF_COMMAND_ISSETPROLOCUTOR					0x0043	// �Ƿ����÷�����
#define		CONF_COMMAND_DELPROLOCUTOR						0x0044	// ɾ��������

#define		CONF_COMMAND_P2PDATA							0x0048	// ���͵�Ե�����
#define		CONF_COMMAND_ISSCREENCONTROL					0x0049	// �Ƿ�����������Ļ����

#define 	CONF_COMMAND_CONFERENCEINITMSGSPOKEMAN			0x0055	// ȡ���ݽ��˽�������ʼ����Ϣ

// �û��������ĳ�ʼ����Ϣ����
#define     CONF_COMMAND_SENDCONFERENCETEMPLET				0x1001  // ���ͻ���ģ��
#define     CONF_COMMAND_SENDCONFERENCEMEMBER				0x1002  // ���ͻ����Ա��ĳ���飩
#define     CONF_COMMAND_SENDCONFERENCEMEMBERPRESENCE		0x1003  // �������߻����Ա
#define     CONF_COMMAND_SENDCONFERENCEMEMBERENTER			0x1004  // ���ͽ�������Ա   
#define		CONF_COMMAND_SENDTALKOVER						0x1005	// ������������
#define		CONF_COMMAND_SENDTALKOVERDATA					0x1006	// ����������ʷ����
#define		CONF_COMMAND_SENDASKTOPROLOCUTORLIST			0x1007	// �������뷢�����б�


// MCU֮��ĳ�ʼ����Ϣ����
#define     CONF_COMMAND_SENDINITCONFERENCETEMPLET			0x2001  // ���ͳ�ʼ������ģ��
#define     CONF_COMMAND_SENDINITCONFERENCEMEMBER			0x2002  // ���ͳ�ʼ�������Ա��ȫ�����飩
#define		CONF_COMMAND_SENDINITVIDEOCHANNELID				0x2003  // ���ͳ�ʼ����Ƶͨ��ID
#define		CONF_COMMAND_SENDINITAUDIOCHANNELID				0x2004  // ���ͳ�ʼ����Ƶͨ��ID
#define		CONF_COMMAND_SENDINITWBCHANNELID				0x2005  // ���ͳ�ʼ����Ƶͨ��ID
#define		CONF_COMMAND_SENDINITDESKTOPCHANNELID			0x2006  // ���ͳ�ʼ������ͨ��ID
#define		CONF_COMMAND_SENDINITTEMPLETDICTIONARY			0x2007  // ���ͳ�ʼ��ģ���ֵ��

#define		CONF_COMMAND_DISCONNECTEDMCU					0x2008  // ĳmcu�Ͽ�����
#define		CONF_COMMAND_SENDINITEND						0x2009  // ���ͳ�ʼ�����ݽ���


// �㲥
#define     CONF_COMMAND_BROADCAST_MCULOGIN					0x3001  // MCU��½״̬�㲥		
#define     CONF_COMMAND_BROADCAST_MCULOGOUT				0x3002  // MCU��½״̬�㲥						
#define 	CONF_COMMAND_BROADCAST_USERLOGIN				0x3003	// �û���¼״̬�㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_USERLOGOUT				0x3004	// �û��˳�״̬�㲥�����·�ɢ��
#define 	CONF_COMMAND_BROADCAST_CONFERENCELOGIN			0x3005	// �û���¼����״̬�㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_CONFERENCELOGOUT			0x3006	// �û��˳�����״̬�㲥�����·�ɢ��

#define		CONF_COMMAND_BROADCAST_P2PDATA					0x3007	// ���͵�Ե�㲥����

#define 	CONF_COMMAND_BROADCAST_OPENTALKOVER				0x4001	// �򿪻������۹㲥					
#define 	CONF_COMMAND_BROADCAST_CLOSETALKOVER			0x4002	// �رջ������۹㲥						
#define 	CONF_COMMAND_BROADCAST_TALKOVERDATA				0x4003	// �����������ݹ㲥�����·�ɢ��

#define 	CONF_COMMAND_BROADCAST_CHANGECONFERENCETEMPLET	0x4004	// �ı����ģ��㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_CHANGENAME				0x4005	// �ı��û����㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_ALLOWKINESCOPE			0x4006	// ����¼��㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_FORBIDKINESCOPE			0x4007	// ������¼��㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_ALLOWCONTROL				0x4008	// ������ƹ㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_FORBIDCONTROL			0x4009	// ��������ƹ㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_SETTALK					0x400A	// �������ù㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_ISSUEBULL				0x400B	// �򿪹���㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_CLOSEBULL				0x400C	// �رչ���㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_SETBULL					0x400D	// ���ù������ݹ㲥���Զ����£�

#define 	CONF_COMMAND_BROADCAST_ALLOWSPEAK				0x400E	// �����ݽ��㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_CLOSESPEAK				0x400F	// �ر��ݽ��㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_ASKSPEAK					0x4010	// �����ݽ��㲥��ֻ�������ˣ�

#define 	CONF_COMMAND_BROADCAST_CHANGUSERMICVIDEOINFO	0x4011	// �ı�����Ƶ��ʽ�㲥��ֻ�������ˣ�

#define		CONF_COMMAND_BROADCAST_SETBROADCASTVIDEO		0x4012  // ��Ƶ�㲥
#define		CONF_COMMAND_BROADCAST_CLOSEBROADCASTVIDEO		0x4013  // �ر���Ƶ�㲥
#define		CONF_COMMAND_BROADCAST_SETBROADCASTSOUND		0x4014  // ��Ƶ�㲥
#define		CONF_COMMAND_BROADCAST_CLOSEBROADCASTSOUND		0x4015  // �ر���Ƶ�㲥

#define		CONF_COMMAND_BROADCAST_SOUNDDRIVERITEM			0x4016  // ��Ƶ�豸��㲥
#define		CONF_COMMAND_BROADCAST_VIDEODRIVERITEM			0x4017  // ��Ƶ�豸��㲥

#define		CONF_COMMAND_BROADCAST_FRAMENO					0x4018	// ��ʾ�������㲥
#define		CONF_COMMAND_BROADCAST_WB						0x4019	// �򿪰װ�㲥
#define		CONF_COMMAND_BROADCAST_CLOSEWB					0x401A  // �رհװ�㲥
#define		CONF_COMMAND_BROADCAST_DESKTOP					0x401B	// ������㲥
#define		CONF_COMMAND_BROADCAST_CLOSEDESKTOP				0x401C  // �ر�����㲥

#define		CONF_COMMAND_BROADCAST_FULLWIN					0x401D  // ���������㲥							
#define		CONF_COMMAND_BROADCAST_SWAPPOSITION				0x401E  // ���������㲥

//////////////////////////////////////////////////////////////////////////
#define		CONF_COMMAND_BROADCAST_DELETEMCU				0x401F  // MCUɾ���㲥
#define		CONF_COMMAND_BROADCAST_UPDATEMCU				0x4020  // MCU���¹㲥
#define		CONF_COMMAND_BROADCAST_INSERTMCU				0x4021  // MCU����㲥
#define		CONF_COMMAND_BROADCAST_DELETECONFERENCE			0x4022  // ����ɾ���㲥
#define		CONF_COMMAND_BROADCAST_UPDATECONFERENCE			0x4023  // ������¹㲥
#define		CONF_COMMAND_BROADCAST_INSERTCONFERENCE			0x4024  // �������㲥
#define		CONF_COMMAND_BROADCAST_DELETECONFERENCEUSER		0x4025  // �����Աɾ���㲥
#define		CONF_COMMAND_BROADCAST_UPDATECONFERENCEUSER		0x4026  // �����Ա���¹㲥
#define		CONF_COMMAND_BROADCAST_INSERTCONFERENCEUSER		0x4027  // �����Ա����㲥
#define		CONF_COMMAND_BROADCAST_DELETETEMPLET			0x4028  // ����ģ��ɾ���㲥
#define		CONF_COMMAND_BROADCAST_UPDATETEMPLET			0x4029  // ����ģ����¹㲥
#define		CONF_COMMAND_BROADCAST_INSERTTEMPLET			0x402A  // ����ģ�����㲥
//////////////////////////////////////////////////////////////////////////

#define		CONF_COMMAND_BROADCAST_FREEVIDEOCHANNEL			0x402B	// �ر���Ƶͨ��
#define		CONF_COMMAND_BROADCAST_FREEAUDIOCHANNEL			0x402C	// �ر���Ƶͨ��

#define 	CONF_COMMAND_BROADCAST_VIDEOORDER				0x402D	// ��ƵԤ�ù㲥��ֻ�������ˣ�
#define 	CONF_COMMAND_BROADCAST_ASKTOPROLOCUTOR			0x402E	// �����Ϊ�����˹㲥

#define 	CONF_COMMAND_BROADCAST_ALLOWUSEWHITEBOARD		0x402F	// ����ʹ�ðװ�㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_FORBIDUSEWHITEBOARD		0x4030	// ������ʹ�ðװ�㲥���Զ����£�

#define		CONF_COMMAND_BROADCAST_ADDNEWAUDIOCHANNEL		0x4031  // ������Ƶͨ���㲥
#define		CONF_COMMAND_BROADCAST_ADDNEWVIDEOCHANNEL		0x4032  // ������Ƶͨ���㲥
#define		CONF_COMMAND_BROADCAST_ADDNEWWBCHANNEL			0x4033  // �����װ�ͨ���㲥
#define		CONF_COMMAND_BROADCAST_ADDNEWDESKTOPCHANNEL		0x4034  // ��������ͨ���㲥

#define		CONF_COMMAND_BROADCAST_OPENFLOATWIN				0x4035  // �򿪸������㲥���Զ����£��������ˣ�
#define		CONF_COMMAND_BROADCAST_CLOSEFLOATWIN			0x4036  // �رո������㲥���Զ����£��������ˣ�
#define		CONF_COMMAND_BROADCAST_SETFLOATWINRECT			0x4037  // ���ø�����λ�ù㲥���Զ����£��������ˣ�

#define		CONF_COMMAND_BROADCAST_SETBANDWIDTH				0x4038  // ���ƵĴ���㲥��ֻ�������ˣ�

#define 	CONF_COMMAND_BROADCAST_SETWATCHUSER				0x4039	// ������Ա�㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_CLOSEWATCHUSER			0x403A  // �رռ����Ա�㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_ALLOWWATCHUSERCONTROL	0x403B	// ������Ա���ƹ㲥���Զ����£�
#define 	CONF_COMMAND_BROADCAST_FORBIDWATCHUSERCONTROL	0x403C	// ��������Ա���ƹ㲥���Զ����£�

#define		CONF_COMMAND_BROADCAST_SETFULLSCREEN			0x403D  // �蹲����Ļȫ���㲥���Զ����£��������ˣ�
#define		CONF_COMMAND_BROADCAST_CLOSEFULLSCREEN			0x403E  // �ر�ȫ����Ļ�㲥���Զ����£��������ˣ�

#define		CONF_COMMAND_BROADCAST_FREEWBCHANNEL			0x403F	// �رհװ�ͨ��
#define		CONF_COMMAND_BROADCAST_FREEDESKTOPCHANNEL		0x4040	// �ر�����ͨ��
#define		CONF_COMMAND_BROADCAST_FREEFILECHANNEL			0x4041	// �ر��ļ�ͨ��

#define		CONF_COMMAND_BROADCAST_ISENABLECONFERENCETOPIC	0x4042	// �Ƿ���ʾ�������
#define		CONF_COMMAND_BROADCAST_ISALLOWENTERCONFERENCE	0x4043	// �Ƿ�����������
#define		CONF_COMMAND_BROADCAST_ISENABLEASKTOPROLOCUTOR	0x4044	// �Ƿ���ʾ���뷢����
#define		CONF_COMMAND_BROADCAST_ISENABLEFLOATWIN			0x4045	// �Ƿ����긡������
#define		CONF_COMMAND_BROADCAST_ISSETPROLOCUTOR			0x4046	// �Ƿ����÷�����
#define		CONF_COMMAND_BROADCAST_DELPROLOCUTOR			0x4047	// ɾ��������

#define		CONF_COMMAND_BROADCAST_TOS						0x4048	// QOS

#define		CONF_COMMAND_BROADCAST_DISCONNECTEDMCU			0x4049  // ĳmcu�Ͽ�����(�Ż���)

#define     CONF_COMMAND_BROADCAST_UPDATECONFERENCEALL      0x404A

#define		CONF_COMMAND_BROADCAST_DELETEAUDIOCHANNEL		0x404B
#define		CONF_COMMAND_BROADCAST_DELETEVIDEOCHANNEL		0x404C
#define		CONF_COMMAND_BROADCAST_DELETEDESKTOPCHANNEL		0x404D
#define		CONF_COMMAND_BROADCAST_DELETEFILECHANNEL		0x404E
#define		CONF_COMMAND_BROADCAST_DELETEWBCHANNEL			0x404F

#define		CONF_COMMAND_BROADCAST_ISSCREENCONTROL			0x4052	// �Ƿ�����������Ļ����


// ��Ӧ����
#define 	CONF_COMMAND_CHANGENAME_REP						0x5001	// �ı��û����Ʒ���
#define 	CONF_COMMAND_CHANGEPASSWORD_REP					0x5002	// �ı��û����뷵��
#define 	CONF_COMMAND_ALLOWKINESCOPE_REP					0x5003	// ����¼�񷵻أ����ˣ�
#define 	CONF_COMMAND_FORBIDKINESCOPE_REP				0x5004	// ������¼�񷵻أ����ˣ�
#define 	CONF_COMMAND_ALLOWCONTROL_REP					0x5005	// ������Ʒ��أ����ˣ�
#define 	CONF_COMMAND_FORBIDCONTROL_REP					0x5006	// ��������Ʒ��أ����ˣ�
#define 	CONF_COMMAND_SETTALK_REP						0x5007	// �������÷��أ����ˣ�

#define 	CONF_COMMAND_CHANGUSERMICVIDEOINFO_REP			0x5008	// �ı�����Ƶ��ʽ����

#define		CONF_COMMAND_INCEPTVIDEO_REP					0x5009  // ������Ƶ���ضԷ�
#define		CONF_COMMAND_CLOSEVIDEO_REP						0x500A  // �ر���Ƶ���ضԷ�
#define		CONF_COMMAND_INCEPTSOUND_REP					0x500B  // ������Ƶ���ضԷ�
#define		CONF_COMMAND_CLOSEINCEPTSOUND_REP				0x500C  // �ر���Ƶ���ضԷ�

#define		CONF_COMMAND_INCEPTVIDEO_SELFREP				0x500D  // ������Ƶ�����Լ�
#define		CONF_COMMAND_INCEPTSOUND_SELFREP				0x500E  // ������Ƶ�����Լ�

#define		CONF_COMMAND_FULLWIN_REP						0x500F  // ������������
#define		CONF_COMMAND_CONTROLCOMMAND_REP					0x5010	// ��̨���Ʒ���
#define		CONF_COMMAND_CONTROLSPEED_REP					0x5011	// ��̨�ٶȷ���

#define		CONF_COMMAND_INVITEUSER_REP 					0x5012	// �����ѵ�½����Ա�λ᷵��

#define 	CONF_COMMAND_ALLOWUSEWHITEBOARD_REP				0x5013	// ����ʹ�ðװ巵�أ����ˣ�
#define 	CONF_COMMAND_FORBIDUSEWHITEBOARD_REP			0x5014	// ������ʹ�ðװ巵�أ����ˣ�

#define 	CONF_COMMAND_TESTMCUBANDWIDTH_REP				0x5015	// �������������

#define 	CONF_COMMAND_SPURNSOMEBODY_REP					0x5016	// ���˷���

#define		CONF_COMMAND_P2PDATA_REP						0x5017	//	��Ե����ݻص�

#define		CONF_COMMAND_CHANGUSERMICVIDEOINFO_SPOKEMAN		0x5018
#define		CONF_COMMAND_SOUNDDRIVERITEM_SPOKEMAN			0x5019
#define		CONF_COMMAND_VIDEODRIVERITEM_SPOKEMAN			0x5020


// �ļ��ַ�
#define		CONF_COMMAND_STARTFILE							0x6000  // ��ʼ�ļ��ַ�
#define		CONF_COMMAND_CLOSEFILE							0x6001  // �ر��ļ��ַ�
#define		CONF_COMMAND_SENDINITFILECHANNELID				0x6002  // ���ͳ�ʼ���ļ��ַ�ͨ��ID
#define		CONF_COMMAND_BROADCAST_STARTFILE				0x6003	// �ַ��ļ��㲥
#define		CONF_COMMAND_BROADCAST_CLOSEFILE				0x6004  // �ر��ļ��ַ��㲥
#define		CONF_COMMAND_BROADCAST_ADDNEWFILECHANNEL		0x6005  // �����ļ��ַ�ͨ���㲥
#define		CONF_COMMAND_FILEEXIST_REP						0x6005  // �ļ��Ѵ���

//////////////////////////////////////////////////////////////////////////
//#ifdef NETTVANDBROADCAST
#define     CONF_COMMAND_FETCHCHANNELINFO					0x7001  // ȡ��Ƶ��������Ϣ
#define     CONF_COMMAND_FETCHCHANNELINFOEND				0x7002  // ȡ��Ƶ��������Ϣ����
#define		CONF_COMMAND_SETTVCHANNEL						0x7003  // ���õ��ӻ�Ƶ��

#define		CONF_COMMAND_BROADCAST_DELETECHANNEL			0x7004  // ����Ƶ��ɾ���㲥
#define		CONF_COMMAND_BROADCAST_UPDATECHANNEL			0x7005  // ����Ƶ�����¹㲥
#define		CONF_COMMAND_BROADCAST_INSERTCHANNEL			0x7006  // ����Ƶ������㲥

#define		CONF_COMMAND_BROADCAST_SETTVCHANNEL				0x7007  // ���õ��ӻ�Ƶ���㲥
#define		CONF_COMMAND_BROADCAST_CHANNELCHARGER			0x7008  // ���õ��ӻ�Ƶ���㲥
//#endif
//////////////////////////////////////////////////////////////////////////


// �������
typedef enum SignalType {
	_eMessage,		// ��Ϣ
	_eVideo		// ��Ƶ
	//_eAudio,		// ��Ƶ
	//_eDesktop,		// ����
	//_eWhiteboard,	// �װ�
	//_eFile			// �ļ�
} ESignalType;

// �������
typedef enum DirectionType {
	_eSingle,		// ��һ
	_eBroadcast		// �㲥
} EDirectionType;

// ����ͷ���������¼��ݣ�
typedef struct SignalHeader {
	ESignalType 	_eSignalType;		// ��������
	UINT32			_iSignalBodyLength;	// �������ֳ�
} _tSignalHeader;

// �����壨δ���壩
typedef struct SignalBody {
} _tSignalBody;

// ����ͷ�ֳ�
const UINT16 c_tSignalHeaderLen = sizeof(SignalHeader);

// ��Ϣͷ
typedef struct MessageHeader {
	EDirectionType	_eDirectionType;	// ��������
	UINT32			_iCommandID;		// ����ID���ο��ļ���ComDefine.h�����粿�ֲο�����	
	UINT32			_iMcuID;			// �������_iMcuIDΪ�����mcuID�����������ʾ��ǰ����·��������ÿһ����1����ʼֵΪ0��
//  ������Ϣ�壺_lMcuID1..._lMcuIDnΪmcuID����·�����У�����mcuID������ɣ�����Ŀ�ĵأ����һ����
//	UINT32	_lMcuID1;					// ��һ��mcuID��������mcu����һ��mcu��
//	...
//	UINT32	_lMcuIDn;					// Ŀ��mcuID����sessionID�������mcuID��sessionID��һ���£�ע�����ݿ�ķ��䣩
} _tMessageHeader;

// ��Ϣͷ�ֳ�
const UINT16 c_tMessageHeaderLen = sizeof(MessageHeader);

// ��Ϣ�壨δ���壩
// �ο��ļ���DataDefine.h

// ͨ������ͷ���װ��޴�ͷ�������������ȵ�����mcu�ٹ㲥���������߻�����Ա��
typedef struct ChannelHeader {
	EDirectionType	_eDirectionType;	// ��������
	UINT32			_cMcuIDCount;		// mcu��������_eDirectionTypeΪ_eSingle����ΪҪ�鲥����������Ϊ_eBroadcast����Ϊ��Ҫ�鲥������
	//  ������Ϣ�壺_lMcuID1..._lMcuIDnΪmcuID�鲥���ϣ�����mcuID���
	//	UINT32	_lMcuID1;					// ��һ��mcuID
	//	...
	//	UINT32	_lMcuIDn;					// ��n��mcuID����sessionID�������mcuID��sessionID��һ���£�ע�����ݿ�ķ��䣩
} _tChannelHeader;


#endif 
