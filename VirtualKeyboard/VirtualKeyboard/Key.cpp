#include "StdAfx.h"
#include "Key.h"
#include <cassert>

using namespace std;

// COLORREF Key::clrBord[] = {
//     RGB(255,255,255),
//     RGB(255,  0,  0)
// };
// COLORREF Key::clrFill[] = {
//     RGB(  0,  0,  0),
//     RGB(236,233,216)
// };
// COLORREF Key::clrText[] = {
//     RGB(255,255,255),
//     RGB(  0,  0,  0)
// };

COLORREF Key::clrBord[] = {
    RGB(  0,  0,  0),
    RGB(255,  0,  0)
};
COLORREF Key::clrFill[] = {
    RGB(236,233,216),
    RGB(  0,  0,255)
};
COLORREF Key::clrText[] = {
    RGB(  0,  0,  0),
    RGB(255,255,255)
};

void Key::draw( CDC* pDc ) const
{
    int i = getState() >> 7;
    CBrush br;
    CPen pen;
    br.CreateSolidBrush(clrFill[i]);
    pen.CreatePen(PS_SOLID,2,clrBord[i]);

    pDc->SaveDC();
    pDc->SelectObject(&br);
    pDc->SelectObject(&pen);
    pDc->SetTextColor(clrText[i]);

    CString txt = getLabel();
    CRect rt = getRect();
    CSize sz = pDc->GetTextExtent(txt);

    pDc->BitBlt(rt.left,rt.top,rt.Width(),rt.Height(),pDc,rt.left,rt.top,SRCINVERT);
    pDc->Rectangle(rt);
    pDc->SetBkMode(TRANSPARENT);
    pDc->TextOut( (rt.right + rt.left - sz.cx) / 2,
        (rt.top + rt.bottom - sz.cy) / 2,
        txt );

    pDc->RestoreDC(-1);
}

SimpleKey::SimpleKey( LabelSetEx* _pls,const KeyConfig& _kc,int _unit,BYTE _state )
{
    assert(_pls != NULL);
    pls    = _pls;
    id     = _kc.id;
    offset = _kc.offset;
    vk     = _kc.vk;
    state   = _state;

    rt.left   = _kc.rt.left * _unit;
    rt.top    = _kc.rt.top * _unit;
    rt.right  = _kc.rt.right * _unit;
    rt.bottom = _kc.rt.bottom * _unit;
}

SimpleKey::SimpleKey()
{
    pls = NULL;
}

bool SimpleKey::hitTest( const CPoint& pt ) const
{
    return rt.PtInRect(pt) == TRUE;
}

BYTE SimpleKey::getState() const
{
    return state;
}

BYTE SimpleKey::getVkey() const
{
    return vk;
}

LPCSTR SimpleKey::getLabel() const
{
    return pls->getLable(id,offset);
}

const CRect& SimpleKey::getRect() const
{
    return rt;
}

void SimpleKey::press()
{
    keybd_event(vk,0,0,0);
    state ^= 0x81;
}

void SimpleKey::release()
{
    keybd_event(vk,0,KEYEVENTF_KEYUP,0);
    state ^= 0x80;
}

SimpleKey::~SimpleKey()
{

}

const LabelSetEx& SimpleKey::getLabelSet() const
{
    return *pls;
}

KeyDecorator::KeyDecorator( Key* _pkey )
: pkey(_pkey)
{

}

bool KeyDecorator::hitTest( const CPoint& pt ) const
{
    return pkey->hitTest(pt);
}

BYTE KeyDecorator::getState() const
{
    return pkey->getState();
}

BYTE KeyDecorator::getVkey() const
{
    return pkey->getVkey();
}

LPCSTR KeyDecorator::getLabel() const
{
    return pkey->getLabel();
}

const CRect& KeyDecorator::getRect() const
{
    return pkey->getRect();
}

void KeyDecorator::press()
{
    return pkey->press();
}

void KeyDecorator::release()
{
    return pkey->release();
}

const LabelSetEx& KeyDecorator::getLabelSet() const
{
    return pkey->getLabelSet();
}

ShiftKey::ShiftKey( Key* _pkey,short _id1,short _id2 )
: KeyDecorator(_pkey)
{
    id1 = _id1;
    id2 = _id2;
}

void ShiftKey::press()
{
    KeyDecorator::press();
    LabelSetEx& ls = const_cast<LabelSetEx&>(getLabelSet());
    ls.turn(id1);
    ls.turn(id2);
}

void ShiftKey::release()
{
    KeyDecorator::release();
    LabelSetEx& ls = const_cast<LabelSetEx&>(getLabelSet());
    ls.turn(id1);
    ls.turn(id2);
}

LockKey::LockKey( Key* _pkey,short _id )
: KeyDecorator(_pkey)
{
    id = _id;
}

void LockKey::press()
{
    KeyDecorator::press();
    LabelSetEx& ls = const_cast<LabelSetEx&>(getLabelSet());
    ls.turn(id);
}

void LockKey::release()
{
    KeyDecorator::release();
}