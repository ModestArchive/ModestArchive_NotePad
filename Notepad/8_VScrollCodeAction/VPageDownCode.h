//VPageDownCode.h
#ifndef _VPAGEDOWNCODE_H
#define _VPAGEDOWNCODE_H

#include"VScrollCodeAction.h"
class ScrollController;
class NotePadForm;

class VPageDownCode :public VScrollCodeAction {
public:
	VPageDownCode(NotePadForm* notePadForm);
	virtual ~VPageDownCode();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_VPAGEDOWNCODE_H


