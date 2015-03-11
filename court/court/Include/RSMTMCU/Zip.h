#ifndef ZIP_H_
#define ZIP_H_

#include "zlib.h"
#include <list>
#include "../libHPBaseclass/ListPtr.h"

void UnZipData(char* pZipData, unsigned long dwZipLen, char* pUnZipData, unsigned long dwUnZipLen);
unsigned long ZipData(char* pUnZipData, unsigned long dwUnZipLen, char** ppZipData);

class CZip  
{
public:
	CZip();
	virtual ~CZip();

public:	
	void Flash();
	bool Open(unsigned long dwLen);
	void Close();
	bool Write(unsigned char* pData,unsigned long dwLength);

	unsigned long	GetLength(){return m_dwBufferLength;};
	unsigned long	GetSize(){	return m_dwBufferSize;};
	unsigned char*	GetBuffer(){return m_pbBuffer;};

private:
	unsigned char*		m_pbBuffer;
	unsigned long		m_dwBufferSize;
	unsigned long		m_dwBufferLength;

	/*std::list<void*>*/ListPtr	m_list;
	z_stream			m_ZIPStream;
	unsigned long		m_crc32;
public:
	static void myfree(void* opaque, void* address);
	static void* myalloc(void* opaque, unsigned int items, unsigned int size);
};

class CUnZip  
{
public:
	CUnZip();
	~CUnZip();
public:
	void Close();
	int Read(void* buf, unsigned int len);
	bool Open(void* pData,int nLen,int nUnCompressed);
	unsigned long	GetPos(){return m_dwReadPos;};
private:
	unsigned char*		m_pbBuffer;
	unsigned long		m_dwBufferSize;
	unsigned long		m_dwReadPos;

	z_stream			m_ZIPStream;
	unsigned long		m_crc32;
	/*std::list<void*>*/ListPtr	m_list;
	unsigned int		m_nLengthOfUnCompressed;
	unsigned char*		m_pReadBuffer;
};

#endif
