//NotePadFormControlWnd.h
#ifndef _NOTEPADFORMCONTROLWND_H
#define _NOTEPADFORMCONTROLWND_H

#include<afxwin.h>
#include<afxext.h>
#include"ContentsFinder.h"
#include"ContentsReplacer.h"
#include"Printer.h"

class NotePadForm;
static UINT WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);

class NotePadFormControlWnd :public CFrameWnd {
public:
	NotePadFormControlWnd();
	//셋함수
	void SetStatusBar(CStatusBar* cStatusBar);
	void SetContentsFinder(ContentsFinder* contentsFinder);
	void SetContentsReplacer(ContentsReplacer* contentsReplacer);
	void SetNoNeedToScroll(bool noNeedToScroll);

	
	//인라인함수
	NotePadForm* GetNotePadForm() const;
	CStatusBar* GetStatusBar() const;
	ContentsFinder* GetContentsFinder() const;
	ContentsReplacer* GetContentsReplacer() const;
	Printer* GetPrinter() const;
	bool GetNoNeedToScroll() const;
	
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnFontMenuBarClicked();
	afx_msg void OnUpdateCommandUIForUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommandUIForRedo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommandUIForSelectionTask(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommandUIForPasteTask(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommandUIFindAndReplace(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommandUIFindNextAndFindPrevious(CCmdUI* pCmdUI);
	afx_msg LONG OnFindReplace(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuCommand(UINT nID);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* cWnd);
	//afx_msg void OnPaint();
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
	
private:
	NotePadForm* notePadForm;
	CStatusBar* statusBar;
	ContentsFinder* contentsFinder;
	ContentsReplacer* contentsReplacer;
	Printer* printer;
	bool noNeedToScroll;
};

inline NotePadForm* NotePadFormControlWnd::GetNotePadForm() const {
	return const_cast<NotePadForm*>(this->notePadForm);
}
inline CStatusBar* NotePadFormControlWnd::GetStatusBar() const {
	return const_cast<CStatusBar*>(this->statusBar);
}
inline ContentsFinder* NotePadFormControlWnd::GetContentsFinder() const {
	return const_cast<ContentsFinder*>(this->contentsFinder);
}
inline ContentsReplacer* NotePadFormControlWnd::GetContentsReplacer() const {
	return const_cast<ContentsReplacer*>(this->contentsReplacer);
}
inline Printer* NotePadFormControlWnd::GetPrinter() const {
	return const_cast<Printer*>(this->printer);
}
inline bool NotePadFormControlWnd::GetNoNeedToScroll() const {
	return this->noNeedToScroll;
}
#endif // !_NOTEPADFORMCONTROLWND_H
