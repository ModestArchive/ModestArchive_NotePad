//ShiftUpArrowKey.cpp

#include"ShiftUpArrowKey.h"
#include"Glyph.h"
#include"KeyAction.h"
#include"Selector.h"
#include"TextMetric.h"
#include"UpArrowKey.h"


ShiftUpArrowKey::ShiftUpArrowKey() {

}

ShiftUpArrowKey::ShiftUpArrowKey(NotePadForm* notePadForm) :KeyAction(notePadForm) {


}

ShiftUpArrowKey::~ShiftUpArrowKey() {


}

void ShiftUpArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Selector* selector = this->notePadForm->GetSelector();
	KeyAction* upArrowKey = new UpArrowKey(this->notePadForm);


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

	upArrowKey->OnKeyDown(nChar, nRepCnt, nFlags);
	if (upArrowKey != 0) {
		delete upArrowKey;
	}

	selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
	selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
}