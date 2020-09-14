//VEndScrollCode.h
#ifndef _VENDSCROLLCODE_H
#define _VENDSCROLLCODE_H

#include"VScrollCodeAction.h"
class ScrollController;
class NotePadForm;

class VEndScrollCode :public VScrollCodeAction {
public:
	VEndScrollCode(NotePadForm* notePadForm);
	virtual ~VEndScrollCode();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_VENDSCROLLCODE_H



