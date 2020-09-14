//VThumbTrackCode.h

#ifndef _VTHUMBTRACKCODE_H
#define _VTHUMBTRACKCODE_H

#include"VScrollCodeAction.h"
class ScrollController;
class NotePadForm;

class VThumbTrackCode :public VScrollCodeAction {
public:
	VThumbTrackCode(NotePadForm* notePadForm);
	virtual ~VThumbTrackCode();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_VTHUMBTRACKCODE_H




