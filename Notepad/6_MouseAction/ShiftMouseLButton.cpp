//ShiftMouseLButton.cpp
#include"ShiftMouseLButton.h"
#include"MouseTrackTextMetric.h"
#include"NotePadForm.h"
#include"TextMetric.h"
#include"SingleByteCharacter.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"Selector.h"
#include"MouseTrackTextMetric.h"

ShiftMouseLButton::ShiftMouseLButton(NotePadForm* notePadForm) :MouseLButtonAction(notePadForm){

}

ShiftMouseLButton::~ShiftMouseLButton() {

}

void ShiftMouseLButton::OnLButtonDown(UINT nFlags, CPoint point) {
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
	mouseTrackTextMetric.TransferMouseCoordinateToNotePadLocation(nFlags, point);

	selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
	selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
	this->notePadForm->SetNoNeedToAutoLineBreak(true);
}