#if !defined (__FILEIO_H__)
#define __FILEIO_H__


class CFileIO  
{
public:
	CFileIO();
	virtual ~CFileIO();

public:
	bool Open(const char* strFileName, const char* strFlag);
	void Close();
	int	Write(char* pData, int nLen);
	int Read(char* pData, int nReadLen);
	int Seek(unsigned long ulPos, int nOrigin);
	unsigned long GetCurPos();
	unsigned long GetFileLength(void);
	int SeekRead(char* pData, int nReadLen, unsigned long ulPos, int nOrigin);
private:
	FILE*				m_fp;
	unsigned long 		m_ulFileLength;
};

//void DirTest(UINT32 iConferenceID);

#endif 
