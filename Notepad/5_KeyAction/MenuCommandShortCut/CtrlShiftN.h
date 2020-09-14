//CtrlShiftN.h

#ifndef _CTRLSHIFTN_H
#define _CTRLSHIFTN_H
#include "KeyAction.h"

class CtrlSHiftN :public KeyAction {
public:
	CtrlSHiftN(NotePadForm* notePadForm);
	virtual ~CtrlSHiftN();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLSHIFTN_H
