//PageDownKey.cpp

#include"PageDownKey.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"Glyph.h"

PageDownKey::PageDownKey() {


}


PageDownKey::PageDownKey(NotePadForm* notePadForm) : KeyAction(notePadForm) {


}

PageDownKey::~PageDownKey() {


}

void PageDownKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->notePadForm->GetScrollController()->MoveVScrPageDown();
	this->notePadForm->SetScrollPos(SB_VERT, this->notePadForm->GetScrollController()->GetVPosition(), TRUE);

	TextMetric textMetric(this->notePadForm);
	while (this->notePadForm->GetScrollController()->GetVPosition() >
		textMetric.GetY(this->notePadForm->notePad->GetCurrent())) {
		this->notePadForm->GetScrollController()->MoveHScrFirst();
		this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
		this->notePadForm->notePad->Next();
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->First();
		textMetric.GetY(this->notePadForm->notePad->GetCurrent() + 1);
	}
}