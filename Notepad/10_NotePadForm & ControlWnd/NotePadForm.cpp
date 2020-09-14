//NotePadForm.cpp

#include<afxdlgs.h>
#include"Glyph.h"
#include"TextMetric.h"
#include"SingleByteCharacter.h"
#include"NotePadForm.h"
#include"GlyphFactory.h"
#include"CaretController.h"
#include"Font.h"
#include"File.h"
#include"NotePadMaker.h"
#include"KeyActionFactory.h"
#include"ScrollController.h"
#include"VScrollCodeActionFactory.h"
#include"HScrollCodeActionFactory.h"
#include"VScrollCodeAction.h"
#include"HScrollCodeAction.h"
#include"Scroll.h"
#include"CommandFactory.h"
#include"MouseMove.h"
#include"CMyDialog.h"
#include"MouseWheelAction.h"
#include"LineBreakCommand.h"
#include"Row.h"
#include"DummyRow.h"
#include"MouseWheelActionFactory.h"
#include"NotePadHistory.h"
#include"Selector.h"
#include"SelectModifier.h"
#include"MouseLeave.h"
#include"SelectionEraseSupervisor.h"
#include"NotePadRestorer.h"
#include"StringMaker.h"
#include"NotePadFormControlWnd.h"
#include"StatusBarMaker.h"
#include"FindReplaceSupervisor.h"
#include"SelectionJudge.h"
#include"CBufferDC.h"
#include"ScrollControllerSupporter.h"
#include"NotePadMetric.h"
#include"MouseLButtonAction.h"
#include"MouseLButtonActionFactory.h"


BEGIN_MESSAGE_MAP(NotePadForm, CWnd)
	ON_WM_CREATE()
	//ON_COMMAND_RANGE(10000 ,20001, &NotePadForm::OnMenuCommand)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_COMPOSITION,OnImeComposition)
	ON_MESSAGE(WM_IME_CHAR, OnImeChar)
	ON_MESSAGE(WM_IME_STARTCOMPOSITION, OnImeStartComposition)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_MENUSELECT()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

NotePadForm::NotePadForm() {
	//public
	this->notePad = 0;
	this->row = 0;
	//private
	this->notePadFormControlWnd = 0;
	this->isComposition = false;
	this->isAutoLineBreak = false;
	this->isSelected = false;
	this->isOnSizing = false;
	this->isUnDoing = false;
	this->isReDoing = false;
	this->isMouseSelecting = false;
	this->isMouseClicking = false;
	this->isScrolling = false;
	this->isFontSizing = false;
	this->isFindingContents = false;
	this->isBackRemove = false;
	this->isWithShiftkey = false;
	this->noNeedToAutoLineBreak = false;
	this->autoLineBreak = 0;
	this->caretController = 0;
	this->scrollController = 0;
	this->selector = 0;
	this->notePadRestorer = 0;
	this->logFont;
	::ZeroMemory(&logFont, sizeof(logFont));
	this->filePath = "";
	this->fileTitle = "";
	this->cx = 0;
	this->cy = 0;
}


void NotePadForm::SetLogFont(LOGFONT logFont) {
	this->logFont = logFont;
}
void NotePadForm::SetFileTitle(string fileTitle) {
	this->fileTitle = fileTitle;
}
void NotePadForm::SetFilePath(string filePath) {
	this->filePath = filePath;
}
void NotePadForm::SetIsAutoLineBreak(bool isAutoLineBreak) {
	this->isAutoLineBreak = isAutoLineBreak;
}
void NotePadForm::SetIsComposition(bool isComposition) {
	this->isComposition = isComposition;
}
void NotePadForm::SetIsSelected(bool isSelected) {
	this->isSelected = isSelected;
}
void NotePadForm::SetIsOnSizing(bool isOnSizing) {
	this->isOnSizing = isOnSizing;
}
void NotePadForm::SetSelector(Selector* selector) {
	this->selector = selector;
}
void NotePadForm::SetAutoLineBreak(AutoLineBreak* autoLineBreak) {
	this->autoLineBreak = autoLineBreak;
}
void NotePadForm::SetIsUnDoing(bool isUnDoing) {
	this->isUnDoing = isUnDoing;
}
void NotePadForm::SetIsReDoing(bool isReDoing) {
	this->isReDoing = isReDoing;
}
void NotePadForm::SetIsMouseSelecting(bool isMouseSelecting) {
	this->isMouseSelecting = isMouseSelecting;
}
void NotePadForm::SetIsMouseClicking(bool isMouseClicking) {
	this->isMouseClicking = isMouseClicking;
}
void NotePadForm::SetIsScrolling(bool isScrolling) {
	this->isScrolling = isScrolling;
}
void NotePadForm::SetIsFontSizing(bool isFontSizing) {
	this->isFontSizing = isFontSizing;
}
void NotePadForm::SetIsFindingContents(bool isFindingContents) {
	this->isFindingContents = isFindingContents;
}
void NotePadForm::SetIsBackRemove(bool isBackRemove) {
	this->isBackRemove = isBackRemove;
}
void NotePadForm::SetIsWithShiftKey(bool isWithShiftKey) {
	this->isWithShiftkey = isWithShiftKey;
}
void NotePadForm::SetNoNeedToAutoLineBreak(bool noNeedToAutoLineBreak) {
	this->noNeedToAutoLineBreak = noNeedToAutoLineBreak;
}
int NotePadForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);//�ڵ��� ���뼺
	
	this->notePadFormControlWnd = ((NotePadFormControlWnd*)(this->GetParent()));
	CRect rect;
	this->GetClientRect(rect);
	this->cx = 0;//rect.right;
	this->cy = 0;//rect.bottom;

	Font font(this);
	LOGFONT logFont = font.MakeInitialLogFont();
	this->logFont = logFont;

	GlyphFactory glyphFactory;
	this->notePad = glyphFactory.MakeGlyph((char*)(""));
	this->row = glyphFactory.MakeGlyph((char*)("\r\n"));
	this->notePad->Add(this->row);
	this->notePad->First();
	this->row->First();

	Scroll* scroll = new Scroll(this);
	this->scrollController = new ScrollController(scroll, this);
	this->selector = new Selector(this);
	this->notePadRestorer = new NotePadRestorer(this);
	
	return 0;
}


void NotePadForm::OnSize(UINT nType, int cx, int cy) {
	if (this->cx!=cx||this->cy!=cy) {
		this->isOnSizing = true;
	}
	this->cx = cx;
	this->cy = cy;
	this->scrollController->GetScroll()->SetScrollWidth(cx);
	this->scrollController->GetScroll()->SetScrollHeight(cy);
	
	if (cx > 0 && cy > 0) {
		Notify();
		
		this->isOnSizing = false;
		if (this->isSelected == TRUE) {
			SelectModifier selectModifier(this->selector);
			selectModifier.MoveSumRegionMatchToScrollPosition(this->scrollController->GetHPosition(), this->scrollController->GetVPosition());
			this->selector->SetOffsetedHPosition(this->scrollController->GetHPosition());
			this->selector->SetOffsetedVPosition(this->scrollController->GetVPosition());
		}
	}
	Invalidate();
}


void NotePadForm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {

	HScrollCodeActionFactory hScrollCodeActionFactory(this);
	HScrollCodeAction* hScrollCodeAction = 0;

	hScrollCodeAction = hScrollCodeActionFactory.MakeCodeAction(nSBCode);
	if (hScrollCodeAction != 0) {
		this->isScrolling = true;
		hScrollCodeAction->OnHScroll(nSBCode,nPos,pScrollBar);
		delete hScrollCodeAction;
	}

	if (this->isSelected == TRUE) {
		SelectModifier selectModifier(this->selector);
		selectModifier.MoveSumRegionMatchToScrollPosition(this->scrollController->GetHPosition(), this->scrollController->GetVPosition());
		this->selector->SetOffsetedHPosition(this->scrollController->GetHPosition());
		this->selector->SetOffsetedVPosition(this->scrollController->GetVPosition());
	}
	Notify();
	if (this->isScrolling==true) {
		this->isScrolling = false;
	}
	Invalidate();
}


void NotePadForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {

	VScrollCodeActionFactory vScrollCodeActionFactory(this);
	VScrollCodeAction* vScrollCodeAction = 0;

	vScrollCodeAction = vScrollCodeActionFactory.MakeCodeAction(nSBCode);
	if (vScrollCodeAction != 0) {
		this->isScrolling = true;
		vScrollCodeAction->OnVScroll(nSBCode,nPos,pScrollBar);
		delete vScrollCodeAction;
	}
	if (this->isSelected == TRUE) {
		SelectModifier selectModifier(this->selector);
		selectModifier.MoveSumRegionMatchToScrollPosition(this->scrollController->GetHPosition(), this->scrollController->GetVPosition());
		this->selector->SetOffsetedHPosition(this->scrollController->GetHPosition());
		this->selector->SetOffsetedVPosition(this->scrollController->GetVPosition());
	}
	Notify();
	if (this->isScrolling==true) {
		this->isScrolling = false;
	}
	Invalidate();
}


BOOL NotePadForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	MouseWheelActionFactory mouseWheelActionFactory(this);
	MouseWheelAction* mouseWheelAction = 0;
	bool isControlPushing = false;
	if (GetKeyState(VK_CONTROL) & 0x8000) {
		isControlPushing = true;
		this->isFontSizing = true;
	}
	else {
		this->isScrolling = true;
	}
	mouseWheelAction = mouseWheelActionFactory.MakeMouseWheel(zDelta,isControlPushing);
	if (mouseWheelAction != 0) {
		mouseWheelAction->OnMouseWheel(nFlags, zDelta, pt);
		delete mouseWheelAction;
	}
	Notify();
	SelectModifier selectModifier(this->selector);
	if (this->isSelected == TRUE) {
		if (this->isFontSizing == true) {
			if (this->selector->IsRightDownWardSelectedArea() == true) {
				this->selector->ReHighLightRightDownwardSumRegionMatchToClientArea();
			}
			else {
				this->selector->ReHighLightLeftUpwardSumRegionMatchToClientArea();
			}
		}
		else {
			selectModifier.MoveSumRegionMatchToScrollPosition(this->scrollController->GetHPosition(), this->scrollController->GetVPosition());
			this->selector->SetOffsetedHPosition(this->scrollController->GetHPosition());
			this->selector->SetOffsetedVPosition(this->scrollController->GetVPosition());
		}
	}
	if (this->isScrolling==true) {
		this->isScrolling = false;
	}
	if (this->isFontSizing==true) {
		this->isFontSizing = false;
	}
	Invalidate();
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void  NotePadForm::OnLButtonDown(UINT nFlags, CPoint point) {
	
	MouseLButtonAction* mouseLButtonAction = 0;
	MouseLButtonActionFactory mouseLButtonActionFactory(this);
	mouseLButtonAction= mouseLButtonActionFactory.MakeMouseAction();
	if (mouseLButtonAction!=0) {
		mouseLButtonAction->OnLButtonDown(nFlags, point);
		delete mouseLButtonAction;
	}
	this->isMouseClicking = true;
	if (((NotePadFormControlWnd*)(this->GetParent()))->GetStatusBar() != 0) {
		StatusBarMaker statusBarMaker(((NotePadFormControlWnd*)(this->GetParent())));
		statusBarMaker.RefreshPaneContents();
	}
	Notify();
	SelectionJudge selectionJudge(this, this->selector);
	selectionJudge.SelectionDecide();

	if (this->noNeedToAutoLineBreak == true) {
		this->noNeedToAutoLineBreak = false;
	}
	if (this->isMouseClicking==true) {
		this->isMouseClicking = false;
	}
	Invalidate();
}


void NotePadForm::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags==MK_LBUTTON) {
		SetCapture();
		this->isMouseSelecting = true;
		MouseMove mouseMove(this);
		mouseMove.OnMouseMove(nFlags, point);
	
		Notify();
		SelectionJudge selectionJudge(this, this->selector);
		selectionJudge.SelectionDecide();

		if (this->noNeedToAutoLineBreak == true) {
			this->noNeedToAutoLineBreak = false;
		}
		if (this->isSelected == TRUE) {
			SelectModifier selectModifier(this->selector);
			selectModifier.MoveSumRegionMatchToScrollPosition(this->scrollController->GetHPosition(), this->scrollController->GetVPosition());
			this->selector->SetOffsetedHPosition(this->scrollController->GetHPosition());
			this->selector->SetOffsetedVPosition(this->scrollController->GetVPosition());
		}
		if (this->isMouseSelecting==true) {
			this->isMouseSelecting = false;
		}
		Invalidate();
		if (((NotePadFormControlWnd*)(this->GetParent()))->GetStatusBar() != 0) {
			StatusBarMaker statusBarMaker(((NotePadFormControlWnd*)(this->GetParent())));
			statusBarMaker.RefreshPaneContents();
		}
	}
}


void NotePadForm::OnLButtonUp(UINT nFlags,CPoint point) {
	ReleaseCapture();
}


void NotePadForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	NotePadMaker notePadMaker(this);

	if (!(GetKeyState(VK_CONTROL) & 0x8000)) {//�߰�ȣ ���� �ϴ� ���µ� ���߿� �������� Ȯ���غ���!
		if (this->isSelected == true) {
			SelectionEraseSupervisor selectionEraseSupervisor(this);
			StringMaker stringMaker(this);
			string* contents = new string(stringMaker.MakeStringInSelectedArea());
			selectionEraseSupervisor.EraseContents(contents,false);
			if (this->isSelected == true) {
				this->isSelected = false;
				if (this->selector != 0) {
					delete this->selector;
				}
				this->selector  = new Selector(this);
				if (((NotePadFormControlWnd*)(this->GetParent()))->GetContentsFinder() != 0) {
					FindReplaceSupervisor findReplaceSupervisor(((NotePadFormControlWnd*)(this->GetParent())), this,
						((NotePadFormControlWnd*)(this->GetParent()))->GetContentsFinder(), 0, 0);
					findReplaceSupervisor.DeleteMatchIndexCollector();
				}
			}
		}
		if (nChar == VK_RETURN) {//���� �Է½�
			notePadMaker.PlusRowInNotePad();
		}
		else if (nChar != VK_BACK&&nChar!=VK_ESCAPE) {
			
			TCHAR buffer[2];
			buffer[0] = nChar;
			buffer[1] = '\0';
			if (nChar == VK_TAB) {//�� �Է½�
				notePadMaker.WriteTabInRow(buffer);
			}
			else if (!(GetKeyState(VK_CONTROL) & 0x8000)) {//���ĺ��Է½�
				notePadMaker.WriteSingleByteCharacterInRow(buffer);
			}
		}
		Notify();
		Invalidate();//���Ž����ִ� �̺�Ʈ ��ü�� �����ϱ� ������ �ʿ��� �̺�Ʈ���ٰ� ���� ������ �ҷ����� �ؾ��ϴ°��� @@������@@
	}
	if (((NotePadFormControlWnd*)(this->GetParent()))->GetStatusBar() != 0) {
		StatusBarMaker statusBarMaker(((NotePadFormControlWnd*)(this->GetParent())));
		statusBarMaker.RefreshPaneContents();
	}
	
}


LRESULT NotePadForm::OnImeComposition(WPARAM wParam, LPARAM lParam) {
	NotePadMaker notePadMaker(this);
	NotePadMetric notePadMetric(this);
	ScrollControllerSupporter scrollControllerSupporter(this,this->scrollController);
	Font font(this);
	TEXTMETRIC tm = font.CalculateFontMetric();
	if (this->isSelected == true) {
		SelectionEraseSupervisor selectionEraseSupervisor(this);
		StringMaker stringMaker(this);
		string* contents = new string(stringMaker.MakeStringInSelectedArea());
		selectionEraseSupervisor.EraseContents(contents, false);

		this->isSelected = false;
		if (this->selector != 0) {
			delete this->selector;
		}
		this->selector = new Selector(this);
		if (((NotePadFormControlWnd*)(this->GetParent()))->GetContentsFinder() != 0) {
			FindReplaceSupervisor findReplaceSupervisor(((NotePadFormControlWnd*)(this->GetParent())), this,
				((NotePadFormControlWnd*)(this->GetParent()))->GetContentsFinder(), 0, 0);
			findReplaceSupervisor.DeleteMatchIndexCollector();
		}
	}
	TCHAR buffer[3];
	buffer[0] = HIBYTE(WORD(wParam));// 4����Ʈ�� word ũ���̰�, �ݿ��尡 2����Ʈ�̴�. ���Ի����ؼ� 32bit �� 64bit ��ǻ�͸� ����
									    // ���ڴ� ��������� ���ڴ� ������������ cpu�� �ѹ��� �����͸� ó���ϴ� ���̴�.
	buffer[1] = LOBYTE(WORD(wParam));
	buffer[2] = '\0';
	notePadMaker.WriteDoubleByteCharacterInRow(buffer);
	
	if (((NotePadFormControlWnd*)(this->GetParent()))->GetStatusBar() != 0) {
		StatusBarMaker statusBarMaker(((NotePadFormControlWnd*)(this->GetParent())));
		statusBarMaker.RefreshPaneContents();
	}
	Notify();
	Invalidate();
	return ::DefWindowProc(this->m_hWnd, WM_IME_COMPOSITION, wParam, lParam);
	
}


LRESULT NotePadForm::OnImeStartComposition(WPARAM wParam, LPARAM lParam) {
	
	return 0;
}
	

LRESULT NotePadForm::OnImeChar(WPARAM wParam, LPARAM lParam) {
	if (!(GetKeyState(VK_CONTROL) & 0x8000)) {
		NotePadMaker notePadMaker(this);
		TCHAR buffer[3];
		buffer[0] = HIBYTE(WORD(wParam));
		buffer[1] = LOBYTE(WORD(wParam));
		buffer[2] = '\0';

		notePadMaker.WriteCompleteDoubleByteCharacterInRow(buffer);
	}
	this->isComposition = false;

	Notify();
	Invalidate();
	return 0;
}


void NotePadForm::OnPaint() {

	CPaintDC dc(this);
	CBufferDC bufferDC(this);

	CFont newFont;
	newFont.CreateFontIndirect(&this->logFont);
	CFont* oldFont = dc.SelectObject(&newFont);
	TEXTMETRIC tm = { 0, };
	dc.GetTextMetrics(&tm);

	dc.FillSolidRect(0, 0, this->cx, this->cy, RGB(255, 255, 255));////////////
	dc.SetBkMode(TRANSPARENT);
	if (this->isSelected == true) {//���ÿ��� ĥ�ϰ�
		CBrush brush;
		brush.CreateSolidBrush(RGB(184, 134, 12));
		CBrush* pOldBrush = dc.SelectObject(&brush);
		dc.PaintRgn(this->selector->GetSumRegion());
		dc.SelectObject(pOldBrush);
		brush.DeleteObject();
	}
	if (isSelected == false) {
		dc.SetBkMode(WHITENESS);
	}
	Long i = 0;
	while (i < this->notePad->GetLength()) {
		dc.TextOut(0 + tm.tmAveCharWidth / 4 - (this->scrollController->GetHPosition()),
			(i * (tm.tmHeight + 5)) - (this->scrollController->GetVPosition()),
			this->notePad->GetAt(i)->GetContents().c_str());
		i++;
	}
	if (this->isSelected == true) {//�������Ѽ� �۾� �Ͼ�� ���ÿ��� �Ķ������� ó�����ش�.
		dc.InvertRgn(this->selector->GetSumRegion());
	}
	dc.SelectObject(oldFont);
	newFont.DeleteObject();
}
	

BOOL NotePadForm::OnEraseBkgnd(CDC* pDC) {
	
	return TRUE;
}


void NotePadForm::OnSetFocus(CWnd * cWnd) {
	
	if (this->caretController==0) {
		this->caretController = new CaretController(this);
	}
	
	Notify();
	
	if (this->notePadFormControlWnd->GetNoNeedToScroll() == true) {
		this->notePadFormControlWnd->SetNoNeedToScroll(false);
	}
	if (this->isSelected == TRUE) {
		SelectModifier selectModifier(this->selector);
		selectModifier.MoveSumRegionMatchToScrollPosition(this->scrollController->GetHPosition(), this->scrollController->GetVPosition());
		this->selector->SetOffsetedHPosition(this->scrollController->GetHPosition());
		this->selector->SetOffsetedVPosition(this->scrollController->GetVPosition());
	}

}


void NotePadForm::OnKillFocus(CWnd* cWnd) {
	this->caretController->KillCaret();
	((Subject*)(this))->Detach(this->caretController);
	this->caretController = 0;
}


void NotePadForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	KeyActionFactory keyActionFactory(this);
	KeyAction* keyAction = 0;
	keyAction = keyActionFactory.MakeKey(nChar);
	
	
	if (keyAction != 0) {
		keyAction->OnKeyDown(nChar, nRepCnt, nFlags);
        delete keyAction;  //��¶�� ���丮���� �Ҵ����༭ �ּҸ� �Ѱ��ִ� �Ŵϱ� ���߿� �� ����!!!! !!!!!!#@#@#@#@#@#@#@#@#@#
		Notify();
		if (this->noNeedToAutoLineBreak==true) {
			this->noNeedToAutoLineBreak = false;
		}
		if (this->isWithShiftkey == true) {
			SelectionJudge selectionJudge(this, this->selector);
			selectionJudge.SelectionDecide();
			this->isWithShiftkey = false;
		}
		if (this->isBackRemove==true) {
			this->isBackRemove = false;
		}
		if (this->isSelected == TRUE) {//ctrl+c�� �ϰ��� ��ũ���� �ø��ų� ������ �ٽ� ctrl+c�� �ϸ� ���ÿ����� �ȸ´´�.
			SelectModifier selectModifier(this->selector);
			selectModifier.MoveSumRegionMatchToScrollPosition(this->scrollController->GetHPosition(), this->scrollController->GetVPosition());
			this->selector->SetOffsetedHPosition(this->scrollController->GetHPosition());
			this->selector->SetOffsetedVPosition(this->scrollController->GetVPosition());
		}
		if (this->isUnDoing==true||this->isReDoing==true) {//���������ֱ�
			if (this->isSelected == TRUE) {
				SelectModifier selectModifier(this->selector);
				selectModifier.MoveSumRegionMatchToScrollPosition(this->scrollController->GetHPosition(), this->scrollController->GetVPosition());
				this->selector->SetOffsetedHPosition(this->scrollController->GetHPosition());
				this->selector->SetOffsetedVPosition(this->scrollController->GetVPosition());
			}
			this->isUnDoing = false;
			this->isReDoing = false;
		}
		Invalidate();
	}
	if (((NotePadFormControlWnd*)(this->GetParent()))->GetStatusBar() != 0) {
		StatusBarMaker statusBarMaker(((NotePadFormControlWnd*)(this->GetParent())));
		statusBarMaker.RefreshPaneContents();
	}
}


void NotePadForm::OnClose() {
	if (this->selector!=0) {
		delete this->selector;
		this->isSelected = false;
	}
	if (this->notePadRestorer!=0) {
		delete this->notePadRestorer;
	}
	NotePadRestorer* notePadRestorer;
	if (this->autoLineBreak!=0) {
		((Subject*)(this))->Detach((Observer*)(this->autoLineBreak));
	}
	((Subject*)(this))->Detach((Observer*)(this->caretController));
	((Subject*)(this))->Detach((Observer*)(this->scrollController));
	CWnd::OnClose();
}
#if 0;
CDC memDC;
CBitmap* pOldBitmap, bitmap;


memDC.CreateCompatibleDC(&dc);
CRect rect;
this->GetClientRect(&rect);

bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());


pOldBitmap = memDC.SelectObject(&bitmap);


memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

// �ӽ� ����(memDC)�� �׸��� ������ ����.
// ...
while (i < this->notePad->GetLength()) {
	menDC.TextOut(0 + tm.tmAveCharWidth / 4 - (this->scrollController->GetHPosition()),
		(i * (tm.tmHeight + 5)) - (this->scrollController->GetVPosition()),
		this->notePad->GetAt(i)->GetContents().c_str());
	i++;
}
// ...

// �ӽ� ���۸� Picture Control�� �׸���.
dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

// ���� ��Ʈ������ �缳��.
memDC.SelectObject(pOldBitmap);

// ������ ���ҽ� ����.
memDC.DeleteDC();
bitmap.DeleteObject();
#endif 0;

#if 0;
CPaintDC dc(this);

CFont newFont;
newFont.CreateFontIndirect(&this->logFont);
CFont* oldFont = dc.SelectObject(&newFont);
TEXTMETRIC tm = { 0, };
dc.GetTextMetrics(&tm);
TextMetric textMetric(this);
CRect rect;
this->GetClientRect(&rect);

dc.FillSolidRect(0, 0, this->cx, this->cy, RGB(255, 255, 255));////////////
tm.tmHeight + 5;
dc.SetBkMode(TRANSPARENT);
if (this->isSelected == true) {//���ÿ��� ĥ�ϰ�
	CBrush brush;
	brush.CreateSolidBrush(RGB(184, 134, 12));
	CBrush* pOldBrush = dc.SelectObject(&brush);
	dc.PaintRgn(this->selector->GetSumRegion());
	dc.SelectObject(pOldBrush);
	brush.DeleteObject();
}
if (isSelected == false) {
	dc.SetBkMode(WHITENESS);
}
Long i = 0;
while (i < this->notePad->GetLength()) {
	dc.TextOut(0 + tm.tmAveCharWidth / 4 - (this->scrollController->GetHPosition()),
		(i * (tm.tmHeight + 5)) - (this->scrollController->GetVPosition()),
		this->notePad->GetAt(i)->GetContents().c_str());
	i++;
}
if (this->isSelected == true) {//�������Ѽ� �۾� �Ͼ�� ���ÿ��� �Ķ������� ó�����ش�.
	dc.InvertRgn(this->selector->GetSumRegion());
}
dc.SelectObject(oldFont);
newFont.DeleteObject();
#endif 0;