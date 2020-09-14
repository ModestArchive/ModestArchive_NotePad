//CtrlH.h

#ifndef _CTRLH_H
#define _CTRLH_H
#include "KeyAction.h"

class CtrlH :public KeyAction {

public:
	CtrlH(NotePadForm* notePadForm);
	virtual ~CtrlH();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLH_H


