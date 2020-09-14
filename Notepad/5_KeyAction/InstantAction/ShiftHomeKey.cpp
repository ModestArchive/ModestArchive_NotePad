//ShiftHomeKey.cpp

#include"ShiftHomeKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"KeyAction.h"
#include"Selector.h"
#include"TextMetric.h"
#include"HomeKey.h"

ShiftHomeKey::ShiftHomeKey() {

}

ShiftHomeKey::ShiftHomeKey(NotePadForm* notePadForm) :KeyAction(notePadForm) {


}

ShiftHomeKey::~ShiftHomeKey() {


}

void ShiftHomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Selector* selector = this->notePadForm->GetSelector();
	KeyAction* homeKey = new HomeKey(this->notePadForm);

	

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

	homeKey->OnKeyDown(nChar, nRepCnt, nFlags);
	if (homeKey != 0) {
		delete homeKey;
	}

	selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
	selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
}