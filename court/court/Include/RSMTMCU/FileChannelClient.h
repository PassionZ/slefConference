#ifndef FileCHANNELCLIENT_H_
#define FileCHANNELCLIENT_H_

#include "FileChannel.h"
#include "../DataDefine/AVMTMCUClient.h"
#include "FileSessionClientTcp.h"

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
typedef std::map<unsigned long,/*std::string*/FileInfo*> MapUlong2Str;

class CFileChannelClient :
	public CFileChannel
	, public ILocalFile
{
public:
	CFileChannelClient(ILocalFileNotify&rNotify, unsigned long ulChannelID);
	virtual ~CFileChannelClient(void);

	virtual bool Connect(void);
	virtual void ReleaseConnections(void);
	virtual void onFileData(unsigned long ulSessionID,char* data,int len);
	virtual void onFileDataOut(const char*pData,int nLen);
	virtual bool IsDisconnected(void);

	void processFileData(const char * pData,long nLen);
	void SetSendFilePath(std::string sFilePath);

	void onFileEnd(const char* cFileName);
	void onFileProcess(double iProcess);

protected:
	ILocalFileNotify&	m_rNotify;
	CFileSessionClientTcp*	m_pFileSessionClientTcp;

	void processFDTRequest(unsigned long ulSessionID,char * data,int len);

private:
	AVCritSec	 m_csMapFileName;
	MapUlong2Str m_MapFileName;
};

#endif
