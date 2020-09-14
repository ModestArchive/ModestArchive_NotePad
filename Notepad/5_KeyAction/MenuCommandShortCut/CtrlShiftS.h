//CtrlShiftS.h

#ifndef _CTRLSHIFTS_H
#define _CTRLSHIFTS_H
#include "KeyAction.h"

class CtrlShiftS :public KeyAction {
public:
	CtrlShiftS(NotePadForm* notePadForm);
	virtual ~CtrlShiftS();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLSHIFTS_H
