//ShiftUpArrowKey.h

#ifndef _SHIFTUPARROWKEY_H
#define _SHIFTUPARROWKEY_H
#include "KeyAction.h"

class ShiftUpArrowKey :public KeyAction {

public:
	ShiftUpArrowKey();
	ShiftUpArrowKey(NotePadForm* notePadForm);
	virtual ~ShiftUpArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _SHIFTUPARROWKEY_H
