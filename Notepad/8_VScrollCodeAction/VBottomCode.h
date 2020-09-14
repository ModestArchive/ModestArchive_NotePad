//VBottomCode.h
#ifndef _VBOTTOMCODE_H
#define _VBOTTOMCODE_H

#include"VScrollCodeAction.h"
class ScrollController;
class NotePadForm;
class VBottomCode :public VScrollCodeAction {
public:
	VBottomCode(NotePadForm* notePadForm);
	virtual ~VBottomCode() ;
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
#endif // !_VBOTTOMCODE_H
