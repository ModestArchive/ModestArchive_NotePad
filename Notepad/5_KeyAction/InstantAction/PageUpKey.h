//PageUpKey.h

#ifndef _PAGEUPKEY_H
#define _PAGEUPKEY_H
#include "KeyAction.h"

class PageUpKey :public KeyAction {
public:

	PageUpKey();
	PageUpKey(NotePadForm* notePadForm);
	virtual ~PageUpKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // _PAGEUPKEY_H

