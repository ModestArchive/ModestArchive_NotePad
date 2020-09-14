//CtrlLeftArrowKey.h

#ifndef _CTRLLEFTARROWKEY_H
#define _CTRLLEFTARROWKEY_H
#include"KeyAction.h"

class CtrlLeftArrowKey : public KeyAction {
public:
	CtrlLeftArrowKey();
	CtrlLeftArrowKey(NotePadForm* notePadForm);
	virtual ~CtrlLeftArrowKey();
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	
private:

	

};





#endif // _CTRLLEFTARROWKEY_H

