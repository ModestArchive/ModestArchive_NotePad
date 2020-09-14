//CtrlE.h

#ifndef _CTRLE_H
#define _CTRLE_H
#include "KeyAction.h"

class CtrlE :public KeyAction {

public:
	CtrlE(NotePadForm* notePadForm);
	virtual ~CtrlE();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLE_H

