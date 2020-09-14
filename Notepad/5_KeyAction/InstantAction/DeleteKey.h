//DeleteKey.h
#ifndef _DELETEKEY_H
#define _DELETEKEY_H
#include"KeyAction.h"
#include"NotePadForm.h"

class DeleteKey :public KeyAction {
public:
	DeleteKey(NotePadForm* notePadForm = 0);
	virtual ~DeleteKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_DELETEKEY_H

