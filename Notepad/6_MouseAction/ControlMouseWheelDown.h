//ControlMouseWheelDown.h

#ifndef _CONTROLMOUSEWHEELDOWN_H
#define _CONTROLMOUSEWHEELDOWN_H

#include"MouseWheelAction.h"
class NotePadForm;

class ControlMouseWheelDown : public MouseWheelAction {
public:

	ControlMouseWheelDown(NotePadForm* notePadForm = 0);
	virtual ~ControlMouseWheelDown();
	virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

};
#endif // !_CONTROLMOUSEWHEELDOWN_H



