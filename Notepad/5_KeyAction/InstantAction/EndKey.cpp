//EndKey.cpp

#include"EndKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"DummyRow.h"

EndKey::EndKey() {

}

EndKey::EndKey(NotePadForm* notePadForm) :KeyAction(notePadForm){


}

EndKey::~EndKey() {


}

void EndKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	TextMetric textMetric(this->notePadForm);
	
	
	if (this->notePadForm->GetIsAutoLineBreak()==true) {
		if (this->notePadForm->row->GetCurrent()<this->notePadForm->row->GetLength()) {
			this->notePadForm->row->Last();
		}
		else {
			if (this->notePadForm->notePad->GetCurrent()<this->notePadForm->notePad->GetLength()-1) {
				if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent()+1))) {
					this->notePadForm->notePad->Next();
					this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
					this->notePadForm->row->Last();
				}
			}
			
		}
	}
	else {
		this->notePadForm->row->Last();
	}

#if 0;
	while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength())>=
		this->notePadForm->GetScrollController()->GetHPosition()+this->notePadForm->GetCx()) {

		this->notePadForm->GetScrollController()->MoveHScrPageRight();
	}
	
	this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(),TRUE);
#endif 0;
}