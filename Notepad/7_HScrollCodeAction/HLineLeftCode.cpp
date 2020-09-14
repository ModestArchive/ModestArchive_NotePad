//HLineLeftCode.cpp

#include"HLineLeftCode.h"
#include"ScrollController.h"
#include"CaretController.h"
#include"TextMetric.h"
#include"Font.h"
#include"Glyph.h"
#include"SingleByteCharacter.h"

HLineLeftCode::HLineLeftCode(NotePadForm* notePadForm) :HScrollCodeAction(notePadForm) {

}

HLineLeftCode::~HLineLeftCode() {

}

void HLineLeftCode::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	this->notePadForm->GetScrollController()->MoveHScrPrevious();
	this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);

	TextMetric textMetric(this->notePadForm);
#if 0;
	
	if (this->notePadForm->GetScrollController()->GetHPosition()+this->notePadForm->GetCx()-tm.tmAveCharWidth/2 <=textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent())) {
		while (this->notePadForm->GetScrollController()->GetHPosition() + this->notePadForm->GetCx() - tm.tmAveCharWidth / 2 <= textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent())) {
			this->notePadForm->row->Previous();
		}
		if (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())) &&
			((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())))->GetSingleByteContent() == '\t') {
			while (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())) &&
				((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())))->GetSingleByteContent() == '\t') {
				this->notePadForm->row->Previous();
			}
			if (this->notePadForm->row->GetCurrent() + 1 < this->notePadForm->row->GetLength() && dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() + 1)) &&
				((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() + 1)))->GetSingleByteContent() == '\t') {
				this->notePadForm->row->Next();
			}
		}
	}
#endif 0;
}