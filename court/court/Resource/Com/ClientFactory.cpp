// ClientFactory.cpp: implementation of the CClientFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClientFactory.h"
//#include "../DataDefine/TheClientDefine.h"
#include "IRSTCPLogicClient.h"
//#include "../../AVCRecordPlayer/RSRecordPlayClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientFactory::CClientFactory()
{

}

CClientFactory::~CClientFactory()
{
}

IRSClient* CClientFactory::CreateClient(int nClientID,IRSClientNotify &rNotify)
{
	switch(nClientID) {
	default:
		return new IRSTCPLogicClient(rNotify);
		break;
	}

	return NULL;
}
