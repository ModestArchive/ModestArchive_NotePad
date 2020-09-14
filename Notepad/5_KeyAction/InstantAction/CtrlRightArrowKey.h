//CtrlRightArrowKey.h

#ifndef _CTRLRIGHTARROWKEY_H
#define _CTRLRIGHTARROWKEY_H
#include"KeyAction.h"

class CtrlRightArrowKey : public KeyAction {
public:
	CtrlRightArrowKey();
	CtrlRightArrowKey(NotePadForm* notePadForm);
	virtual ~CtrlRightArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

};

#endif // _CTRLLEFTARROWKEY_H


