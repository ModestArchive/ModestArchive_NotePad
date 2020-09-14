//HLeftCode.h
#ifndef _HLEFTCODE_H
#define _HLEFTCODE_H
#include"HScrollCodeAction.h"

class NotePadForm;

class HLeftCode :public HScrollCodeAction {
public:
	HLeftCode(NotePadForm* notePadForm);
	virtual ~HLeftCode();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_HLEFTCODE_H

