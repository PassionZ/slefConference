#ifndef __FILEDTS_H__
#define __FILEDTS_H__

#include "IFileDTS.h"
#include "CharArray.h"
//#include "AVCritSec.h"
#include "../libHPBaseclass/AVAutoLock.h"
#include <map>

#define FILE_TRANS_MAXLENGTH    8*1024
#define TRANS_DT_FILE			0 
#define TRANS_FDT_REQUEST		1 
#define TRANS_FDT_RESPONSE		2

typedef struct {	
	unsigned long ulFileId;	
	unsigned long ulFileLen;
	unsigned long ulOffset;	
	unsigned char byType;
}FDT_COMMAND_HEAD,*LPFDT_COMMAND_HEAD, *PFDT_COMMAND_HEAD;

typedef std::map<unsigned long,unsigned long> MapULong2ULong;
typedef std::map<unsigned long,/*std::string*/FileInfo*> MapUlong2Str;


class FileDTS 
	: public IFileDTS
{
public:
	FileDTS(IFileDTSNotify&rIFileDTSNotify,bool bMcu);
	virtual ~FileDTS(void);
public:
	void addChannel(unsigned long channelId);
	void removeChannel(unsigned long channelId);
	void /*processFDTData*/processFileData(unsigned long channelId,const char * data,int len);
	void releaseConnection();
	//void SetSendFilePath(std::string sFilePath);
public:
	void processDTFile(unsigned long channelId,char * data,int len);
	void processFDTRequest(unsigned long channelId,char * data,int len);
	void processDTResponse(unsigned long channelId,char * data,int len);
	void SaveDataToFile(unsigned long channelId,std::string sFileName,char* data, int len, unsigned long dwOffset, int iFileLen);//≤‚ ‘ π”√
	void deliverGroupFDTData(unsigned long channelId,char * data,int len);
	
protected:
	IFileDTSNotify&	m_rIFileDTSNotify;
	bool	m_bMcu;

private:
	MapULong2ULong m_MapChsId;
	AVCritSec		m_csMapChsId;
	AVCritSec		m_csMapObjects;
	MapUlong2Str	m_MapFileName;
};

#endif