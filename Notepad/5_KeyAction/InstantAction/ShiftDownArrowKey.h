//ShiftDownArrowKey.h

#ifndef _SHIFTDOWNARROWKEY_H
#define _SHIFTDOWNARROWKEY_H
#include "KeyAction.h"

class ShiftDownArrowKey :public KeyAction {
public:

	ShiftDownArrowKey();
	ShiftDownArrowKey(NotePadForm* notePadForm);
	virtual ~ShiftDownArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _SHIFTDOWNARROWKEY_H


