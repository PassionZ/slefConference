//IFILEDTS.h
#ifndef __IFILEDTS_H__
#define __IFILEDTS_H__

#include "StdAfx.h"


class IFileDTSNotify
{
public:
	IFileDTSNotify(void){};
	virtual~IFileDTSNotify(void){};
public:
	virtual void /*onFDTData*/onFileData(unsigned long channelId, char* data, int len)=0;
	virtual void onFileEnd(const char* cFileName)=0;
	virtual void onFileProcess(double iProcess)=0;

	virtual void processFDTRequest(unsigned long ulSessionID,char * data,int len)=0;
};

class IFileDTS
{
public:
	IFileDTS(void)
	{
		memset(m_szModulePathFile, 0, MAX_PATH);
	};
	virtual~IFileDTS(void){};
public:
	virtual void addChannel(unsigned long channelId)=0;
	virtual void removeChannel(unsigned long channelId)=0;
	//virtual void SetSendFilePath(std::string sFilePath)=0;
	virtual void /*processFDTData*/processFileData(unsigned long channelId,const char * data,int len)=0;
	virtual void releaseConnection()=0;

	char m_szModulePathFile[MAX_PATH];
};

IFileDTS*CreateIFileDTS(IFileDTSNotify&rIFileDTSNotify,bool bMcu);

typedef struct {	
	std::string   strFileName;	
	unsigned long ulFileLen;
}FileInfo;

#endif