//VTopCode.h
#ifndef _VTOPCODE_H
#define _VTOPCODE_H

#include"VScrollCodeAction.h"
class ScrollController;
class NotePadForm;

class VTopCode :public VScrollCodeAction {
public:
	VTopCode(NotePadForm* notePadForm);
	virtual ~VTopCode();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_VTOPCODE_H

