//MouseLeave.h

#ifndef _MOUSELEAVE_H
#define _MOUSELEAVE_H

#include "NotePadForm.h"

class MouseLeave {
public:
	MouseLeave(NotePadForm* notePadForm = 0);
	~MouseLeave();
	void OnMouseLeave();
private:
	NotePadForm* notePadForm;
};
#endif // !_MOUSELEAVE_H
