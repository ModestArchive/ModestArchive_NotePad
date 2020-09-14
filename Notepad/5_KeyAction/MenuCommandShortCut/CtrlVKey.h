//CtrlVKey.h

#ifndef _CTRLVKEY_H
#define _CTRLVKEY_H
#include "KeyAction.h"

class CtrlVKey :public KeyAction {
public:
	CtrlVKey();
	CtrlVKey(NotePadForm* notePadForm);
	virtual ~CtrlVKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLVKEY_H

