//ShiftHomeKey.h

#ifndef _SHIFTHOMEKEY_H
#define _SHIFTHOMEKEY_H
#include "KeyAction.h"

class ShiftHomeKey :public KeyAction {

public:
	ShiftHomeKey();
	ShiftHomeKey(NotePadForm* notePadForm);
	virtual ~ShiftHomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _SHIFTHOMEKEY_H
