// H323DataInfo.h

#if !defined(_H323DATAINFO_H__20091117_111436__INCLUDED_HHJ_)
#define _H323DATAINFO_H__20091117_111436__INCLUDED_HHJ_

// **************************************************************
//  H323DataInfo Interface   version:  1.0   ��  date: 11/17/2009
//  -------------------------------------------------------------
//  H323 �������ݽ����ӿ�
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
//                                                 By:    HHJ
// ***************************************************************


#ifdef _H323DATAINFO_HHJ_
    #define DllExport_IH323DATAINFO __declspec(dllexport)
#else
    #define DllExport_IH323DATAINFO __declspec(dllimport) 
#endif


// ��������˵��:
// pbData:      ��ǰ���������ڴ��
// dwDataLen:    ��ǰ�������ݳ���
// dwChannelNO:    �鴫��ͨ��, ����Ƶ��Ψһ��ʶ
// pszName:        ��Ƶ��Ϣ���᳡���ƺͶ�Ӧ����Ƶ���ţ�


//////////////////////////////////////////////////////////////////////////
//    �������ݶ˻ص��ӿڣ� ��̳�
//////////////////////////////////////////////////////////////////////////
interface ISendAVdieoDataInfoCallBack
{
public:
    ISendAVdieoDataInfoCallBack(){};
    virtual ~ISendAVdieoDataInfoCallBack(){};
};


//////////////////////////////////////////////////////////////////////////
//    �������ݶ˵��ýӿ� (��Ƶ����ƵҪ�ֱ𴴽������)
//////////////////////////////////////////////////////////////////////////
interface ISendAVdieoDataInfo
{
public:
    ISendAVdieoDataInfo(){};
    virtual ~ISendAVdieoDataInfo(){};

public:
    // �ͷŽӿ� (�� CloseAudioChannel �� CloseVideoChannel ֮ǰ����)
    virtual void ReleaseSendAVdieoDataInfo(DWORD dwChannelNO) = 0;

	// �ͷ���Ƶ���ݰ��ӿ� (�� CloseAudioChannel �� CloseVideoChannel ֮ǰ����)
	virtual void ReleaseSendAudioDataInfo(DWORD dwChannelNO) = 0;

	// �ͷ���Ƶ���ݰ��ӿ� (�� CloseAudioChannel �� CloseVideoChannel ֮ǰ����)
	virtual void ReleaseSendVideoDataInfo(DWORD dwChannelNO) = 0;


    // д��Ƶ���ݰ�
	// pbData:		��ǰ���������ڴ��
	// dwDataLen:	��ǰ�������ݳ���
	// dSamples:	����
	// dwChannelNO:	�鴫��ͨ��, ����Ƶ��Ψһ��ʶ
    virtual void SetAudioData(BYTE* pbData, WORD wDataLen, double dSamples, DWORD dwChannelNO) = 0;

    // д��Ƶ���ݰ�
	// pbData:		��ǰ���������ڴ��
	// nWidth:		��Ƶ���
	// nHeight��	��Ƶ�߶�
	// nFrameType��	��Ƶ��ʽ���� 0: RGB24,  1: RGB16, 2: YV12,  3: YUYV;
	// dwChannelNO:	�鴫��ͨ��, ����Ƶ��Ψһ��ʶ
    virtual void SetVideoData(BYTE* pbData, int nWidth, int nHeight, int nFrameType, DWORD dwChannelNO) = 0;

    // ������Ƶ��Ϣ����
    // pszName:        ��Ƶ��Ϣ������
    // wNameLen:    ���Ƶĳ���
    //virtual void SetInfoPparameter(char* pszName, WORD wNameLen, DWORD dwChannelNO) = 0;
};


//////////////////////////////////////////////////////////////////////////
//    �������ݶ˻ص��ӿڣ� ��̳�
//////////////////////////////////////////////////////////////////////////
interface IReceiveAVdieoDataInfoCallBack
{
public:
    IReceiveAVdieoDataInfoCallBack():m_lContext(-1){};
    virtual ~IReceiveAVdieoDataInfoCallBack(){};

public:
    // �ص���Ƶ���ݰ�
	// pbData:		��ǰ���������ڴ��
	// dwDataLen:	��ǰ�������ݳ���
	// dSamples:	����
	// dwChannelNO:	�鴫��ͨ��, ����Ƶ��Ψһ��ʶ
    // lContext:	Ӧ�ó��������ģ��ɿͻ�����SetAppContext���ã��˴�ԭ�ⲻ�����뵽�ص�������
    virtual void ReceiveAudioDataInfoCallBack(BYTE* &pbData, WORD& wDataLen, double dSamples, DWORD dwChannelNO, LONG lContext) = 0;

    // �ص���Ƶ���ݰ�
	// pbData:		��ǰ���������ڴ��
	// nWidth:		��Ƶ���
	// nHeight��	��Ƶ�߶�
	// nFrameType��	��Ƶ��ʽ���� 0: RGB24,  1: RGB16, 2: YV12,  3: YUYV;
    // lContext:	Ӧ�ó��������ģ��ɿͻ�����SetAppContext���ã��˴�ԭ�ⲻ�����뵽�ص�������
    virtual void ReceiveVideoDataInfoCallBack(BYTE* &pbData, int nWidth, int nHeight, int nFrameType, DWORD dwChannelNO, LONG lContext) = 0;

    // �ص���Ƶ�������ݰ�
	// pbData:		��ǰ���������ڴ��
	// nWidth:		��Ƶ���
	// nHeight��	��Ƶ�߶�
	// nFrameType��	��Ƶ��ʽ���� 0: RGB24,  1: RGB16, 2: YV12,  3: YUYV;
	// lContext:	Ӧ�ó��������ģ��ɿͻ�����SetAppContext���ã��˴�ԭ�ⲻ�����뵽�ص�������
    virtual void ReceiveVideoAideDataInfoCallBack(BYTE* &pbData, int nWidth, int nHeight, int nFrameType, DWORD dwChannelNO, LONG lContext) = 0;

    void SetAppContext(LONG lContext)
    {
        m_lContext = lContext;
    }
protected:
    LONG m_lContext;   //ÿһ��IReceiveAVdieoDataInfoCallBackʹ��һ��AppContex��ͳһ��������Ƶ�͸������ɿͻ�����
};


//////////////////////////////////////////////////////////////////////////
//    �������ݶ˵��ýӿ� (��Ƶ����ƵҪ�ֱ𴴽������)
//////////////////////////////////////////////////////////////////////////
interface IReceiveAVdieoDataInfo
{
public:
    IReceiveAVdieoDataInfo(){};
    virtual ~IReceiveAVdieoDataInfo(){};

public:
    // �ͷŽӿ�
    virtual void ReleaseReceiveAVdieoDataInfo(DWORD dwChannelNO) = 0;

	// �ͷ���Ƶ���ݰ��ӿ�
	virtual void ReleaseReceiveAudioDataInfo(DWORD dwChannelNO) = 0;

	// �ͷ���Ƶ���ݰ��ӿ�
	virtual void ReleaseReceiveVideoDataInfo(DWORD dwChannelNO) = 0;

    // ɾ����Ƶ���ݰ�
    virtual void DeleteAudioData(DWORD dwChannelNO) = 0;

    // ɾ����Ƶ���ݰ�
    virtual void DeleteVideoData(DWORD dwChannelNO) = 0;

    // ��ȡ��Ƶ��Ϣ����
    // pszName:        ��Ƶ��Ϣ
    virtual void GetInfoPparameter(char* &pszName, DWORD dwChannelNO) = 0;
};

//////////////////////////////////////////////////////////////////////////
// ����ģ��ӿڣ� ��������ʱ������
//////////////////////////////////////////////////////////////////////////
interface IHLAVdieoDataInfoCallBack
{
public:
    IHLAVdieoDataInfoCallBack(){};
    virtual ~IHLAVdieoDataInfoCallBack(){};

public:
    // ������Ƶ�Ĵ���ͨ���ص��ӿ�    
    // nSendFlage:     0 ��ʾ������Ƶ�� 1 ��ʾ������Ƶ
    // dwChannelNO:  ��Ƶ��Ψһ��ʶ�������Ƿ��͵��ĸ���Ƶ��
    // lContext:   Ӧ�ó��������ģ����û�����ͨ��ʱ���룬�˴�ԭ�ⷵ��
	// nSponsor:	������, �����ж������ĸ�ģ���������ͨ������, ��һ��ģ�鴴�����Ӧ��ͨ�� 1  ��ʾ����Ĺ���ģ�飬0  ��ʾ�ͻ��Ĺ���ģ��
	// nCardNO:		��ʾ�ڼ�·����0 : ����  1: ��һ·����������
    virtual void CreateAudioChannelCallBack(int nSendFlage, DWORD dwChannelNO, LONG lContext, int nSponsor, int nCardNO = 0) = 0;

    // ������Ƶ�Ĵ���ͨ���ص��ӿ�    
    // nSendFlage:   0 ��ʾ������Ƶ�� 1 ��ʾ������Ƶ
    // dwChannelNO:  ��Ƶ��Ψһ��ʶ�������Ƿ��͵��ĸ���Ƶ��
    // lContext:   Ӧ�ó��������ģ����û�����ͨ��ʱ���룬�˴�ԭ�ⷵ��
	// nSponsor:	������, �����ж������ĸ�ģ���������ͨ������, ��һ��ģ�鴴�����Ӧ��ͨ�� 1  ��ʾ����Ĺ���ģ�飬0  ��ʾ�ͻ��Ĺ���ģ��
	// nCardNO:		��ʾ�ڼ�·����0 : ����  1: ��һ·����������
    virtual void CreateVideoChannelCallBack(int nSendFlage, DWORD dwChannelNO, LONG lContext, int nSponsor, int nCardNO = 0) = 0;  

	//�õ�ͨ������
	// nCardNO:		��ʾ�ڼ�·����0 : ����  1: ��һ·����������
	// nDisplayType:�ֱ���
	virtual void GetChannelInf(int nCardNO,int& nDisplayType) = 0;

	//����ͨ������
	// nCardNO:		��ʾ�ڼ�·����0 : ����  1: ��һ·����������
	// nDisplayType:�ֱ���
	virtual void SetChannelInf(int nCardNO,int nDisplayType) = 0;

	// �ر���Ƶ�Ĵ���ͨ���ص��ӿ�(�����ͷ���Ӧ�ķ��ͻ�������ݵĶ���)   
	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������ǹرյ��ĸ���Ƶ��
	// lContext:	Ӧ�ó��������ģ����û����������ã�������չ
	virtual void CloseAudioChannelCallBack(DWORD dwChannelNO, LONG lContext) = 0;  

	// �ر���Ƶ�Ĵ���ͨ���ص��ӿ�(�����ͷ���Ӧ�ķ��ͻ�������ݵĶ���)     
	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������ǹرյ��ĸ���Ƶ��
	// lContext:	Ӧ�ó��������ģ����û����������ã�������չ
	virtual void CloseVideoChannelCallBack(DWORD dwChannelNO, LONG lContext) = 0;  

	// ���ӷ��������������״̬�Ļص���Ϣ
	// dwInfo:  ��Ϣ˵����ʶ:
		// 0: ���������ӳ�ʱ�����Ӵ���(�������ӷ�����)
		// 1: ���������ӶϿ�
		// 2: �����
		// 3: �ʺ��ѵ�½
		// 4: ��������æ
		// 5: �ʺŲ����ڻ�û�б����䵽�κλ�����
		// 6: ��Ȩ�Ѵ�����

		// 10: �ʺųɹ���¼
		// 12: �������ɹ�֪ͨ
	virtual void ConnectedLoginInfoCallBack(DWORD dwInfo) = 0;

	// ϵͳ�˳�, ���ǿͻ���� "X" ֪ͨ
	virtual void QuitHLAVdieoDataInfoCallBack() = 0;
};

interface IHLAVdieoDataInfo
{
public:
    IHLAVdieoDataInfo(){};
    virtual ~IHLAVdieoDataInfo(){};

public:
    // �ͷŸ�ģ�飬 ��Ϊ��ģ��ֻ��Ӧһ����Ƶ��ͻ��ˣ�ֻҪ�ͷ����ڲ��ͻ�ִ���˳�����
    virtual void ReleaseHLAVdieoDataInfo() = 0;

	// �����������ݶ˵��ýӿ�
	virtual ISendAVdieoDataInfo* CreateHLSendAVdieoDataInfo(ISendAVdieoDataInfoCallBack* pICallBack, DWORD dwChannelNO) = 0;

	// �����������ݶ˵��ýӿ�
	virtual IReceiveAVdieoDataInfo* CreateHLReceiveAVdieoDataInfo(IReceiveAVdieoDataInfoCallBack* pICallBack, DWORD dwChannelNO) = 0;

    // ������Ƶ�Ĵ���ͨ��    
    // nSendFlage:	0 ��ʾ������Ƶ�� 1 ��ʾ������Ƶ
    // pszName:     ��Ƶ��Ϣ
    // lContext:	Ӧ�ó��������ģ����û����������ã�������չ
	// nSponsor:	������, �����ж������ĸ�ģ���������ͨ������, ��һ��ģ�鴴�����Ӧ��ͨ�� 1  ��ʾ����Ĺ���ģ�飬0  ��ʾ�ͻ��Ĺ���ģ��:
	// nCardNO:		��ʾ�ڼ�·����0 : ����  1: ��һ·����������
    virtual void CreateAudioChannel(int nSendFlage, char* pszName, LONG lContext, DWORD dwChannelNO, int nSponsor, int nCardNO = 0) = 0;

    // ������Ƶ�Ĵ���ͨ��    
    // nSendFlage:	0 ��ʾ������Ƶ�� 1 ��ʾ������Ƶ
    // pszName:     ��Ƶ��Ϣ
    // lContext:	Ӧ�ó��������ģ����û����������ã�������չ
	// nSponsor:	������, �����ж������ĸ�ģ���������ͨ������, ��һ��ģ�鴴�����Ӧ��ͨ�� 1  ��ʾ����Ĺ���ģ�飬0  ��ʾ�ͻ��Ĺ���ģ��
	// nCardNO:		��ʾ�ڼ�·����0 : ����  1: ��һ·����������
    virtual void CreateVideoChannel(int nSendFlage, char* pszName, LONG lContext, DWORD dwChannelNO, int nSponsor, int nCardNO = 0) = 0;  

    // �ر���Ƶ�Ĵ���ͨ��    
	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������ǹرյ��ĸ���Ƶ��
	// lContext:	Ӧ�ó��������ģ����û����������ã�������չ
    virtual void CloseAudioChannel(DWORD dwChannelNO, LONG lContext) = 0;  

    // �ر���Ƶ�Ĵ���ͨ��    
	// dwChannelNO:  ��Ƶ��Ψһ��ʶ�������ǹرյ��ĸ���Ƶ��
	// lContext:	Ӧ�ó��������ģ����û����������ã�������չ
    virtual void CloseVideoChannel(DWORD dwChannelNO, LONG lContext) = 0;  
};

// ��������ģ��ӿ�    
// pICallBack    ��ָ��Ļص��ӿ�
// nMcuLevel     MCU ����Ŀǰֻ��0
// pszServerIP   ��������IP��ַ
// pszUserID     �û���¼��ID���û���¼�ʺţ�
// pszPassword	 ��½����
// nConfID       ��¼�Ļ�����ID
// lContext:	 Ӧ�ó��������ģ����û����������ã�������չ
// nFlage:       1  ��ʾ��������Ĺ���ģ�飬0  ��ʾ�����ͻ��Ĺ���ģ�� ������Ĺ���ģ��Ҫ�ڿͻ��Ĺ���ģ��ǰ�洴����
DllExport_IH323DATAINFO IHLAVdieoDataInfo* CreateHLAVdieoDataInfo(IHLAVdieoDataInfoCallBack* pICallBack, 
                                                                  int    nMcuLevel, 
                                                                  char*  pszServerIP, 
                                                                  char*  pszUserID, 
																  char*  pszPassword,
                                                                  int    nConfID, 
																  LONG	 lContext,
                                                                  int    nFlage);

#endif