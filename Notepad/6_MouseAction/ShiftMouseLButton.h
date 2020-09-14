//ShiftMouseLButton.h

#ifndef _SHIFTMOUSELBUTTON_H
#define _SHIFTMOUSELBUTTON_H

#include "NotePadForm.h"
#include"MouseLButtonAction.h"

class ShiftMouseLButton : public MouseLButtonAction {
public:
	ShiftMouseLButton(NotePadForm* notePadForm);
	virtual ~ShiftMouseLButton();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
};
#endif // !_SHIFTMOUSELBUTTON_H