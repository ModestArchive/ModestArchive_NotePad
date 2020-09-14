//HThumbTrackCode.cpp

#include"HThumbTrackCode.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"Font.h"
#include"TextMetric.h"
#include"NotePadMetric.h"
#include"Glyph.h"
#include"SingleByteCharacter.h"

HThumbTrackCode::HThumbTrackCode(NotePadForm* notePadForm) :HScrollCodeAction(notePadForm) {

}

HThumbTrackCode::~HThumbTrackCode() {

}

void HThumbTrackCode::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {

	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	this->notePadForm->GetScrollController()->MoveHScrThumb();
	this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
#if 0;
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);

	if (this->notePadForm->GetScrollController()->GetHPosition() >
		textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent())) {

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
	}
	else if (this->notePadForm->GetScrollController()->GetHPosition() + this->notePadForm->GetCx() - tm.tmAveCharWidth / 2 <=
			textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent())) {

			while (this->notePadForm->GetScrollController()->GetHPosition() + this->notePadForm->GetCx() - tm.tmAveCharWidth / 2 <=
				textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent())) {
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