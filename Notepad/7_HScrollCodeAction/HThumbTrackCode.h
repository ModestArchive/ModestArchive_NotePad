//HThumbTrackCode.h
#ifndef _HTHUMBTRACKCODE_H
#define _HTHUMBTRACKCODE_H

#include "HScrollCodeAction.h"
typedef signed long int Long;

class NotePadForm;

class HThumbTrackCode :public HScrollCodeAction {
public:
	HThumbTrackCode(NotePadForm* notePadForm);
	virtual ~HThumbTrackCode();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_HTHUMBTRACKCODE_H


