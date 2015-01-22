#ifndef __WBDTS_H__
#define __WBDTS_H__

#define FILE_TRANS_MAXLENGTH 8*1024
//{{xmc
#ifndef MAX_PATH
#define MAX_PATH	4096
#endif
//}}

#include "IWBDTS.h"


#include <list>
#include <map>

#include "WbCommandType.h"
#include "../libHPBaseclass/AVAutoLock.h"

typedef struct tag_OBJDATABUF
{
	char*			pData;
	int				nLen;
}OBJDATABUF, *LPOBJDATABUF;

typedef std::map<unsigned long,unsigned long> MapULong2ULong;
typedef std::map<unsigned long,OBJDATABUF> MapObjects;

class WbDTS 
	: public IWbDTS
{
public:
	WbDTS(IWbDTSNotify&rIWbDTSNotify);
	virtual ~WbDTS(void);
public:
	void processWbData(unsigned long channelId,char * data,int len);
	void addChannel(unsigned long channelId);
	void removeChannel(unsigned long channelId);
protected:
	void processAddObj(unsigned long channelId,PWB_COMMAND_HEAD pWbHead);
	void ClearAllObject(void);
	void DeleteAllShareDocObj();
	void processDeleteAll(unsigned long channelId,char* data,int len);
	void processDeleteObj(unsigned long channelId,char* data,int len);
	void processObjRequest(unsigned long channelId,PWB_COMMAND_HEAD pWbHead);
	void processObjResponse(unsigned long channelId,char* data,int len);
	void deliverGroupWbData(unsigned long channelId,char * data,int len);

	void processPageChanged(unsigned long channelId,char* data,int len);
	void processDocPageChanged(unsigned long channelId,char* data,int len);

	void processDocClose(unsigned long channelId,char* data,int len);
	void processScroll(unsigned long channelId,char* data,int len);
	void processMoveObj(unsigned long channelId,char* data,int len);
	void processTransLastPosition(unsigned long channelId,char* data,int len);
	void processTabCtrlChange(unsigned long channelId,char* data,int len);
	void processFullScreen(unsigned long channelId,char* data,int len);
	void processToolBarMove(unsigned long channelId,char* data,int len);

	void processTransAllObj(unsigned long channelId,char*pData,int nLen);
	void processTransLastPositionRequest(unsigned long channelId,char* data,int len);//add by wzf 2006.05.15
	void processTransLastPositionResponse(unsigned long channelId,char* data,int len);//add by wzf 2006.05.15
		
	bool FindObj(unsigned long ulObjID);
	void processTransLoadFile(unsigned long channelId,char*pData,int nLen);
	void SaveDataToZplFile(char* data,int len, unsigned long	dwOffset);//add by wzf 2006.05.17
	void processTransShareFileRequest(unsigned long channelId,char*pData,int nLen);//add by wzf 2006.05.17
	void processTransShareFileResponse(unsigned long channelId,char*pData,int nLen);//add by wzf 2006.05.17
	
	void processTransDTObjLength(unsigned long channelId,char* data,int len);//add by wzf on 2006.05.25
	void processTransDTObjResponse(unsigned long channelId,char* data,int len);//add by wzf on 2006.05.26
	void processTransDTObjRequest(unsigned long channelId,char* data,int len);//add by wzf on 2006.05.26

protected:
	MapObjects		m_MapObjects;
	MapULong2ULong	m_MapChsId;
	AVCritSec		m_csMapChsId;
	AVCritSec		m_csMapObjects;
	IWbDTSNotify&	m_rIWbDTSNotify;
	CLIENT_WINDOW_POSITION m_cwPos;
	unsigned long			m_dwVirtualDocObjId;
	unsigned long			m_dwShareFileLength;
	char m_csZsplFileName[MAX_PATH]; 
};


#endif