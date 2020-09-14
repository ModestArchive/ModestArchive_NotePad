//MouseLButtonAction.h

#ifndef _MOUSELBUTTONACTION_H
#define _MOUSELBUTTONACTION_H

#include"NotePadForm.h"

class MouseLButtonAction {
public:

	MouseLButtonAction(NotePadForm* notePadForm);
	virtual ~MouseLButtonAction() = 0;
	virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;

protected:
	NotePadForm* notePadForm;
};
#endif // !_MOUSELBUTTONACTION_H

