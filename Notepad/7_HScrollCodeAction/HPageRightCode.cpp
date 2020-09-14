//HPageRightCode.cpp
#include"HPageRightCode.h"
#include"ScrollController.h"
#include"NotePadForm.h"
#include"Font.h"
#include"TextMetric.h"
#include"NotePadMetric.h"
#include"Glyph.h"
#include"SingleByteCharacter.h"

HPageRightCode::HPageRightCode(NotePadForm* notePadForm) :HScrollCodeAction(notePadForm) {

}


HPageRightCode::~HPageRightCode() {

}


void HPageRightCode::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {

	this->notePadForm->GetScrollController()->MoveHScrPageRight();
	this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
#if 0;
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);

	while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) <=
		this->notePadForm->GetScrollController()->GetHPosition() &&
		this->notePadForm->row->GetCurrent() < this->notePadForm->row->GetLength()) {

		this->notePadForm->row->Next();
		while (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())) &&
			((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())))->GetSingleByteContent() == '\t') {
			this->notePadForm->row->Next();
		}
	}

	Long clientLongestXRowIndex = notePadMetric.GetClientLongestXRowIndex();

	if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) <=
		this->notePadForm->GetScrollController()->GetHPosition() &&
		this->notePadForm->notePad->GetCurrent() != clientLongestXRowIndex) {

		notePadMetric.MoveClientLongestXRow(clientLongestXRowIndex, this->notePadForm->GetScrollController()->GetVPosition());
		notePadMetric.MoveColumnOverHPos(this->notePadForm->GetScrollController()->GetHPosition());
	}

	if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) <=
		this->notePadForm->GetScrollController()->GetHPosition()) {

		Long longestXRowIndex = notePadMetric.GetLongestXRowIndex();
		notePadMetric.MoveLongestXRow(longestXRowIndex, this->notePadForm->GetScrollController()->GetVPosition());
		notePadMetric.MoveColumnOverHPos(this->notePadForm->GetScrollController()->GetHPosition());
	}
#endif 0;
}
