//CtrlEndKey.h

#ifndef _CTRLENDKEY_H
#define _CTRLENDKEY_H
#include "KeyAction.h"

class CtrlEndKey :public KeyAction {
public:
	CtrlEndKey();
	CtrlEndKey(NotePadForm* notePadForm);
	virtual ~CtrlEndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLENDKEY_H
