//ShiftCtrlRightArrowKey.h

#ifndef _SHIFTCTRLRIGHTARROWKEY_H
#define _SHIFTCTRLRIGHTARROWKEY_H
#include "KeyAction.h"

class ShiftCtrlRightArrowKey :public KeyAction {
public:

	ShiftCtrlRightArrowKey();
	ShiftCtrlRightArrowKey(NotePadForm* notePadForm);
	virtual ~ShiftCtrlRightArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _SHIFTCTRLRIGHTARROWKEY_H


