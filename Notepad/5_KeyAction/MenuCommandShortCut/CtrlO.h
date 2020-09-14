//CtrlO.h

#ifndef _CTRLO_H
#define _CTRLO_H
#include "KeyAction.h"

class CtrlO :public KeyAction {

public:
	CtrlO(NotePadForm* notePadForm);
	virtual ~CtrlO();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_CTRLO_H
