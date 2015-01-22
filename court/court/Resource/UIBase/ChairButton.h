#pragma once
#include "BmpBkButton.h"

// CChairButton

class CChairButton : public CBmpBkButton
{
	DECLARE_DYNAMIC(CChairButton)

public:
	void SetChairIndex(int nIndex = -1);
	int GetChairIndex();

	CChairButton();
	virtual ~CChairButton();

protected:
	DECLARE_MESSAGE_MAP()

	int m_nIndex;
};


