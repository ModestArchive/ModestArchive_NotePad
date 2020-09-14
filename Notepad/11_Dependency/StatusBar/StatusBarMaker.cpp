//StatusBarMaker.cpp

#include"StatusBarMaker.h"
#include"NotePadFormControlWnd.h"
#include"NotePadForm.h"
#include"Glyph.h"
#include<imm.h>
#include<atlstr.h>

static UINT BASED_CODE indicators[] = {
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
};


StatusBarMaker::StatusBarMaker(NotePadFormControlWnd* notePadFormControlWnd) {
	this->notePadFormControlWnd=notePadFormControlWnd;
}


StatusBarMaker::~StatusBarMaker() {

}


void StatusBarMaker::SetStatusBar() {
	CStatusBar* cStatusBar = new CStatusBar;
	CRect rect;
	this->notePadFormControlWnd->GetClientRect(&rect);
	this->notePadFormControlWnd->SetStatusBar(cStatusBar);
	cStatusBar->Create(this->notePadFormControlWnd);
	cStatusBar->SetIndicators(indicators, 5);
	cStatusBar->SetPaneInfo(0, ID_SEPARATOR, SBPS_STRETCH, 0);
	cStatusBar->SetPaneInfo(1, ID_SEPARATOR, SBPS_NORMAL, rect.Width() / 3);
	cStatusBar->SetPaneInfo(2, ID_SEPARATOR, SBPS_NORMAL, rect.Width() / 15);
	cStatusBar->SetPaneInfo(3, ID_INDICATOR_CAPS, SBPS_NORMAL, rect.Width() / 30);
	cStatusBar->SetPaneInfo(4, ID_INDICATOR_NUM, SBPS_NORMAL, rect.Width() / 30);
	CString string;
	string.Format("   Line:  %d , Column:  %d", this->notePadFormControlWnd->GetNotePadForm()->notePad->GetCurrent()+1,
												this->notePadFormControlWnd->GetNotePadForm()->row->GetCurrent());
	cStatusBar->SetPaneText(1, string);
	
	DWORD conv, sentence;
	HIMC h_imc = ImmGetContext(this->notePadFormControlWnd->m_hWnd);
	// IME(input method editor) 상태를 얻는다.
	ImmGetConversionStatus(h_imc, &conv, &sentence);
	ImmReleaseContext(this->notePadFormControlWnd->m_hWnd, h_imc);
	if (conv & IME_CMODE_LANGUAGE) {
		cStatusBar->SetPaneText(2, "   한글입력");
	}
	else{
		cStatusBar->SetPaneText(2, "   영어입력");
	}
	this->notePadFormControlWnd->GetNotePadForm()->MoveWindow(CRect(0, 0, rect.Width(), rect.Height() - 30));
	cStatusBar->MoveWindow(CRect(0, rect.Height() - 30, rect.Width(), rect.Height()));	
}


void StatusBarMaker::MoveStatusBarAndClientArea() {
	CRect rect;
	this->notePadFormControlWnd->GetClientRect(&rect);
	this->notePadFormControlWnd->GetStatusBar()->MoveWindow(CRect(0, rect.Height() - 30, rect.Width(), rect.Height()));
	this->notePadFormControlWnd->GetNotePadForm()->MoveWindow(CRect(0,0,rect.Width(),rect.Height()-30));
}


void StatusBarMaker::RemoveStatusBar() {
	if (this->notePadFormControlWnd->GetStatusBar() != 0) {
		delete this->notePadFormControlWnd->GetStatusBar();
		this->notePadFormControlWnd->SetStatusBar(0);
	}
	CRect rect;
	this->notePadFormControlWnd->GetClientRect(&rect);
	this->notePadFormControlWnd->GetNotePadForm()->MoveWindow(CRect(0, 0, rect.Width(), rect.Height()));
}


void StatusBarMaker::RefreshPaneContents() {
	CString string;
	string.Format("   Line:  %d , Column:  %d", this->notePadFormControlWnd->GetNotePadForm()->notePad->GetCurrent()+1,
												this->notePadFormControlWnd->GetNotePadForm()->row->GetCurrent());
	this->notePadFormControlWnd->GetStatusBar()->SetPaneText(1, string);
	
	DWORD conv, sentence;
	HIMC h_imc = ImmGetContext(this->notePadFormControlWnd->m_hWnd);
	// IME(input method editor) 상태를 얻는다.
	ImmGetConversionStatus(h_imc, &conv, &sentence);
	ImmReleaseContext(this->notePadFormControlWnd->m_hWnd, h_imc);
	if (conv & IME_CMODE_LANGUAGE) {
		this->notePadFormControlWnd->GetStatusBar()->SetPaneText(2, "   한글입력");
	}
	else {
		this->notePadFormControlWnd->GetStatusBar()->SetPaneText(2, "   영어입력");
	}
}