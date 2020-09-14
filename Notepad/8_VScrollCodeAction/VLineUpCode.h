//VLineUpCode.h
#ifndef _VLINEUPCODE_H
#define _VLINEUPCODE_H

#include"VScrollCodeAction.h"
class ScrollController;
class NotePadForm;
class VLineUpCode :public VScrollCodeAction {
public:
	VLineUpCode(NotePadForm* notePadForm);
	virtual ~VLineUpCode();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_VLINEUPCODE_H


