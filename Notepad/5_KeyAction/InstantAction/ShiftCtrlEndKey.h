//ShiftCtrlEndKey.h

#ifndef _SHIFTCTRLENDKEY_H
#define _SHIFTCTRLENDKEY_H
#include "KeyAction.h"

class ShiftCtrlEndKey :public KeyAction {
public:

	ShiftCtrlEndKey();
	ShiftCtrlEndKey(NotePadForm* notePadForm);
	virtual ~ShiftCtrlEndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _SHIFTCTRLENDKEY_H


