//MouseLButtonOneClick.h

#ifndef _MOUSELBUTTONONECLICK_H
#define _MOUSELBUTTONONECLICK_H

#include "NotePadForm.h"
#include"MouseLButtonAction.h"

class MouseLButtonOneClick :public MouseLButtonAction{
public:
	MouseLButtonOneClick(NotePadForm* notePadForm);
	virtual ~MouseLButtonOneClick();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);

};
#endif // !_MOUSELBUTTONONECLICK_H


