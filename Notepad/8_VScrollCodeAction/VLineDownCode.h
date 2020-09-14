//VLineDownCode.h
#ifndef _VLINEDOWNCODE_H
#define _VLINEDOWNCODE_H

#include"VScrollCodeAction.h"
class ScrollController;
class NotePadForm;

class VLineDownCode :public VScrollCodeAction {
public:
	VLineDownCode(NotePadForm* notePadForm);
	virtual ~VLineDownCode();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_VLINEDOWNCODE_H


