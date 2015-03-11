// ResourceDefine.cpp: implementation of the CResourceDefine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResourceDefine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//查找视频卡设置信息
TVideoCardInfo *GetVideoCardSetting(CTVideoCardInfoArray &array, int nCardNo)
{
    int i=0;for ( i=0; i<array.GetCount(); i++)
    {
        if (array.GetAt(i)->_iUserCardNo == nCardNo)
        {
            return array.GetAt(i);
        }
    }

    return NULL;
}
