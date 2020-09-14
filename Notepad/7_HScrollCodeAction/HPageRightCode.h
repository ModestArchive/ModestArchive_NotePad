//HPageRightCode.h
#ifndef _HPAGERIGHTCODE_H
#define _HPAGERIGHTCODE_H

#include "HScrollCodeAction.h"

class NotePadForm;

class HPageRightCode :public HScrollCodeAction {
public:
	HPageRightCode(NotePadForm* notePadForm);
	virtual ~HPageRightCode();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_HPAGERIGHTCODE_H

