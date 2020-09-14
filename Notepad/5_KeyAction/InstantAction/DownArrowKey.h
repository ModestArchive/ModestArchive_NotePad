//DownArrowKey.h

#ifndef _DOWNARROWKEY_H
#define _DOWNARROWKEY_H
#include"KeyAction.h"

class DownArrowKey :public KeyAction {
public:
	DownArrowKey();
	DownArrowKey(NotePadForm* notePadForm);
	virtual ~DownArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

};
#endif // !_DOWNARROWKEY_H
