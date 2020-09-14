//MouseMove.cpp

#include"MouseMove.h"
#include"NotePadForm.h"
#include"TextMetric.h"
#include"SingleByteCharacter.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"Selector.h"
#include"MouseTrackTextMetric.h"

MouseMove::MouseMove(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}

MouseMove::~MouseMove() {

}

void MouseMove::OnMouseMove(UINT nFlags, CPoint point) {
	Selector* selector = this->notePadForm->GetSelector();
	MouseTrackTextMetric mouseTrackTextMetric(this->notePadForm);


	if (this->notePadForm->GetIsSelected() == false) {
		selector->SetOriginRowIndex(this->notePadForm->notePad->GetCurrent());
		selector->SetOriginColumnIndex(this->notePadForm->row->GetCurrent());
		selector->SetStartRowIndex(this->notePadForm->notePad->GetCurrent());
		selector->SetStartColumnIndex(this->notePadForm->row->GetCurrent());
		selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
		selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
	}
	else {
		selector->SetStartRowIndex(selector->GetEndRowIndex());
		selector->SetStartColumnIndex(selector->GetEndColumnIndex());
	}
	mouseTrackTextMetric.TransferMouseCoordinateToNotePadLocaitonWhenMouseMove(nFlags,point);

	selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
	selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
	this->notePadForm->SetNoNeedToAutoLineBreak(true);

}