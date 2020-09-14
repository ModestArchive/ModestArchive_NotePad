//ShiftCtrlRightArrowKey.cpp

#include"ShiftCtrlRightArrowKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"KeyAction.h"
#include"Selector.h"
#include"TextMetric.h"
#include"CtrlRightArrowKey.h"


ShiftCtrlRightArrowKey::ShiftCtrlRightArrowKey() {

}

ShiftCtrlRightArrowKey::ShiftCtrlRightArrowKey(NotePadForm* notePadForm) :KeyAction(notePadForm) {


}

ShiftCtrlRightArrowKey::~ShiftCtrlRightArrowKey() {


}

void ShiftCtrlRightArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Selector* selector = this->notePadForm->GetSelector();
	KeyAction* ctrlRightArrowKey = new CtrlRightArrowKey(this->notePadForm);

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

	ctrlRightArrowKey->OnKeyDown(nChar, nRepCnt, nFlags);
	if (ctrlRightArrowKey != 0) {
		delete ctrlRightArrowKey;
	}

	selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
	selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
}