//BackspaceKey.h

#ifndef _BACKSPACEKEY_H
#define _BACKSPACEKEY_H

#include"KeyAction.h"
#include"NotePadForm.h"

class BackspaceKey :public KeyAction {
public:
	BackspaceKey(NotePadForm* notePadForm=0);
	~BackspaceKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);


};
#endif // !_BACKSPACEKEY_H

