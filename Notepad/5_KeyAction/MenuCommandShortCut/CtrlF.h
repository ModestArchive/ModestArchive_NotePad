//CtrlF.h

#ifndef _CTRLF_H
#define _CTRLF_H
#include "KeyAction.h"

class CtrlF :public KeyAction {

public:
	CtrlF(NotePadForm* notePadForm);
	virtual ~CtrlF();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLF_H


