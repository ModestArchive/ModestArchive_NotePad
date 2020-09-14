//HRightCode.cpp

#include"HRightCode.h"
#include"ScrollController.h"
#include"Font.h"
#include"TextMetric.h"
#include"NotePadMetric.h"
#include"Glyph.h"
#include"SingleByteCharacter.h"

HRightCode::HRightCode(NotePadForm* notePadForm): HScrollCodeAction(notePadForm) {

}

HRightCode::~HRightCode() {

}

void HRightCode::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {

	this->notePadForm->GetScrollController()->MoveHScrLast();
	this->notePadForm->SetScrollPos(SB_HORZ, this->notePadForm->GetScrollController()->GetHPosition(), TRUE);
#if 0;
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);

	if (this->notePadForm->GetScrollController()->GetHPosition() >
		textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent())) {

		if (notePadMetric.GetClientLongestX() == textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength())) {
			//현재 줄이 클라이언트영역 내 에서 가장 긴줄이면
			while (this->notePadForm->GetScrollController()->GetHPosition() >
				textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) &&
				this->notePadForm->row->GetCurrent() < this->notePadForm->row->GetLength()) {

				this->notePadForm->row->Next();
				while (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())) &&
					((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())))->GetSingleByteContent() == '\t') {
					this->notePadForm->row->Next();
				}
			}


		}
		else {
			//현재 줄이 클라이언트영역 내 에서 가장 긴줄이 아닐때 
			Long clientLongestXRowIndex = notePadMetric.GetClientLongestXRowIndex();
			this->notePadForm->row = this->notePadForm->notePad->GetAt(clientLongestXRowIndex);
			while (this->notePadForm->notePad->GetCurrent() > clientLongestXRowIndex) {
				this->notePadForm->notePad->Previous();
			}
			while (this->notePadForm->notePad->GetCurrent() < clientLongestXRowIndex) {
				this->notePadForm->notePad->Next();
			}
			this->notePadForm->row->First();
			while (this->notePadForm->GetScrollController()->GetHPosition() >
				textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) &&
				this->notePadForm->row->GetCurrent() < this->notePadForm->row->GetLength()) {

				this->notePadForm->row->Next();
			}

		}

		if (this->notePadForm->GetScrollController()->GetHPosition() >
			textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent())) {
			//클라이언트 영역보다 스크롤길이가 더 길어질때 제일긴줄 찾아감.

			Long longestXRowIndex = notePadMetric.GetLongestXRowIndex();
			this->notePadForm->row = this->notePadForm->notePad->GetAt(longestXRowIndex);
			while (this->notePadForm->notePad->GetCurrent() > longestXRowIndex) {
				this->notePadForm->notePad->Previous();
			}
			while (this->notePadForm->notePad->GetCurrent() < longestXRowIndex) {
				this->notePadForm->notePad->Next();
			}
			this->notePadForm->row->First();
			while (this->notePadForm->GetScrollController()->GetHPosition() >
				textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) &&
				this->notePadForm->row->GetCurrent() < this->notePadForm->row->GetLength()) {

				this->notePadForm->row->Next();
			}

			this->notePadForm->GetScrollController()->SetVPos(textMetric.GetY(longestXRowIndex));
		}

	}
#endif 0;
}