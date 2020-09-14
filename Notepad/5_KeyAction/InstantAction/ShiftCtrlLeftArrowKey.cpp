//ShiftCtrlLeftArrowKey.cpp

#include"ShiftCtrlLeftArrowKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"KeyAction.h"
#include"Selector.h"
#include"TextMetric.h"
#include"CtrlLeftArrowKey.h"


ShiftCtrlLeftArrowKey::ShiftCtrlLeftArrowKey() {

}

ShiftCtrlLeftArrowKey::ShiftCtrlLeftArrowKey(NotePadForm* notePadForm) :KeyAction(notePadForm) {


}

ShiftCtrlLeftArrowKey::~ShiftCtrlLeftArrowKey() {


}

void ShiftCtrlLeftArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Selector* selector = this->notePadForm->GetSelector();
	KeyAction* ctrlLeftArrowKey = new CtrlLeftArrowKey(this->notePadForm);

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

	ctrlLeftArrowKey->OnKeyDown(nChar, nRepCnt, nFlags);
	if (ctrlLeftArrowKey != 0) {
		delete ctrlLeftArrowKey;
	}

	selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
	selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
}