//MouseLButton.h

#ifndef _MOUSELBUTTON_H
#define _MOUSELBUTTON_H

#include "NotePadForm.h"

class MouseLButton  {
public:
	MouseLButton(NotePadForm* notePadForm = 0);
	~MouseLButton();
	void OnLButtonDown(UINT nFlags, CPoint point) ;
private:
	NotePadForm* notePadForm;
};
#endif // !_MOUSELBUTTON_H

