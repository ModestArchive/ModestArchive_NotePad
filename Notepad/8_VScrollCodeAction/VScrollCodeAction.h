//VScrollCodeAction.h

#ifndef _VSCROLLCODEACTION_H
#define _VSCROLLCODEACTION_H
#include<afxwin.h>

class NotePadForm;
class ScrollController;
typedef unsigned int UINT;

class VScrollCodeAction {
public:
	VScrollCodeAction(NotePadForm* notePadForm);
	virtual ~VScrollCodeAction() = 0;
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) = 0;

protected:
	NotePadForm* notePadForm;

};
#endif // !_VSCROLLCODEACTION_H