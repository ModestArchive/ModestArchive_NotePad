//HomeKey.h

#ifndef _HOMEKEY_H
#define _HOMEKEY_H

#include"KeyAction.h"


class HomeKey :public KeyAction {
public:
	HomeKey();
	HomeKey(NotePadForm* notePadForm);
	virtual ~HomeKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _HOMEKEY_H