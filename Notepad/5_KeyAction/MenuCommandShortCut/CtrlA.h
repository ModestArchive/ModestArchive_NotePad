//CtrlA.h

#ifndef _CTRLA_H
#define _CTRLA_H
#include "KeyAction.h"

class CtrlA :public KeyAction {

public:
	CtrlA(NotePadForm* notePadForm);
	virtual ~CtrlA();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLA_H

