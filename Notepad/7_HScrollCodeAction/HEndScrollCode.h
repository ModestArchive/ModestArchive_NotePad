//HEndScrollCode.h
#ifndef _HENDSCROLLCODE_H
#define _HENDSCROLLCODE_H

#include "HScrollCodeAction.h"

class NotePadForm;

class  HEndScrollCode :public HScrollCodeAction {
public:
	HEndScrollCode(NotePadForm* notePadForm);
	virtual ~HEndScrollCode();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_HENDSCROLLCODE_H


