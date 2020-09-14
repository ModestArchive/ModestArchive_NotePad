//ShiftLeftArrowKey.h

#ifndef _SHIFTLEFTARROWKEY_H
#define _SHIFTLEFTARROWKEY_H
#include "KeyAction.h"

class ShiftLeftArrowKey :public KeyAction {

public:
	ShiftLeftArrowKey();
	ShiftLeftArrowKey(NotePadForm* notePadForm);
	virtual ~ShiftLeftArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _SHIFTLEFTARROWKEY_H
