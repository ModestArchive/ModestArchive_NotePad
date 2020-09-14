//LeftArrowKey.h

#ifndef _LEFTARROWKEY_H
#define _LEFTARROWKEY_H
#include "KeyAction.h"

class LeftArrowKey :public KeyAction {
public:

	LeftArrowKey();
	LeftArrowKey(NotePadForm* notePadForm);
	virtual ~LeftArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

};
#endif // _RIGHTARROWKEY_H

