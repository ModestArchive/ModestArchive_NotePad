//MouseWheelDown.h

#ifndef _MOUSEWHEELDOWN_H
#define _MOUSEWHEELDOWN_H

#include"MouseWheelAction.h"
class NotePadForm;

class MouseWheelDown : public MouseWheelAction{
public:

	MouseWheelDown(NotePadForm* notePadForm = 0);
	virtual ~MouseWheelDown() ;
	virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

};
#endif // _MOUSEWHEELDOWN_H


