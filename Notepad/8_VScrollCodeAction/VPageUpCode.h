//VPageUpCode.h
#ifndef _VPAGEUPCODE_H
#define _VPAGEUPCODE_H

#include"VScrollCodeAction.h"
class ScrollController;
class NotePadForm;

class VPageUpCode :public VScrollCodeAction {
public:
	VPageUpCode(NotePadForm* notePadForm);
	virtual ~VPageUpCode();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_VPAGEUPCODE_H



