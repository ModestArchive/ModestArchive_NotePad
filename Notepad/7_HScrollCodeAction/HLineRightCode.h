//HLineRightCode.h
#ifndef _HLINERIGHTCODE_H
#define _HLINERIGHTCODE_H

#include"HScrollCodeAction.h"

class NotePadForm;

class HLineRightCode :public HScrollCodeAction {
public:
	HLineRightCode(NotePadForm* notePadForm);
	virtual ~HLineRightCode();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_HLINELEFTCODE_H



