//HPageLeftCode.h
#ifndef _HPAGELEFTCODE_H
#define _HPAGELEFTCODE_H

#include "HScrollCodeAction.h"

class NotePadForm;

class HPageLeftCode :public HScrollCodeAction {
public:
	HPageLeftCode(NotePadForm* notePadForm);
	virtual ~HPageLeftCode();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_HPAGELEFTCODE_H


