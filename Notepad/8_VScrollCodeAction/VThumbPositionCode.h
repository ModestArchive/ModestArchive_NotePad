//VThumbPositionCode.h
#ifndef _VTHUMBPOSITIONCODE_H
#define _VTHUMBPOSITIONCODE_H

#include"VScrollCodeAction.h"
class ScrollController;
class NotePadForm;

class VThumbPositionCode :public VScrollCodeAction {
public:
	VThumbPositionCode(NotePadForm* notePadForm);
	virtual ~VThumbPositionCode();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_VTHUMBPOSITIONCODE_H




