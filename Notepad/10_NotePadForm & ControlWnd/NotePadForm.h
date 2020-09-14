//NotePadForm.h
#ifndef _NOTEPADFORM_H
#define _NOTEPADFORM_H

#include <afxwin.h>
#include <string.h>
#include<iostream>
#include"Subject.h"
#include"NotePadHistory.h"

using namespace std;

typedef signed long int Long;
class NotePadFormControlWnd;
class NotePadRestorer;
class CaretController;
class ScrollController;
class AutoLineBreak;
class NotePadHistory;
class Selector;
class Glyph;

class NotePadForm :  public CWnd, public Subject {

public:
	NotePadForm();
	
	void SetLogFont(LOGFONT logFont);
	void SetFileTitle(string fileTitle);
	void SetFilePath(string filePath);
	void SetIsAutoLineBreak(bool isAutoLineBreak);
	void SetIsComposition(bool isComposition);
	void SetIsSelected(bool isSelected);
	void SetIsOnSizing(bool isOnSizing);
	void SetSelector(Selector* selector);
	void SetAutoLineBreak(AutoLineBreak* autoLineBreak);
	void SetIsUnDoing(bool isUnDoing);
	void SetIsReDoing(bool isReDoing);
	void SetIsMouseSelecting(bool isMouseSelecting);
	void SetIsMouseClicking(bool isMouseClicking);
	void SetIsScrolling(bool isScrolling);
	void SetIsFontSizing(bool isFontSizing);
	void SetIsFindingContents(bool isFindingContents);
	void SetIsBackRemove(bool isBackRemove);
	void SetIsWithShiftKey(bool isWithShiftKey);
	void SetNoNeedToAutoLineBreak(bool noNeedToAutoLineBreak);
	

	//인라인함수
	NotePadFormControlWnd* GetNotePadFormControlWnd() const;
	BOOL GetIsComposition() const;
	BOOL GetIsAutoLineBreak() const;
	BOOL GetIsSelected() const;
	BOOL GetIsOnSizing() const;
	BOOL GetIsUnDoing() const;
	BOOL GetIsReDoing() const;
	BOOL GetIsMouseSelecting() const;
	BOOL GetIsMouseClicking() const;
	BOOL GetIsScrolling() const;
	BOOL GetIsFontSizing() const;
	BOOL GetIsFindingContents() const;
	BOOL GetIsBackRemove() const;
	BOOL GetIsWithShiftKey() const;
	BOOL GetNoNeedToAutoLineBreak() const;
	NotePadRestorer* GetNotePadRestorer() const;
	ScrollController* GetScrollController() const;
	CaretController* GetCaretController() const;
	Selector* GetSelector() const;
	AutoLineBreak* GetAutoLineBreak() const;

	LOGFONT GetLogFont() const;
	string GetFileTitle() const;
	string GetFilePath() const;
	Long GetCx() const;
	Long GetCy() const;
	
public:
	Glyph* notePad;
	Glyph* row;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnFontMenuBarClicked();
	//afx_msg void OnMenuCommand(UINT nID);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags,short zDelta,CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeChar(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd *cWnd);
	afx_msg void OnKillFocus(CWnd* cWnd);
	afx_msg void OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags);
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()

private:
	NotePadFormControlWnd* notePadFormControlWnd;
	BOOL isComposition;
	BOOL isAutoLineBreak;
	BOOL isSelected;
	BOOL isOnSizing;
	BOOL isUnDoing;
	BOOL isReDoing;
	BOOL isMouseSelecting;
	BOOL isMouseClicking;
	BOOL isScrolling;
	BOOL isFontSizing;
	BOOL isFindingContents;
	BOOL isBackRemove;
	BOOL isWithShiftkey;
	BOOL noNeedToAutoLineBreak;
	AutoLineBreak* autoLineBreak;
	CaretController* caretController;
	ScrollController* scrollController;
	Selector* selector;
	NotePadRestorer* notePadRestorer;
	LOGFONT logFont;
	string fileTitle;
	string filePath;
	Long cx;
	Long cy;  
};


inline NotePadFormControlWnd* NotePadForm::GetNotePadFormControlWnd() const {
	return const_cast<NotePadFormControlWnd*>(this->notePadFormControlWnd);
}

inline BOOL NotePadForm::GetIsComposition() const {
	return this->isComposition;
}
inline BOOL NotePadForm::GetIsAutoLineBreak() const {
	return this->isAutoLineBreak;
}
inline BOOL NotePadForm::GetIsSelected() const {
	return this->isSelected;
}
inline BOOL NotePadForm::GetIsOnSizing() const {
	return this->isOnSizing;
}
inline NotePadRestorer* NotePadForm::GetNotePadRestorer() const {
	return const_cast<NotePadRestorer*>(this->notePadRestorer);
}
inline ScrollController* NotePadForm::GetScrollController() const{
	return const_cast<ScrollController*>(this->scrollController);
}
inline CaretController* NotePadForm::GetCaretController() const {
	return const_cast<CaretController*>(this->caretController);
}
inline Selector* NotePadForm::GetSelector() const {
	return const_cast<Selector*>(this->selector);
}
inline AutoLineBreak* NotePadForm::GetAutoLineBreak() const {
	return const_cast<AutoLineBreak*>(this->autoLineBreak);
}
inline LOGFONT NotePadForm::GetLogFont() const {
	return this->logFont;
}
inline string NotePadForm::GetFileTitle() const {
	return this->fileTitle;
}
inline string NotePadForm::GetFilePath() const {
	return this->filePath;
}
inline Long NotePadForm::GetCx() const {
	return this->cx;
}
inline Long NotePadForm::GetCy() const {
	return this->cy;
}
inline BOOL NotePadForm::GetIsUnDoing() const {
	return this->isUnDoing;
}
inline BOOL NotePadForm::GetIsReDoing() const {
	return this->isReDoing;
}
inline BOOL NotePadForm::GetIsMouseSelecting() const {
	return this->isMouseSelecting;
}
inline BOOL NotePadForm::GetIsMouseClicking() const {
	return this->isMouseClicking;
}
inline BOOL NotePadForm::GetIsScrolling() const {
	return this->isScrolling;
}
inline BOOL NotePadForm::GetIsFontSizing() const {
	return this->isFontSizing;
}
inline BOOL NotePadForm::GetIsFindingContents() const {
	return this->isFindingContents;
}
inline BOOL NotePadForm::GetIsBackRemove() const {
	return this->isBackRemove;
}
inline BOOL NotePadForm::GetIsWithShiftKey() const {
	return this->isWithShiftkey;
}
inline BOOL NotePadForm::GetNoNeedToAutoLineBreak() const {
	return this->noNeedToAutoLineBreak;
}
#endif//!_NOTEPADFORM_H
