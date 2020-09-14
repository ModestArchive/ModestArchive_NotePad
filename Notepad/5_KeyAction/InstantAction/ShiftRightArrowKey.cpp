//ShiftRightArrowKey.cpp

#include"ShiftRightArrowKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"KeyAction.h"
#include"Selector.h"
#include"TextMetric.h"
#include"RightArrowKey.h"


ShiftRightArrowKey::ShiftRightArrowKey() {

}


ShiftRightArrowKey::ShiftRightArrowKey(NotePadForm* notePadForm) :KeyAction(notePadForm) {


}


ShiftRightArrowKey::~ShiftRightArrowKey() {


}


void ShiftRightArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Selector* selector = this->notePadForm->GetSelector();
	KeyAction* rightArrowKey = new RightArrowKey(this->notePadForm);
	

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

	rightArrowKey->OnKeyDown(nChar, nRepCnt, nFlags);
	if (rightArrowKey != 0) {
		delete rightArrowKey;
	}

	selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
	selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
}