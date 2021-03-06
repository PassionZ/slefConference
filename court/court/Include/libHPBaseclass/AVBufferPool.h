#ifndef __AVBUFFERPOOL_H__
#define __AVBUFFERPOOL_H__

#include "../libHPBaseclass/ListPtr.h"
#include "AVDataBuffer.h"
#include "../libHPBaseclass/AVAutoLock.h"

class AFX_EXT_CLASS AVBufferPool
{
public:
	AVBufferPool(void);
	virtual ~AVBufferPool(void);
public:
	virtual void SetDataBuffer(AVDataBuffer*pAVDataBuffer);
	virtual AVDataBuffer*GetDataBuffer(void);
	virtual int GetCount(void);
	virtual void Flush(void);
protected:
	AVCritSec			m_AVCritSec;
	ListPtr				m_listDataBuffer;
};

#endif
