//MouseWheelAction.h

#ifndef _MOUSEWHEELACTION_H
#define _MOUSEWHEELACTION_H

#include"NotePadForm.h"


class MouseWheelAction {
public:
	
	MouseWheelAction(NotePadForm* notePadForm=0);
	virtual ~MouseWheelAction() = 0;
	virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) = 0;

protected:
	NotePadForm* notePadForm;

};
#endif // _MOUSEWHEELACTION_H

