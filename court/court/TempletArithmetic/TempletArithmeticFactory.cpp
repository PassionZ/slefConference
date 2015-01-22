// TempletArithmeticFactory.cpp: implementation of the CTempletArithmeticFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TempletArithmeticFactory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "16x9TempletNormal.h"
#include "TempletFree.h"
#include "TempletNormal.h"
#include "TempletAALang.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTempletArithmeticFactory::CTempletArithmeticFactory()
{
}

CTempletArithmeticFactory::~CTempletArithmeticFactory()
{
}

CTempletArithmetic* CTempletArithmeticFactory::CreateTempletArithmetic(int nTempletArithmeticID)
{
	switch( nTempletArithmeticID )
	{
	case TEMPLETFREE_LOGIC:
		return new CTempletAALang();	//CTempletFree();
		break;
	case TEMPLETNORMAL_LOGIC:
		return new CTempletAALang();	//CTempletNormal();
		break;
	case ID16x9TEMPLETNORMALID_LOGIC:
		return new CTempletAALang();	//C16x9TempletNormal();
		break;
	default:
		break;
	}
	return NULL;
}
