//CtrlZKey.h

#ifndef _CTRLZKEY_H
#define _CTRLZKEY_H
#include "KeyAction.h"

class CtrlZKey :public KeyAction {
public:
	CtrlZKey();
	CtrlZKey(NotePadForm* notePadForm);
	virtual ~CtrlZKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLZKEY_H

