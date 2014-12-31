#pragma once

#include "LabelSet.h"
#include "Key.h"
#include <vector>
#include <stack>

class Keyboard
{
public:
	Keyboard(CWnd* _pWnd = NULL);
    void rebind(CWnd* _pWnd);
    const CSize& getSize() const;
    void draw();
    int hit(const CPoint& pt);
    bool press(int index);
    bool release(int index);

	~Keyboard(void);

protected:
	void initLabelSet(BYTE states[]);
    void initKeys(BYTE states[]);
    void releaseAll(CDC* pDc);

private:
    int unit;
	LabelSetEx ls;
    std::vector<Key*> keys;
    std::stack<Key*> keyStack;
    //Key* keys[256];
    CSize sz;
    CWnd* pWnd;
    Key* pCur;
};
