//CtrlP.h

#ifndef _CTRLP_H
#define _CTRLP_H
#include "KeyAction.h"

class CtrlP :public KeyAction {

public:
	CtrlP(NotePadForm* notePadForm);
	virtual ~CtrlP();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLP_H
