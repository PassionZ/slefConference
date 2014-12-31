#include "StdAfx.h"
#include "Keyboard.h"
#include "config.h"
#include <algorithm>

using namespace std;

Keyboard::Keyboard( CWnd* _pWnd /* = NULL*/ )
: ls(5),pWnd(_pWnd)
{
    BYTE states[256];
    ::GetKeyboardState(states);
    initLabelSet(states);
    initKeys(states);
}

Keyboard::~Keyboard(void)
{
}

void Keyboard::initLabelSet( BYTE states[] )
{
	int tab = states[VK_CAPITAL] & 0x01;
	int shift = (states[VK_SHIFT] & 0x80) >> 7;
	int num = (states[VK_NUMLOCK] & 0x80) >> 7;

	ls.addSets(0,
		AlphaTable1,AlphaTable2,
		AlphaTableSize,
		tab ^ shift);
	ls.addSets(1,
		SymbolTable1,SymbolTable2,
		SymbolTableSize,
		shift);
	ls.addSets(2,
		NumPadTable1,NumPadTable2,
		NumPadTableSize,
		num);
	ls.addSets(3,
		MainTable,MainTable,
		MainTableSize);
	ls.addSets(4,
		HelpTable,HelpTable,
		HelpTableSize);
}

void Keyboard::initKeys( BYTE states[] )
{
    int unit = 4;
    keys.resize(kcSize,NULL);
    for(int i = 0;i < kcSize;i++)
    {
        BYTE vk = kcs[i].vk;
        keys[i] = new SimpleKey(&ls,kcs[i],unit,(states[vk]));
        switch(vk)
        {
        case VK_LSHIFT:
        case VK_RSHIFT:
            keys[i] = new ShiftKey(keys[i],LABEL_SET_ALPHA,LABEL_SET_SYMBOL);
            break;
        case VK_CAPITAL:
            keys[i] = new LockKey(keys[i],LABEL_SET_ALPHA);
            break;
        case VK_NUMLOCK:
            keys[i] = new LockKey(keys[i],LABEL_SET_NUMPAD);
            break;
        }
    }
    sz.SetSize(kbSize.cx * unit,kbSize.cy * unit);
}

void Keyboard::rebind( CWnd* _pWnd )
{
    pWnd = _pWnd;
}

void Keyboard::draw()
{
    CPaintDC dc(pWnd);
    for(int i = 0;i < keys.size();i++)
    {
        keys[i]->draw(&dc);
    }
}

int Keyboard::hit( const CPoint& pt )
{
    for(int i = 0;i < keys.size();i++)
    {
        if(keys[i]->hitTest(pt) )
        {
            return i;
        }
    }
    return -1;
}

void Keyboard::releaseAll(CDC* pDc)
{
    while(!keyStack.empty())
    {
        keyStack.top()->release();
        keyStack.top()->draw(pDc);
        keyStack.pop();
    }
}

const CSize& Keyboard::getSize() const
{
    return sz;
}

bool Keyboard::press( int index )
{
    pCur = keys[index];

    if(!pCur)
        return false;

    CClientDC dc(pWnd);
    BYTE vk = pCur->getVkey();
    if( vk == VK_LSHIFT   || vk == VK_RSHIFT
        || vk == VK_LCONTROL || vk == VK_RCONTROL
        || vk == VK_LMENU    || vk == VK_RMENU
        || vk == VK_LWIN     || vk == VK_RWIN )
    {
        if(pCur->getState() & 0x80)
        {
            releaseAll(&dc);
        }
        else
        {
            pCur->press();
            pCur->draw(&dc);
            keyStack.push(pCur);
        }
    }
    else
    {
        pCur->press();
        pCur->draw(&dc);
    }
    if( vk == VK_CAPITAL || vk == VK_NUMLOCK
     || vk == VK_LSHIFT   || vk == VK_RSHIFT )
    {
        pWnd->Invalidate(FALSE);
    }

    return true;
}

bool Keyboard::release( int index )
{
    if(pCur != keys[index])
        return false;

    BYTE vk = pCur->getVkey();
    if( vk == VK_LSHIFT   || vk == VK_RSHIFT
        || vk == VK_LCONTROL || vk == VK_RCONTROL
        || vk == VK_LMENU    || vk == VK_RMENU
        || vk == VK_LWIN     || vk == VK_RWIN )
    {
//         if(pCur->active())
//         {
//             pCur->release();
//             releaseAll();
//         }
//         else
//         {
//             pCur->press();
//             keyStack.push(p);
//         }
    }
    else
    {
        CClientDC dc(pWnd);
        pCur->release();
        pCur->draw(&dc);
        releaseAll(&dc);
        pWnd->Invalidate(FALSE);
        //ÖØ»æ
    }
    return true;
}