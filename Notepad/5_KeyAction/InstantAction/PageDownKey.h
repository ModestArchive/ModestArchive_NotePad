//PageDownKey.h

#ifndef _PAGEDOWNKEY_H
#define _PAGEDOWNKEY_H
#include "KeyAction.h"

class PageDownKey :public KeyAction {
public:

	PageDownKey();
	PageDownKey(NotePadForm* notePadForm);
	virtual ~PageDownKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

};
#endif // _PAGEDOWNKEY_H


