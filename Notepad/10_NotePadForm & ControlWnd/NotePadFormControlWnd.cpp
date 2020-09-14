//NotePadFormControlWnd.cpp

#include"NotePadFormControlWnd.h"
#include"NotePadForm.h"
#include"CommandFactory.h"
#include"CMyDialog.h"
#include"File.h"
#include"Observer.h"
#include"Subject.h"
#include"TextMetric.h"
#include"Selector.h"
#include"ScrollController.h"
#include"StatusBarMaker.h"
#include"NotePadMetric.h"
#include"NotePadModifier.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
#include"MatchIndexCollector.h"
#include"FindReplaceSupervisor.h"
#include"SelectModifier.h"
#include"NotePadRestorer.h"
#include"NotePad.h"
#include"MatchIndex.h"
#include"resource.h"


BEGIN_MESSAGE_MAP(NotePadFormControlWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(9000, 30006, &NotePadFormControlWnd::OnMenuCommand)
	ON_UPDATE_COMMAND_UI_RANGE(9005, 9005, &NotePadFormControlWnd::OnUpdateCommandUIForUndo)
	ON_UPDATE_COMMAND_UI_RANGE(9006,9006, &NotePadFormControlWnd::OnUpdateCommandUIForRedo)
	ON_UPDATE_COMMAND_UI_RANGE(9007, 9009, &NotePadFormControlWnd::OnUpdateCommandUIForSelectionTask)
	ON_UPDATE_COMMAND_UI_RANGE(9010, 9010, &NotePadFormControlWnd::OnUpdateCommandUIForPasteTask)
	ON_UPDATE_COMMAND_UI_RANGE(20000, 20001, &NotePadFormControlWnd::OnUpdateCommandUIFindAndReplace)
	ON_UPDATE_COMMAND_UI_RANGE(9012, 9013, &NotePadFormControlWnd::OnUpdateCommandUIFindNextAndFindPrevious)
	ON_REGISTERED_MESSAGE(WM_FINDREPLACE, &NotePadFormControlWnd::OnFindReplace)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	//ON_WM_PAINT()
	//ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


NotePadFormControlWnd::NotePadFormControlWnd() {
	this->notePadForm = 0;
	this->statusBar = 0;
	this->contentsFinder = 0;
	this->contentsReplacer = 0;
	this->printer = 0;
	this->noNeedToScroll = false;
}


void NotePadFormControlWnd::SetStatusBar(CStatusBar* cStatusBar) {
	this->statusBar = cStatusBar;
}
void NotePadFormControlWnd::SetContentsFinder(ContentsFinder* contentsFinder) {
	this->contentsFinder = contentsFinder;
}
void NotePadFormControlWnd::SetContentsReplacer(ContentsReplacer* contentsReplacer) {
	this->contentsReplacer = contentsReplacer;
}
void NotePadFormControlWnd::SetNoNeedToScroll(bool noNeedToScroll) {
	this->noNeedToScroll= noNeedToScroll;
}

int NotePadFormControlWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	this->SetIcon(m_hIcon, TRUE);
	CRect rect;
	this->GetClientRect(&rect);
	this->notePadForm = new NotePadForm;
	this->notePadForm->Create(NULL,NULL, WS_CHILD | WS_VISIBLE, rect,this,1234);
	
	CMenu mainMenu;
	mainMenu.CreateMenu();

	CMenu fileMenuPopup;
	fileMenuPopup.CreatePopupMenu();
	CMenu editMenuPopup;
	editMenuPopup.CreatePopupMenu();
	CMenu templateMenuPopup;
	templateMenuPopup.CreatePopupMenu();
	CMenu lookingMenuPopUp;
	lookingMenuPopUp.CreatePopupMenu();
	CMenu helpMenuPopUp;
	helpMenuPopUp.CreatePopupMenu();

	fileMenuPopup.AppendMenu(MF_STRING, 9000, _T("새로 만들기                           Ctrl+N"));
	fileMenuPopup.AppendMenu(MF_STRING, 9001, _T("새창                            Ctrl+Shift+N"));
	fileMenuPopup.AppendMenu(MF_STRING, 10000, _T("열기                                     Ctrl+O"));
	fileMenuPopup.AppendMenu(MF_STRING, 10001, _T("저장                                     Ctrl+S"));
	fileMenuPopup.AppendMenu(MF_STRING, 10002, _T("다른 이름으로 저장         Ctrl+Shift+S"));
	fileMenuPopup.AppendMenu(MF_SEPARATOR);
	fileMenuPopup.AppendMenu(MF_STRING, 9003, _T("페이지 설정하다"));
	fileMenuPopup.AppendMenu(MF_STRING, 10003, _T("인쇄하다                                Ctrl+P"));
	fileMenuPopup.AppendMenu(MF_SEPARATOR);
	fileMenuPopup.AppendMenu(MF_STRING, 9004, _T("끝내다                          Ctrl+Shift+X"));
	////////
	editMenuPopup.AppendMenu(MF_STRING, 9005, _T("실행취소                    Ctrl+Z"));//
	editMenuPopup.AppendMenu(MF_STRING,9006, _T("재실행                       Ctrl+Y"));//
	editMenuPopup.AppendMenu(MF_SEPARATOR);
	editMenuPopup.AppendMenu(MF_STRING,9007 , _T("잘라내다                    Ctrl+X"));//
	editMenuPopup.AppendMenu(MF_STRING,9008 , _T("복사                          Ctrl+C"));//
	editMenuPopup.AppendMenu(MF_STRING, 9009, _T("삭제                     Backspace"));//
	editMenuPopup.AppendMenu(MF_STRING, 9010, _T("붙여넣기                    Ctrl+V"));//
	editMenuPopup.AppendMenu(MF_SEPARATOR);
	editMenuPopup.AppendMenu(MF_STRING, 9011, _T("NAVER로 검색하기       Ctrl+E"));//
	editMenuPopup.AppendMenu(MF_STRING,20000, _T("찾다                           Ctrl+F"));
	editMenuPopup.AppendMenu(MF_STRING,9012 , _T("다음찾기                          F3"));//
	editMenuPopup.AppendMenu(MF_STRING, 9013, _T("이전찾기                  Shift+F3"));//
	editMenuPopup.AppendMenu(MF_STRING, 20001, _T("바꾸다                       Ctrl+H"));
	editMenuPopup.AppendMenu(MF_SEPARATOR);
	editMenuPopup.AppendMenu(MF_STRING, 9014, _T("모두선택                     Ctrl+A"));
	editMenuPopup.AppendMenu(MF_STRING, 20002, _T("시간/날짜                         F5"));
	//////
	templateMenuPopup.AppendMenu(MF_STRING, 30000, _T("자동 줄 바꿈"));
	templateMenuPopup.AppendMenu(MF_STRING, 30001, _T("글꼴"));
	//////
	lookingMenuPopUp.AppendMenu(MF_STRING,30002, _T("상태표시줄"));
	helpMenuPopUp.AppendMenu(MF_STRING,30006,_T("도움말 보기"));
	//////
	CMenu lookingMenuPopUpOfPopUp;
	lookingMenuPopUpOfPopUp.CreatePopupMenu();
	lookingMenuPopUpOfPopUp.AppendMenu(MF_STRING,30003, _T("글씨크기 확대하기"));
	lookingMenuPopUpOfPopUp.AppendMenu(MF_STRING, 30004, _T("글씨크기 축소하기"));
	lookingMenuPopUpOfPopUp.AppendMenu(MF_STRING, 30005, _T("글씨크기 기본값복원"));
	lookingMenuPopUp.AppendMenu(MF_POPUP, (UINT)lookingMenuPopUpOfPopUp.Detach(),_T("글씨 확대하기/축소하기"));


	mainMenu.AppendMenu(MF_POPUP, (UINT)fileMenuPopup.Detach(), _T("파일"));
	mainMenu.AppendMenu(MF_POPUP, (UINT)editMenuPopup.Detach(), _T("편집"));
	mainMenu.AppendMenu(MF_POPUP, (UINT)templateMenuPopup.Detach(), _T("서식"));
	mainMenu.AppendMenu(MF_POPUP, (UINT)lookingMenuPopUp.Detach(), _T("보기"));
	mainMenu.AppendMenu(MF_POPUP, (UINT)helpMenuPopUp.Detach(), _T("도움말"));
	
	SetMenu(&mainMenu);
	mainMenu.Detach();
	
	this->printer = new Printer(this, this->notePadForm);
	return 0;
}

void NotePadFormControlWnd::OnUpdateCommandUIForUndo(CCmdUI* pCmdUI) {
	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength() > 0) {
		if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent()>0) {
			pCmdUI->Enable(TRUE);
		}
		else {
			pCmdUI->Enable(false);
		}
	}
	else {
		pCmdUI->Enable(false);
	}
}

void NotePadFormControlWnd::OnUpdateCommandUIForRedo(CCmdUI* pCmdUI) {
	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength() > 0) {
		if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() < 
			  this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {

			pCmdUI->Enable(TRUE);
		}
		else {
			pCmdUI->Enable(false);
		}
	}
	else {
		pCmdUI->Enable(false);
	}
}


void NotePadFormControlWnd::OnUpdateCommandUIForSelectionTask(CCmdUI* pCmdUI) {
	if (this->notePadForm->GetIsSelected()==true) {
		pCmdUI->Enable(TRUE);
	}
	else {
		pCmdUI->Enable(FALSE);
	}
}


void NotePadFormControlWnd::OnUpdateCommandUIForPasteTask(CCmdUI* pCmdUI) {
	unsigned int priority_list = CF_TEXT;
	char* p_string = NULL;
	// 클립보드에는 문자열만 저장할수 있는것이 아니기 때문에 
	// 현재 문자열이 저장되어 있는지 확인한다. 
	if (::GetPriorityClipboardFormat(&priority_list, 1) == CF_TEXT) {
		// 클립보드에 있는 비트맵 정보를 얻기 위해서 클립보드를 연다. 
		if (::OpenClipboard(this->notePadForm->m_hWnd)) {
			// 클립보드에서 문자열이 저장된 메모리의 핸들 값을 얻는다. 
			HANDLE h_clipboard_data = ::GetClipboardData(CF_TEXT);
			if (h_clipboard_data != NULL) {
				pCmdUI->Enable(TRUE);
			}
			else {
				pCmdUI->Enable(FALSE);
			}
			// 클립보드를 닫는다. 
			::CloseClipboard();
		}
	}
}


void NotePadFormControlWnd::OnUpdateCommandUIFindAndReplace(CCmdUI* pCmdUI) {
	NotePadMetric notePadMetric(this->notePadForm);
	bool thereIsContents = notePadMetric.GetThereIsContents();
	if (thereIsContents==false) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}
}


void NotePadFormControlWnd::OnUpdateCommandUIFindNextAndFindPrevious(CCmdUI* pCmdUI) {
	NotePadMetric notePadMetric(this->notePadForm);
	bool thereIsContents = notePadMetric.GetThereIsContents();
	if (thereIsContents == false) {
		pCmdUI->Enable(FALSE);
	}
	else {
		pCmdUI->Enable(TRUE);
	}
}


LONG NotePadFormControlWnd::OnFindReplace(WPARAM wParam, LPARAM lParam) {
	CFindReplaceDialog* pDlg = CFindReplaceDialog::GetNotifier(lParam);
	FindReplaceSupervisor findReplaceSupervisor(this, this->notePadForm,this->contentsFinder,this->contentsReplacer,pDlg);
	bool isTerminating = false;
	if (pDlg != NULL) {
		if (pDlg->IsTerminating()) {
			isTerminating = true;
			findReplaceSupervisor.SaveInformationAsPdlgTerminating();
		}
		else if (pDlg->FindNext()) {
			if (pDlg->SearchDown()) {
				findReplaceSupervisor.GetReadyToFindNextFromPdlg();
				if (pDlg->MatchCase()) {
					findReplaceSupervisor.DoMatchCaseSearchDown();
				}
				else {
					findReplaceSupervisor.DoNoMatchCaseSearchDown();
				}
			}
			else {
				findReplaceSupervisor.GetReadyToFindPreviousFromPdlg();
				if (pDlg->MatchCase()) {
					findReplaceSupervisor.DoMatchCaseSearchUp();
				}
				else {
					findReplaceSupervisor.DoNoMatchCaseSearchUp();
				}
			}
		}
		else if (pDlg->ReplaceCurrent()) {
			MatchIndex alreadyMatchedIndex(-1, -1, -1, -1);
			alreadyMatchedIndex = findReplaceSupervisor.GetReadyToReplaceCurrentFromPdlg();
			if (pDlg->MatchCase()) {
				findReplaceSupervisor.DoReplaceCurrentMatchCase(alreadyMatchedIndex);
			}
			else{
				findReplaceSupervisor.DoReplaceCurrentNoMatchCase(alreadyMatchedIndex);
			}
		}
		else if (pDlg->ReplaceAll()) {
			findReplaceSupervisor.GetReadyToReplaceAllFromPdlg();
			if (pDlg->MatchCase()) {
				findReplaceSupervisor.DoReplaceAllMatchCase();
			}
			else {
				findReplaceSupervisor.DoReplaceAllNoMatchCase();
			}
		}
	}
	if (this->statusBar != 0) {
		StatusBarMaker statusBarMaker(this);
		statusBarMaker.RefreshPaneContents();
	}
	this->notePadForm->Notify();
	if (this->notePadForm->GetIsSelected() == true) {
		SelectModifier selectModifier(this->notePadForm->GetSelector());
		selectModifier.MoveSumRegionMatchToScrollPosition(this->notePadForm->GetScrollController()->GetHPosition(), this->notePadForm->GetScrollController()->GetVPosition());
		this->notePadForm->GetSelector()->SetOffsetedHPosition(this->notePadForm->GetScrollController()->GetHPosition());
		this->notePadForm->GetSelector()->SetOffsetedVPosition(this->notePadForm->GetScrollController()->GetVPosition());
	}
	if (this->notePadForm->GetIsFindingContents()==true) {
		this->notePadForm->SetIsFindingContents(false);
	}
	this->notePadForm->Invalidate();
	if (isTerminating==false) {//찾아주고나서 스크롤이 갱신된것이 화면에 나타나지않는 경우가 종종생겨서 
		this->notePadForm->SetFocus();
		pDlg->SetFocus();
	}
	return 0;
}


void NotePadFormControlWnd::OnMenuCommand(UINT nID) {
	CommandFactory commandFactory(this->notePadForm,this);
	Command* command = 0;
	bool noNeedToNotify = false;
	command = commandFactory.MakeCommand(nID);
	if (command != 0) {
		command->Execute();
 		delete command;
	}
	this->notePadForm->Notify();
	if (this->noNeedToScroll==true) {
		this->noNeedToScroll = false;
	}
	if (this->notePadForm->GetIsSelected() == true) {
		SelectModifier selectModifier(this->notePadForm->GetSelector());
		selectModifier.MoveSumRegionMatchToScrollPosition(this->notePadForm->GetScrollController()->GetHPosition(), this->notePadForm->GetScrollController()->GetVPosition());
		this->notePadForm->GetSelector()->SetOffsetedHPosition(this->notePadForm->GetScrollController()->GetHPosition());
		this->notePadForm->GetSelector()->SetOffsetedVPosition(this->notePadForm->GetScrollController()->GetVPosition());
	}
	if (this->notePadForm->GetIsFontSizing() == true) {
		this->notePadForm->SetIsFontSizing(false);
	}
	this->notePadForm->Invalidate();
}


void NotePadFormControlWnd::OnSize(UINT nType, int cx, int cy) {
	if (this->statusBar!=0) {
		StatusBarMaker statusBarMaker(this);
		statusBarMaker.MoveStatusBarAndClientArea();
	}
	else {
		this->notePadForm->MoveWindow(CRect(0, 0, cx, cy));
	}
}


void NotePadFormControlWnd::OnSetFocus(CWnd* cWnd) {
	if (this->notePadForm!=0) {	
		this->notePadForm->SetFocus();
	}
}


void NotePadFormControlWnd::OnClose() {
	File file(this->notePadForm);
	string contents = "";
	string fileContents = "";
	string nullString = "";
	string originalBuffer = " 제목 없음 - 메모장 ";
	string captionBuffer = "";
	this->GetWindowText((char*)captionBuffer.c_str(), 100);
	int ret = -1;

	if (strcmp((char*)captionBuffer.c_str(), (char*)originalBuffer.c_str()) == 0) {
		if (strcmp((char*)this->notePadForm->notePad->GetContents().c_str(), (char*)nullString.c_str()) != 0) {
			CMyDialog cMyDialog(this->notePadForm);
			ret = cMyDialog.DoModal();
		}
		else {
			ret = 0;
		}
	}
	else {
		contents = ((NotePad*)(this->notePadForm->notePad))->SaveModeGetContents();
		fileContents = file.Load((char*)this->notePadForm->GetFilePath().c_str());
		if (strcmp((char*)contents.c_str(), (char*)fileContents.c_str()) != 0) {
			CMyDialog cMyDialog(this->notePadForm);
			ret = cMyDialog.DoModal();
		}
		else {
			ret = 0;
		}
	}
	if (ret == 0) {
		if (this->statusBar!=0) {
			delete this->statusBar;
		}
		if (this->contentsFinder!=0) {
			delete this->contentsFinder;
		}
		if (this->contentsReplacer!=0) {
			delete this->contentsReplacer;
		}
		if (this->printer!=0) {
			delete this->printer;
		}
		this->notePadForm->OnClose();
		this->notePadForm = 0;
		CFrameWnd::OnClose();
	}
}