
//========================================================================================
//版权所有: 版权所有(C) 2008
//系统名称: 
//作　　者: 
//创建日期: 
//功能说明: 数据传输服务器内核接口类定义
//

#pragma once

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS IHPDTSNotify
{
public:
	IHPDTSNotify(void){};
	virtual~ IHPDTSNotify(void){};
public:
	virtual void onDTSNetDataNotify(unsigned long ulSessionID,const char* pData,int nLen)=0;  //回调网络数据
	virtual void onDTSUIDataNotify(const char* pData,int nLen)=0;							  //回调界面数据
};


//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS IHPDTS
{
public:
	IHPDTS(void){};
	virtual~IHPDTS(void){};

	virtual void Init(void) = 0;
	virtual void Release(void) = 0;
public:
	virtual void processUIData(const char* pData,int nLen)=0;								//处理界面数据
	virtual void processDTSData(unsigned long ulSessionID,const char* pData,int nLen)=0;	//处理网络数据
	virtual void AddDTSSession(unsigned long ulSessionID,bool bHost/*此ulSessionID是否为Host Server*/)=0; //增加DTS连接
	virtual void RemoveDTSSession(unsigned long ulSessionID)=0;								//删除DTS连接
};

//---------------------------------------------------------------------------------------
AFX_EXT_CLASS IHPDTS*CreateIHPDTS(IHPDTSNotify& rIHPDTSNotify,bool bUI/*是否有UI*/);

AFX_EXT_CLASS void HPDTSInit(const char* cszTemPath/*接收文件临时目录*/);	
AFX_EXT_CLASS void HPDTSUnInit(void);
AFX_EXT_CLASS void HPDTSSetSavePath(const char* cszSavePath);//客户端设置文件保存目录,可重复调用
AFX_EXT_CLASS const char* GetFileTemPath(void);
AFX_EXT_CLASS const char* GetFileSavePath(void);

