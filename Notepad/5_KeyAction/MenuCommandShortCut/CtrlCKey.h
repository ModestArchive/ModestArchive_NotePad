//CtrlCKey.h

#ifndef _CTRLCKEY_H
#define _CTRLCKEY_H
#include "KeyAction.h"

class CtrlCKey :public KeyAction {
public:
	CtrlCKey();
	CtrlCKey(NotePadForm* notePadForm);
	virtual ~CtrlCKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLCKEY_H


