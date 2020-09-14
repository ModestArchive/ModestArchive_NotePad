//ShiftF3.h

#ifndef _SHIFTF3_H
#define _SHIFTF3_H
#include "KeyAction.h"

class ShiftF3 :public KeyAction {
public:
	
	ShiftF3(NotePadForm* notePadForm);
	virtual ~ShiftF3();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_SHIFTF3_H


