//EndKey.h

#ifndef _ENDKEY_H
#define _ENDKEY_H

#include"KeyAction.h"


class EndKey :public KeyAction {

public:
	EndKey();
	EndKey(NotePadForm* notePadForm);
	virtual ~EndKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // !_ENDKEY_H