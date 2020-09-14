//ShiftDownArrowKey.cpp

#include"ShiftDownArrowKey.h"
#include"Glyph.h"
#include"KeyAction.h"
#include"Selector.h"
#include"TextMetric.h"
#include"DownArrowKey.h"


ShiftDownArrowKey::ShiftDownArrowKey() {

}

ShiftDownArrowKey::ShiftDownArrowKey(NotePadForm* notePadForm) :KeyAction(notePadForm) {


}

ShiftDownArrowKey::~ShiftDownArrowKey() {


}

void ShiftDownArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Selector* selector = this->notePadForm->GetSelector();
	KeyAction* downArrowKey = new DownArrowKey(this->notePadForm);
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

	downArrowKey->OnKeyDown(nChar, nRepCnt, nFlags);
	if (downArrowKey != 0) {
		delete downArrowKey;
	}

	selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
	selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
}