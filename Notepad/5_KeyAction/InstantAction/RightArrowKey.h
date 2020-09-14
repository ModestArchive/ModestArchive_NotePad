//RightArrowKey.h

#ifndef _RIGHTARROWKEY_H
#define _RIGHTARROWKEY_H
#include "KeyAction.h"

class RightArrowKey :public KeyAction {
public:

	RightArrowKey();
	RightArrowKey(NotePadForm* notePadForm);
	virtual ~RightArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

};
#endif // _RIGHTARROWKEY_H
