//F5.h

#ifndef _F5_H
#define _F5_H
#include "KeyAction.h"

class F5 :public KeyAction {
public:
	F5(NotePadForm* notePadForm);
	virtual ~F5();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_F5_H



