//HRightCode.h
#ifndef _HRIGHTCODE_H
#define _HRIGHTCODE_H

#include "HScrollCodeAction.h"

class NotePadForm;

class HRightCode :public HScrollCodeAction {
public:
	HRightCode(NotePadForm* notePadForm);
	virtual ~HRightCode();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_HRIGHTCODE_H


