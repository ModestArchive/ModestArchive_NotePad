//ShiftCtrlHomeKey.h

#ifndef _SHIFTCTRLHOMEKEY_H
#define _SHIFTCTRLHOMEKEY_H
#include "KeyAction.h"

class ShiftCtrlHomeKey :public KeyAction {
public:

	ShiftCtrlHomeKey();
	ShiftCtrlHomeKey(NotePadForm* notePadForm);
	virtual ~ShiftCtrlHomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _SHIFTCTRLHOMEKEY_H


