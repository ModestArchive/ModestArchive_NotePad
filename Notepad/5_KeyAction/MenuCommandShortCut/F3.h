//F3.h

#ifndef _F3_H
#define _F3_H
#include "KeyAction.h"

class F3 :public KeyAction {
public:
	F3(NotePadForm* notePadForm);
	virtual ~F3();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
#endif // !_F3_H