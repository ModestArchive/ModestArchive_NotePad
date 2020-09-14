//CtrlS.h

#ifndef _CTRLS_H
#define _CTRLS_H
#include "KeyAction.h"

class CtrlS :public KeyAction {

public:
	CtrlS(NotePadForm* notePadForm);
	virtual ~CtrlS();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLS_H
