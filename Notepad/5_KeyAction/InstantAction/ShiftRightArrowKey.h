//ShiftRightArrowKey.h

#ifndef _SHIFTRIGHTARROWKEY_H
#define _SHIFTRIGHTARROWKEY_H
#include "KeyAction.h"

class ShiftRightArrowKey :public KeyAction {

public:
	ShiftRightArrowKey();
	ShiftRightArrowKey(NotePadForm* notePadForm);
	virtual ~ShiftRightArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _SHIFTRIGHTARROWKEY_H
