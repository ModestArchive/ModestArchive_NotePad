//MouseWheelUp.h

#ifndef _MOUSEWHEELUP_H
#define _MOUSEWHEELUP_H

#include"MouseWheelAction.h"
class NotePadForm;

class MouseWheelUp : public MouseWheelAction {
public:

	MouseWheelUp(NotePadForm* notePadForm = 0);
	virtual ~MouseWheelUp();
	virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

};
#endif // _MOUSEWHEELUP_H


