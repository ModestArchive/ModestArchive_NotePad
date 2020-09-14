//ShiftEndKey.cpp

#include"ShiftEndKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"KeyAction.h"
#include"Selector.h"
#include"TextMetric.h"
#include"EndKey.h"

ShiftEndKey::ShiftEndKey() {

}

ShiftEndKey::ShiftEndKey(NotePadForm* notePadForm) :KeyAction(notePadForm) {


}

ShiftEndKey::~ShiftEndKey() {


}

void ShiftEndKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Selector* selector = this->notePadForm->GetSelector();
	KeyAction* endKey = new EndKey(this->notePadForm);

	
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

	endKey->OnKeyDown(nChar, nRepCnt, nFlags);
	if (endKey != 0) {
		delete endKey;
	}

	selector->SetEndRowIndex(this->notePadForm->notePad->GetCurrent());
	selector->SetEndColumnIndex(this->notePadForm->row->GetCurrent());
}