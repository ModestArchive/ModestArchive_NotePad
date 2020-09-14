//CaretController.cpp

#include"CaretController.h"
#include"Row.h"
#include"TextMetric.h"
#include"ScrollController.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//持失切,社瑚切
CaretController::CaretController() {
	this->notePadForm = 0;
	this->caret = 0;
	this->caretCordinate = {0,};
}


CaretController::CaretController(NotePadForm* notePadForm) {
	
	this->notePadForm = notePadForm;
	this->caret = 0;
	this->caretCordinate = { 0, };
	
	((Subject*)(this->notePadForm))->Attach(this);

}


CaretController::CaretController(NotePadForm* notePadForm,Caret* caret) {

	this->notePadForm = notePadForm;
	
	this->caret = caret;
	this->caretCordinate = { 0, };
	((Subject*)(this->notePadForm))->Attach(this);
	
}


CaretController::~CaretController() {
	((Subject*)(this->notePadForm))->Detach(this);
}

//五社球
void CaretController::Update(Subject* theChangedSubject) {

	if (theChangedSubject == this->notePadForm) {
		
		Font font(this->notePadForm);
		Caret caret(font.CalculateFontMetric());
		this->caret = &caret;
		this->CalculateCaretCordinate();
		this->SetCaret();
	}
}


void CaretController::CalculateCaretCordinate() {

	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm=font.CalculateFontMetric();
	Long width = 0;

	if (this->notePadForm->GetIsComposition() == true) {
		width= textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent());
		this->caretCordinate.cx = width - this->caret->GetCompositionCaretWidth()+tm.tmAveCharWidth/4 - this->notePadForm->GetScrollController()->GetHPosition();
	}
	else {
		width = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent());
		this->caretCordinate.cx = width + tm.tmAveCharWidth / 4-this->notePadForm->GetScrollController()->GetHPosition();
	}
	
	Long height = textMetric.GetY(this->notePadForm->notePad->GetCurrent());
	this->caretCordinate.cy = height - this->notePadForm->GetScrollController()->GetVPosition();
}

void CaretController::SetCaret() {
	
	this->notePadForm->HideCaret();
	if (this->notePadForm->GetIsComposition() == true) {
		this->notePadForm->CreateSolidCaret(this->caret->GetCompositionCaretWidth(), this->caret->GetCaretHeight());
	}
	else {
		this->notePadForm->CreateSolidCaret(this->caret->GetNotCompositionCaretWidth(), this->caret->GetCaretHeight());
	}
	CPoint point(this->caretCordinate.cx, this->caretCordinate.cy);
	
	this->notePadForm->SetCaretPos(point);
	this->notePadForm->ShowCaret();
}


void CaretController::KillCaret() {
	this->notePadForm->HideCaret();
	::DestroyCaret();
}

