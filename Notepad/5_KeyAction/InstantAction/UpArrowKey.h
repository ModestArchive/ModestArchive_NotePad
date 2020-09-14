//UpArrowKey.h

#ifndef _UPARROWKEY_H
#define _UPARROWKEY_H
#include"KeyAction.h"

class UpArrowKey :public KeyAction {
public:
	UpArrowKey();
	UpArrowKey(NotePadForm* notePadForm);
	virtual ~UpArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _UPARROWKEY_H