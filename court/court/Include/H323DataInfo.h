// H323DataInfo.h

#if !defined(_H323DATAINFO_H__20091117_111436__INCLUDED_HHJ_)
#define _H323DATAINFO_H__20091117_111436__INCLUDED_HHJ_

// **************************************************************
//  H323DataInfo Interface   version:  1.0   ·  date: 11/17/2009
//  -------------------------------------------------------------
//  H323 会议数据交互接口
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


// 函数参数说明:
// pbData:      当前包的数据内存块
// dwDataLen:    当前包的数据长度
// dwChannelNO:    虚传输通道, 视音频的唯一标识
// pszName:        视频信息（会场名称和对应的视频卡号）


//////////////////////////////////////////////////////////////////////////
//    发送数据端回调接口， 需继承
//////////////////////////////////////////////////////////////////////////
interface ISendAVdieoDataInfoCallBack
{
public:
    ISendAVdieoDataInfoCallBack(){};
    virtual ~ISendAVdieoDataInfoCallBack(){};
};


//////////////////////////////////////////////////////////////////////////
//    发送数据端调用接口 (音频和视频要分别创建对象的)
//////////////////////////////////////////////////////////////////////////
interface ISendAVdieoDataInfo
{
public:
    ISendAVdieoDataInfo(){};
    virtual ~ISendAVdieoDataInfo(){};

public:
    // 释放接口 (在 CloseAudioChannel 或 CloseVideoChannel 之前调用)
    virtual void ReleaseSendAVdieoDataInfo(DWORD dwChannelNO) = 0;

	// 释放音频数据包接口 (在 CloseAudioChannel 或 CloseVideoChannel 之前调用)
	virtual void ReleaseSendAudioDataInfo(DWORD dwChannelNO) = 0;

	// 释放视频数据包接口 (在 CloseAudioChannel 或 CloseVideoChannel 之前调用)
	virtual void ReleaseSendVideoDataInfo(DWORD dwChannelNO) = 0;


    // 写音频数据包
	// pbData:		当前包的数据内存块
	// dwDataLen:	当前包的数据长度
	// dSamples:	样本
	// dwChannelNO:	虚传输通道, 视音频的唯一标识
    virtual void SetAudioData(BYTE* pbData, WORD wDataLen, double dSamples, DWORD dwChannelNO) = 0;

    // 写视频数据包
	// pbData:		当前包的数据内存块
	// nWidth:		视频宽度
	// nHeight：	视频高度
	// nFrameType：	视频格式类型 0: RGB24,  1: RGB16, 2: YV12,  3: YUYV;
	// dwChannelNO:	虚传输通道, 视音频的唯一标识
    virtual void SetVideoData(BYTE* pbData, int nWidth, int nHeight, int nFrameType, DWORD dwChannelNO) = 0;

    // 设置视频信息参数
    // pszName:        视频信息的名称
    // wNameLen:    名称的长度
    //virtual void SetInfoPparameter(char* pszName, WORD wNameLen, DWORD dwChannelNO) = 0;
};


//////////////////////////////////////////////////////////////////////////
//    接收数据端回调接口， 需继承
//////////////////////////////////////////////////////////////////////////
interface IReceiveAVdieoDataInfoCallBack
{
public:
    IReceiveAVdieoDataInfoCallBack():m_lContext(-1){};
    virtual ~IReceiveAVdieoDataInfoCallBack(){};

public:
    // 回调音频数据包
	// pbData:		当前包的数据内存块
	// dwDataLen:	当前包的数据长度
	// dSamples:	样本
	// dwChannelNO:	虚传输通道, 视音频的唯一标识
    // lContext:	应用程序上下文，由客户调用SetAppContext设置，此处原封不动传入到回调函数中
    virtual void ReceiveAudioDataInfoCallBack(BYTE* &pbData, WORD& wDataLen, double dSamples, DWORD dwChannelNO, LONG lContext) = 0;

    // 回调视频数据包
	// pbData:		当前包的数据内存块
	// nWidth:		视频宽度
	// nHeight：	视频高度
	// nFrameType：	视频格式类型 0: RGB24,  1: RGB16, 2: YV12,  3: YUYV;
    // lContext:	应用程序上下文，由客户调用SetAppContext设置，此处原封不动传入到回调函数中
    virtual void ReceiveVideoDataInfoCallBack(BYTE* &pbData, int nWidth, int nHeight, int nFrameType, DWORD dwChannelNO, LONG lContext) = 0;

    // 回调视频辅流数据包
	// pbData:		当前包的数据内存块
	// nWidth:		视频宽度
	// nHeight：	视频高度
	// nFrameType：	视频格式类型 0: RGB24,  1: RGB16, 2: YV12,  3: YUYV;
	// lContext:	应用程序上下文，由客户调用SetAppContext设置，此处原封不动传入到回调函数中
    virtual void ReceiveVideoAideDataInfoCallBack(BYTE* &pbData, int nWidth, int nHeight, int nFrameType, DWORD dwChannelNO, LONG lContext) = 0;

    void SetAppContext(LONG lContext)
    {
        m_lContext = lContext;
    }
protected:
    LONG m_lContext;   //每一个IReceiveAVdieoDataInfoCallBack使用一个AppContex，统一处理音视频和辅流，由客户设置
};


//////////////////////////////////////////////////////////////////////////
//    接收数据端调用接口 (音频和视频要分别创建对象的)
//////////////////////////////////////////////////////////////////////////
interface IReceiveAVdieoDataInfo
{
public:
    IReceiveAVdieoDataInfo(){};
    virtual ~IReceiveAVdieoDataInfo(){};

public:
    // 释放接口
    virtual void ReleaseReceiveAVdieoDataInfo(DWORD dwChannelNO) = 0;

	// 释放音频数据包接口
	virtual void ReleaseReceiveAudioDataInfo(DWORD dwChannelNO) = 0;

	// 释放视频数据包接口
	virtual void ReleaseReceiveVideoDataInfo(DWORD dwChannelNO) = 0;

    // 删除音频数据包
    virtual void DeleteAudioData(DWORD dwChannelNO) = 0;

    // 删除视频数据包
    virtual void DeleteVideoData(DWORD dwChannelNO) = 0;

    // 获取视频信息参数
    // pszName:        视频信息
    virtual void GetInfoPparameter(char* &pszName, DWORD dwChannelNO) = 0;
};

//////////////////////////////////////////////////////////////////////////
// 管理模块接口， 程序启动时创建的
//////////////////////////////////////////////////////////////////////////
interface IHLAVdieoDataInfoCallBack
{
public:
    IHLAVdieoDataInfoCallBack(){};
    virtual ~IHLAVdieoDataInfoCallBack(){};

public:
    // 创建音频的传输通道回调接口    
    // nSendFlage:     0 表示接收音频， 1 表示发送音频
    // dwChannelNO:  音频的唯一标识，区分是发送的哪个音频流
    // lContext:   应用程序上下文，由用户创建通道时传入，此处原封返回
	// nSponsor:	发起人, 用来判断是由哪个模块提出创建通道申请, 另一个模块创建相对应的通道 1  表示服务的管理模块，0  表示客户的管理模块
	// nCardNO:		表示第几路流，0 : 主流  1: 第一路流（辅流）
    virtual void CreateAudioChannelCallBack(int nSendFlage, DWORD dwChannelNO, LONG lContext, int nSponsor, int nCardNO = 0) = 0;

    // 创建视频的传输通道回调接口    
    // nSendFlage:   0 表示接收视频， 1 表示发送视频
    // dwChannelNO:  视频的唯一标识，区分是发送的哪个视频流
    // lContext:   应用程序上下文，由用户创建通道时传入，此处原封返回
	// nSponsor:	发起人, 用来判断是由哪个模块提出创建通道申请, 另一个模块创建相对应的通道 1  表示服务的管理模块，0  表示客户的管理模块
	// nCardNO:		表示第几路流，0 : 主流  1: 第一路流（辅流）
    virtual void CreateVideoChannelCallBack(int nSendFlage, DWORD dwChannelNO, LONG lContext, int nSponsor, int nCardNO = 0) = 0;  

	//得到通道参数
	// nCardNO:		表示第几路流，0 : 主流  1: 第一路流（辅流）
	// nDisplayType:分辨率
	virtual void GetChannelInf(int nCardNO,int& nDisplayType) = 0;

	//设置通道参数
	// nCardNO:		表示第几路流，0 : 主流  1: 第一路流（辅流）
	// nDisplayType:分辨率
	virtual void SetChannelInf(int nCardNO,int nDisplayType) = 0;

	// 关闭音频的传输通道回调接口(用于释放相应的发送或接受数据的对象)   
	// dwChannelNO:  音频的唯一标识，区分是关闭的哪个音频流
	// lContext:	应用程序上下文，由用户定义其作用，用于扩展
	virtual void CloseAudioChannelCallBack(DWORD dwChannelNO, LONG lContext) = 0;  

	// 关闭视频的传输通道回调接口(用于释放相应的发送或接受数据的对象)     
	// dwChannelNO:  视频的唯一标识，区分是关闭的哪个视频流
	// lContext:	应用程序上下文，由用户定义其作用，用于扩展
	virtual void CloseVideoChannelCallBack(DWORD dwChannelNO, LONG lContext) = 0;  

	// 连接服务器及进入会议状态的回调信息
	// dwInfo:  信息说明标识:
		// 0: 服务器连接超时或连接错误(不能连接服务器)
		// 1: 服务器连接断开
		// 2: 密码错
		// 3: 帐号已登陆
		// 4: 服务器繁忙
		// 5: 帐号不存在或没有被分配到任何会议里
		// 6: 授权已达限制

		// 10: 帐号成功登录
		// 12: 进入会议成功通知
	virtual void ConnectedLoginInfoCallBack(DWORD dwInfo) = 0;

	// 系统退出, 就是客户点击 "X" 通知
	virtual void QuitHLAVdieoDataInfoCallBack() = 0;
};

interface IHLAVdieoDataInfo
{
public:
    IHLAVdieoDataInfo(){};
    virtual ~IHLAVdieoDataInfo(){};

public:
    // 释放该模块， 因为此模块只对应一个视频软客户端，只要释放它内部就会执行退出流程
    virtual void ReleaseHLAVdieoDataInfo() = 0;

	// 创建发送数据端调用接口
	virtual ISendAVdieoDataInfo* CreateHLSendAVdieoDataInfo(ISendAVdieoDataInfoCallBack* pICallBack, DWORD dwChannelNO) = 0;

	// 创建接收数据端调用接口
	virtual IReceiveAVdieoDataInfo* CreateHLReceiveAVdieoDataInfo(IReceiveAVdieoDataInfoCallBack* pICallBack, DWORD dwChannelNO) = 0;

    // 创建音频的传输通道    
    // nSendFlage:	0 表示接收音频， 1 表示发送音频
    // pszName:     视频信息
    // lContext:	应用程序上下文，由用户定义其作用，用于扩展
	// nSponsor:	发起人, 用来判断是由哪个模块提出创建通道申请, 另一个模块创建相对应的通道 1  表示服务的管理模块，0  表示客户的管理模块:
	// nCardNO:		表示第几路流，0 : 主流  1: 第一路流（辅流）
    virtual void CreateAudioChannel(int nSendFlage, char* pszName, LONG lContext, DWORD dwChannelNO, int nSponsor, int nCardNO = 0) = 0;

    // 创建视频的传输通道    
    // nSendFlage:	0 表示接收视频， 1 表示发送视频
    // pszName:     视频信息
    // lContext:	应用程序上下文，由用户定义其作用，用于扩展
	// nSponsor:	发起人, 用来判断是由哪个模块提出创建通道申请, 另一个模块创建相对应的通道 1  表示服务的管理模块，0  表示客户的管理模块
	// nCardNO:		表示第几路流，0 : 主流  1: 第一路流（辅流）
    virtual void CreateVideoChannel(int nSendFlage, char* pszName, LONG lContext, DWORD dwChannelNO, int nSponsor, int nCardNO = 0) = 0;  

    // 关闭音频的传输通道    
	// dwChannelNO:  音频的唯一标识，区分是关闭的哪个音频流
	// lContext:	应用程序上下文，由用户定义其作用，用于扩展
    virtual void CloseAudioChannel(DWORD dwChannelNO, LONG lContext) = 0;  

    // 关闭视频的传输通道    
	// dwChannelNO:  视频的唯一标识，区分是关闭的哪个视频流
	// lContext:	应用程序上下文，由用户定义其作用，用于扩展
    virtual void CloseVideoChannel(DWORD dwChannelNO, LONG lContext) = 0;  
};

// 创建管理模块接口    
// pICallBack    所指向的回调接口
// nMcuLevel     MCU 级别，目前只有0
// pszServerIP   服务器的IP地址
// pszUserID     用户登录的ID（用户登录帐号）
// pszPassword	 登陆密码
// nConfID       登录的会议室ID
// lContext:	 应用程序上下文，由用户定义其作用，用于扩展
// nFlage:       1  表示创建服务的管理模块，0  表示创建客户的管理模块 （服务的管理模块要在客户的管理模块前面创建）
DllExport_IH323DATAINFO IHLAVdieoDataInfo* CreateHLAVdieoDataInfo(IHLAVdieoDataInfoCallBack* pICallBack, 
                                                                  int    nMcuLevel, 
                                                                  char*  pszServerIP, 
                                                                  char*  pszUserID, 
																  char*  pszPassword,
                                                                  int    nConfID, 
																  LONG	 lContext,
                                                                  int    nFlage);

#endif