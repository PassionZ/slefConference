#include "StdAfx.h"
#include "LabelSet.h"
#include <algorithm>
#include <cassert>

using namespace std;

LabelSet::LabelSet( LPCSTR* _pTable,int _n )
{
	n = _n;
	pTable = new LPCSTR[n];
	copy(_pTable,_pTable + _n,pTable);
}

LPCSTR LabelSet::getLabel( int _id ) const
{
	return pTable[_id];
}

LabelSet::~LabelSet()
{
	delete [] pTable;
}

LabelSetEx::LabelSetEx( int _n )
{
	n = _n;
	pGroup = new Switch[n];
	memset(pGroup,0,n * sizeof(pGroup[0]));
}

LabelSetEx::~LabelSetEx()
{
	while(n--)
	{
		if(pGroup[n].s[0] == pGroup[n].s[1])
			delete pGroup[n].s[0];
		else
		{
			delete pGroup[n].s[0];
			delete pGroup[n].s[1];
		}
	}
	delete [] pGroup;
}

bool LabelSetEx::addSets( int id,LPCSTR* s1,LPCSTR* s2,int n,int at /*= 0*/ )
{
	assert((at & ~1) == 0);
	if(pGroup[id].s[0] != NULL)
		return false;
	LabelSet* p = new LabelSet(s1,n);
	pGroup[id].s[0] = p;
	if(s1 == s2)
		pGroup[id].s[1] = p;
	else
		pGroup[id].s[1] = new LabelSet(s2,n);
	pGroup[id].at = at;
	return true;
}

LPCSTR LabelSetEx::getLable( int id,int off ) const
{
	Switch* p = pGroup + id;
	return p->s[p->at]->getLabel(off);
}

void LabelSetEx::turn( int id )
{
    assert((pGroup->at & ~1) == 0);
    pGroup[id].at ^= 1;
}