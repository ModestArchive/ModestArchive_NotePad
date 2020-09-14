//CtrlN.h

#ifndef _CTRLN_H
#define _CTRLN_H
#include "KeyAction.h"

class CtrlN :public KeyAction {

public:
	CtrlN(NotePadForm* notePadForm);
	virtual ~CtrlN();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLN_H

