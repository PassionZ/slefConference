#pragma once

#include "config.h"
#include "LabelSet.h"
#include <memory>

class Key
{
public:
    virtual bool hitTest(const CPoint& pt) const = 0;

    virtual BYTE         getState() const = 0;
    virtual BYTE         getVkey() const = 0;
    virtual LPCSTR       getLabel() const = 0;
    virtual const CRect& getRect() const = 0;
    virtual const LabelSetEx&  getLabelSet() const = 0;

    virtual void press() = 0;
    virtual void release() = 0;

    virtual void draw(CDC* pDc) const;
    virtual ~Key(void) {}

public:
    static COLORREF clrBord[2];
    static COLORREF clrFill[2];
    static COLORREF clrText[2];
};

class SimpleKey : public Key
{
public:
    SimpleKey(LabelSetEx* _pls,const KeyConfig& _kc,int _unit,BYTE _stat);

    bool hitTest(const CPoint& pt) const;

    BYTE         getState() const;
    BYTE         getVkey() const;
    LPCSTR       getLabel() const;
    const CRect& getRect() const;
    const LabelSetEx&  getLabelSet() const;

    void press();
    void release();

    ~SimpleKey();

protected:
    SimpleKey();

protected:
    LabelSetEx* pls;
    short id;
    short offset;
    CRect rt;
    BYTE vk;
    BYTE state;
};

class KeyDecorator : public Key
{
public:
    KeyDecorator(Key* _pkey);

    bool hitTest(const CPoint& pt) const;

    BYTE         getState() const;
    BYTE         getVkey() const;
    LPCSTR       getLabel() const;
    const CRect& getRect() const;
    const LabelSetEx&  getLabelSet() const;

    virtual void press();
    virtual void release();

protected:
    std::auto_ptr<Key> pkey;
};

class ShiftKey : public KeyDecorator
{
public:
    ShiftKey(Key* _pkey,short _id1,short _id2);

    void press();
    void release();

private:
    short id1;
    short id2;
};

class LockKey : public KeyDecorator
{
public:
    LockKey(Key* _pkey,short _id);

    void press();
    void release();

private:
    short id;
};