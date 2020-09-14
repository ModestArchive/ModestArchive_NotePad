//CtrlYKey.h

#ifndef _CTRLYKEY_H
#define _CTRLYKEY_H
#include "KeyAction.h"

class CtrlYKey :public KeyAction {
public:
	CtrlYKey();
	CtrlYKey(NotePadForm* notePadForm);
	virtual ~CtrlYKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLYKEY_H

