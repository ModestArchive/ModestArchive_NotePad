//KeyAction.h

#ifndef _KEYACTION_H
#define _KEYACTION_H

#include"NotePadForm.h"


class KeyAction {
public:
	KeyAction();
	KeyAction(NotePadForm *notePadForm);
	virtual ~KeyAction()=0;
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)=0;

protected:
	NotePadForm* notePadForm;
	
};
#endif // _KEYACTION_H
