//HScrollCodeAction.h

#ifndef _HSCROLLCODEACTION_H
#define _HSCROLLCODEACTION_H
#include <afxwin.h>

class NotePadForm;
typedef unsigned int UINT;

class HScrollCodeAction {
public:
	HScrollCodeAction(NotePadForm* notePadForm);
	virtual ~HScrollCodeAction()=0;
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) = 0;
	
protected:
	NotePadForm* notePadForm;
	
};
#endif // !_HSCROLLCODEACTION_H