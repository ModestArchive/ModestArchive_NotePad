#include"NotePadApp.h"
#include"NotePadForm.h"
#include"NotePadFormControlWnd.h"
#include<Windows.h>

BOOL NotePadApp::InitInstance() {
	
	NotePadFormControlWnd* notePadFormControlWnd = new NotePadFormControlWnd;
	
	notePadFormControlWnd->Create(NULL," 제목 없음 - 메모장 ");
	notePadFormControlWnd->ShowWindow(SW_SHOW);
	
	notePadFormControlWnd->UpdateWindow();
	this->m_pMainWnd = notePadFormControlWnd;
	return TRUE;
	
}
NotePadApp notePadApp;
#if 0;
	NotePadForm* notePadForm = new NotePadForm;
	
	notePadForm->Create(NULL, " 제목 없음 - 메모장 ");
	notePadForm->ShowWindow(SW_SHOW);
	notePadForm->UpdateWindow();
	this->m_pMainWnd = notePadForm;
#endif 0;