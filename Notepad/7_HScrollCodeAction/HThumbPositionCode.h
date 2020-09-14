//HThumbPositionCode.h
#ifndef _HTHUMBPOSITIONCODE_H
#define _HTHUMBPOSITIONCODE_H

#include "HScrollCodeAction.h"
typedef signed long int Long;

class NotePadForm;

class HThumbPositionCode :public HScrollCodeAction {
public:
	HThumbPositionCode(NotePadForm* notePadForm);
	virtual ~HThumbPositionCode();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_HTHUMBPOSITIONCODE_H


