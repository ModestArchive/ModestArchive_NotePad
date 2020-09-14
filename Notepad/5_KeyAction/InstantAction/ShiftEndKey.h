//ShiftEndKey.h

#ifndef _SHIFTENDKEY_H
#define _SHIFTENDKEY_H
#include "KeyAction.h"

class ShiftEndKey :public KeyAction {

public:
	ShiftEndKey();
	ShiftEndKey(NotePadForm* notePadForm);
	virtual ~ShiftEndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _SHIFTENDKEY_H
