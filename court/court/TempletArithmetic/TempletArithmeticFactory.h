// TempletArithmeticFactory.h: interface for the CTempletArithmeticFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEMPLETARITHMETICFACTORY_H__6D3AEE74_DDD6_4FD1_9A0A_02CBB4DEC7E4__INCLUDED_)
#define AFX_TEMPLETARITHMETICFACTORY_H__6D3AEE74_DDD6_4FD1_9A0A_02CBB4DEC7E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <ace/Singleton.h>
//#include <ace/Containers.h>

#include "TempletArithmetic.h"
//#include "../../Resource/DataDefine/TempletArithmeticDefine.h"
const int TEMPLETFREE_LOGIC	= 0x0001;
const int TEMPLETNORMAL_LOGIC = 0x0002;
const int ID16x9TEMPLETNORMALID_LOGIC	= 0x0003;
class CTempletArithmeticFactory  
{
// Operations
public:
	/*
	 *	FUCTION NAME: CreateTempletArithmetic
	 *	DESCRIPTION:
	 *		Create a TempletArithmetic Instance in terms of TempletArithmetic Id
	 *	PARAMETERS:
	 *		@nTempletArithmeticId : TempletArithmetic Id
	 *	RETURN:
	 *		the TempletArithmetic created
	 */
	CTempletArithmetic* CreateTempletArithmetic(int nTempletArithmeticID);
public:
	CTempletArithmeticFactory();
	virtual ~CTempletArithmeticFactory();

};

//typedef ACE_Singleton<CTempletArithmeticFactory, ACE_Null_Mutex> TEMPLETARITHMETICFACTORY;

#endif // !defined(AFX_TEMPLETARITHMETICFACTORY_H__6D3AEE74_DDD6_4FD1_9A0A_02CBB4DEC7E4__INCLUDED_)
