//CtrlXKey.h

#ifndef _CTRLXKEY_H
#define _CTRLXKEY_H
#include "KeyAction.h"

class CtrlXKey :public KeyAction {
public:
	CtrlXKey();
	CtrlXKey(NotePadForm* notePadForm);
	virtual ~CtrlXKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLVKEY_H


