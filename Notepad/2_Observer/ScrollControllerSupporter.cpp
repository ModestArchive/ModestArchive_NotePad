//ScrollControllerSupporter.cpp

#include"ScrollControllerSupporter.h"
#include"Glyph.h"
#include"TextMetric.h"
#include"Font.h"
#include"Selector.h"
#include"SelectModifier.h"
#include"NotePadMetric.h"

ScrollControllerSupporter::ScrollControllerSupporter(NotePadForm* notePadForm, ScrollController* scrollController) {
	this->notePadForm = notePadForm;
	this->scrollController = scrollController;
}


ScrollControllerSupporter::~ScrollControllerSupporter() {

}


void ScrollControllerSupporter::MoveHScrollForFindingContents() {
	ScrollController* scrollController = this->notePadForm->GetScrollController();
	NotePadMetric notePadMetric(this->notePadForm);
	Selector* selector = this->notePadForm->GetSelector();
	TextMetric textMetric(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	Font font(this->notePadForm);
	tm = font.CalculateFontMetric();

	bool isHScrollOn = scrollController->GetIsHScrollOn();
	if (isHScrollOn == true) {
		if (textMetric.GetX(this->notePadForm->notePad->GetAt(selector->GetOriginRowIndex()), selector->GetOriginColumnIndex()) + tm.tmAveCharWidth / 4
			< scrollController->GetHPosition()) {
			while (textMetric.GetX(this->notePadForm->notePad->GetAt(selector->GetOriginRowIndex()), selector->GetOriginColumnIndex()) + tm.tmAveCharWidth / 4
				< scrollController->GetHPosition()) {
				scrollController->MoveHScrPrevious();
			}
		}
		else if (textMetric.GetX(this->notePadForm->notePad->GetAt(selector->GetEndRowIndex()), selector->GetEndColumnIndex()) + tm.tmAveCharWidth / 4
				> this->notePadForm->GetCx() + scrollController->GetHPosition()) {
					bool stopScrolling = false;
					while (textMetric.GetX(this->notePadForm->notePad->GetAt(selector->GetEndRowIndex()), selector->GetEndColumnIndex()) + tm.tmAveCharWidth / 4
							> this->notePadForm->GetCx() + scrollController->GetHPosition() && stopScrolling==false) {
									scrollController->MoveHScrNext();
									if (this->notePadForm->GetScrollLimit(SB_HORZ)==this->scrollController->GetHPosition()) {
										stopScrolling = true;
									}
									else if (textMetric.GetX(this->notePadForm->notePad->GetAt(selector->GetOriginRowIndex()), selector->GetOriginColumnIndex()) + tm.tmAveCharWidth / 4
											  <this->scrollController->GetHPosition()) {
												 stopScrolling = true;
												 scrollController->MoveHScrPrevious();
									     }
					}
			 }
	}
}


void ScrollControllerSupporter::MoveVScrollForFindingContents() {
	ScrollController* scrollController = this->notePadForm->GetScrollController();
	Selector* selector = this->notePadForm->GetSelector();
	TextMetric textMetric(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	Font font(this->notePadForm);
	tm = font.CalculateFontMetric();

	bool isVScrollOn = scrollController->GetIsVScrollOn();
	if (isVScrollOn == true) {
		
		if (textMetric.GetY(selector->GetEndRowIndex()) + tm.tmHeight + 5 > this->notePadForm->GetCy() + scrollController->GetVPosition()) {
			bool stopScroll = false;
			while (stopScroll==false && textMetric.GetY(selector->GetEndRowIndex()) + tm.tmHeight + 5 > this->notePadForm->GetCy() + scrollController->GetVPosition()) {
				scrollController->MoveVScrNext();
				if (textMetric.GetY(selector->GetOriginRowIndex()) + tm.tmHeight - scrollController->GetVPosition() <= tm.tmHeight) {
					scrollController->SetVPos(textMetric.GetY(selector->GetOriginRowIndex()));
					stopScroll = true;
				}
			}
		}
		else if (textMetric.GetY(selector->GetOriginRowIndex()) + tm.tmHeight - scrollController->GetVPosition() <= tm.tmHeight) {
			scrollController->SetVPos(textMetric.GetY(selector->GetOriginRowIndex()));
		}
	}
}

#if 0;
void ScrollControllerSupporter::MoveHScrolAndSelectionForMouseSelection() {
	ScrollController* scrollController = this->notePadForm->GetScrollController();
	NotePadMetric notePadMetric(this->notePadForm);
	Selector* selector = this->notePadForm->GetSelector();

	TextMetric textMetric(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	Font font(this->notePadForm);
	tm = font.CalculateFontMetric();

	bool isHScrollOn = scrollController->GetIsHScrollOn();
	if (isHScrollOn == true) {
		if (textMetric.GetX(this->notePadForm->row, selector->GetEndColumnIndex()) <= scrollController->GetHPosition()) {
			while (textMetric.GetX(this->notePadForm->row, selector->GetEndColumnIndex()) <= scrollController->GetHPosition()) {
				scrollController->MoveHScrPrevious();
			}
			Long i = 0;
			while (i<7) {
				scrollController->MoveHScrPrevious();
				i++;
			}
			if (textMetric.GetX(this->notePadForm->row, selector->GetEndColumnIndex()) < this->notePadForm->GetCx()) {
				scrollController->MoveHScrFirst();
			}
		}
		scrollController->SetHScroll();
		SelectModifier selectModifier(selector);
		selectModifier.MoveSumRegionMatchToScrollPosition(scrollController->GetHPosition(), scrollController->GetVPosition());
		selector->SetOffsetedHPosition(scrollController->GetHPosition());
		selector->SetOffsetedVPosition(scrollController->GetVPosition());
	}
}
#endif 0;

void ScrollControllerSupporter::MoveHScrollToCurrent() {
	ScrollController* scrollController = this->notePadForm->GetScrollController();
	NotePadMetric notePadMetric(this->notePadForm);

	TextMetric textMetric(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	Font font(this->notePadForm);
	tm = font.CalculateFontMetric();

	bool isHScrollOn = scrollController->GetIsHScrollOn();
	if (isHScrollOn == true) {
		if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) + tm.tmAveCharWidth / 4
			< scrollController->GetHPosition()) {//삭제할때이고, 스크롤영역보다 짧아서 안보이는상황

			while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) + tm.tmAveCharWidth / 4
				< scrollController->GetHPosition()) {
				     scrollController->MoveHScrPrevious();
			}
			Long k = 0;
			while (k<7) {
				scrollController->MoveHScrPrevious();
				k++;
			}
		}
		else if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) + tm.tmAveCharWidth / 4
				> this->notePadForm->GetCx() + scrollController->GetHPosition()) {//글자를 더할때이고, 스크롤+클라이언트영역보다 길어서 안보이는상황

					while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) + tm.tmAveCharWidth / 4
							> this->notePadForm->GetCx() + scrollController->GetHPosition()) {
								  scrollController->MoveHScrNext();
					}
					if (notePadMetric.GetLongestXRowIndex() == this->notePadForm->notePad->GetCurrent() &&
						this->notePadForm->row->GetCurrent()==this->notePadForm->row->GetLength()) {
						scrollController->SetHPos(this->notePadForm->GetScrollLimit(SB_HORZ));
					}
					else {
						Long k = 0;
						while (k < 7) {
							scrollController->MoveHScrNext();
							k++;
						}
					}
			 }
		else {//양옆범위를 안넘어갈때상황을 정리하면된다.
			if (notePadMetric.GetLongestXRowIndex() == this->notePadForm->notePad->GetCurrent()) {
				if (this->notePadForm->row->GetCurrent()==this->notePadForm->row->GetLength()) {
					scrollController->SetHPos(this->notePadForm->GetScrollLimit(SB_HORZ));
				}
			}
		}
		scrollController->SetHScroll();
	}
}


void ScrollControllerSupporter::MoveVScrollToCurrent(){
	ScrollController* scrollController = this->notePadForm->GetScrollController();

	TextMetric textMetric(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	Font font(this->notePadForm);
	tm = font.CalculateFontMetric();

	bool isVScrollOn = scrollController->GetIsVScrollOn();
	if (isVScrollOn == true) {
		if (textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight+5 > this->notePadForm->GetCy() + scrollController->GetVPosition()) {

			while (textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight + 5> this->notePadForm->GetCy() + scrollController->GetVPosition()) {
				if (this->notePadForm->notePad->GetCurrent() == this->notePadForm->notePad->GetLength() - 1) {
					scrollController->SetVPos(this->notePadForm->GetScrollLimit(SB_VERT));
				}
				else {
					scrollController->MoveVScrNext();
				}
			}
		}
		else if (this->notePadForm->notePad->GetCurrent() != this->notePadForm->notePad->GetLength()-1 &&
			     textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight-scrollController->GetVPosition()<=tm.tmHeight) {

			scrollController->SetVPos(textMetric.GetY(this->notePadForm->notePad->GetCurrent()));
			
		}
		else {
			if (this->notePadForm->GetCy() + scrollController->GetVPosition() - textMetric.GetY(this->notePadForm->notePad->GetLength()) >=tm.tmHeight + 5) {
				while (this->notePadForm->GetCy() + scrollController->GetVPosition() - textMetric.GetY(this->notePadForm->notePad->GetLength()) >=tm.tmHeight + 5) {
					scrollController->MoveVScrPrevious();
				}
			}
		}
		scrollController->SetVScroll();
	}
}