//CtrlHomeKey.h

#ifndef _CTRLHOMEKEY_H
#define _CTRLHOMEKEY_H

#include "KeyAction.h"

class CtrlHomeKey :public KeyAction {
public:
	CtrlHomeKey();
	CtrlHomeKey(NotePadForm* notePadForm);
	virtual ~CtrlHomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


#endif // !_CTRLHOMEKEY_H
