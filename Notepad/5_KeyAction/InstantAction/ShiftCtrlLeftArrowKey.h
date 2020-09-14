//ShiftCtrlLeftArrowKey.h

#ifndef _SHIFTCTRLLEFTARROWKEY_H
#define _SHIFTCTRLLEFTARROWKEY_H
#include "KeyAction.h"

class ShiftCtrlLeftArrowKey :public KeyAction {
public:

	ShiftCtrlLeftArrowKey();
	ShiftCtrlLeftArrowKey(NotePadForm* notePadForm);
	virtual ~ShiftCtrlLeftArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _SHIFTCTRLLEFTARROWKEY_H


