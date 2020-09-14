//MouseMove.h

#ifndef _MOUSEMOVE_H
#define _MOUSEMOVE_H

#include "NotePadForm.h"

class MouseMove {
public:
	MouseMove(NotePadForm* notePadForm = 0);
	~MouseMove();
	void OnMouseMove(UINT nFlags, CPoint point);
private:
	NotePadForm* notePadForm;
};
#endif // !_MOUSEMOVE_H
