//ShiftLeftArrowKey.cpp

#include"ShiftLeftArrowKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"KeyAction.h"
#include"Selector.h"
#include"TextMetric.h"
#include"LeftArrowKey.h"

ShiftLeftArrowKey::ShiftLeftArrowKey() {

}

ShiftLeftArrowKey::ShiftLeftArrowKey(NotePadForm* notePadForm) :KeyAction(notePadForm) {


}

ShiftLeftArrowKey::~ShiftLeftArrowKey() {


}

void ShiftLeftArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Selector* selector = this->notePadForm->GetSelector();
	KeyAction* leftArrowKey = new LeftArrowKey(this->notePadForm);


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

	leftArrowKey->OnKeyDown(nChar, nRepCnt, nFlags);
	if (leftArrowKey != 0) {
		delete leftArrowKey;
	}

	selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
	selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
}