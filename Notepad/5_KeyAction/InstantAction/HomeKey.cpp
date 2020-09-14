//HomeKey.cpp

#include"HomeKey.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"DummyRow.h"


HomeKey::HomeKey() {

}

HomeKey::HomeKey(NotePadForm* notePadForm):KeyAction(notePadForm) {


}

HomeKey::~HomeKey() {


}

void HomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	
	if (this->notePadForm->GetIsAutoLineBreak() == true) {
		if (this->notePadForm->row->GetCurrent() > 0) {
			this->notePadForm->row->First();
		}
		else {
			if (this->notePadForm->notePad->GetCurrent() >0 && 
				dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent()))) {
				this->notePadForm->notePad->Previous();
				this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
				this->notePadForm->row->First();	
			}
		}
	}
	else {
		this->notePadForm->row->First();
	}
	this->notePadForm->SetNoNeedToAutoLineBreak(true);

#if 0;
	this->notePadForm->GetScrollController()->MoveHScrFirst();
	this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
#endif 0;
}