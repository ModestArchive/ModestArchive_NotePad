//HLineLeftCode.h
#ifndef _HLINELEFTCODE_H
#define _HLINELEFTCODE_H
#include"HScrollCodeAction.h"

class NotePadForm;

class HLineLeftCode :public HScrollCodeAction {
public:
	HLineLeftCode(NotePadForm* notePadForm);
	virtual ~HLineLeftCode();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_HLINELEFTCODE_H


