// ClientFactory.h: interface for the CClientFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTFACTORY_H__D7E99374_882F_4834_91B6_D439B136FBE8__INCLUDED_)
#define AFX_CLIENTFACTORY_H__D7E99374_882F_4834_91B6_D439B136FBE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <ace/Singleton.h>
//#include <ace/Containers.h>

#include "IRSClient.h"
#include "IRSClientNotify.h"

class CClientFactory  
{
// Operations
public:
	/*
	 *	FUCTION NAME: CreateClient
	 *	DESCRIPTION:
	 *		Create a Client Instance in terms of Client Id
	 *	PARAMETERS:
	 *		@nClientId : Client Id
	 *	RETURN:
	 *		the Client created
	 */
	IRSClient* CreateClient(int nClientID,IRSClientNotify &rNotify);
public:
	CClientFactory();
	virtual ~CClientFactory();

};

//typedef ACE_Singleton<CClientFactory, ACE_Null_Mutex> CLIENTFACTORY;


#endif // !defined(AFX_CLIENTFACTORY_H__D7E99374_882F_4834_91B6_D439B136FBE8__INCLUDED_)
 
