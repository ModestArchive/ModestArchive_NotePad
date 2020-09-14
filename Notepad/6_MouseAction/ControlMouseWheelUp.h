//ControlMouseWheelUp.h

#ifndef _CONTROLMOUSEWHEELUP_H
#define _CONTROLMOUSEWHEELUP_H

#include"MouseWheelAction.h"
class NotePadForm;

class ControlMouseWheelUp : public MouseWheelAction {
public:

	ControlMouseWheelUp(NotePadForm* notePadForm = 0);
	virtual ~ControlMouseWheelUp();
	virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

};
#endif // !_CONTROLMOUSEWHEELUP_H

