//ScrollController.cpp

#include"ScrollController.h"
#include"HScrollCodeActionFactory.h"
#include"VScrollCodeActionFactory.h"
#include"VScrollCodeAction.h"
#include"HScrollCodeAction.h"
#include"Scroll.h"
#include"Font.h"
#include"Glyph.h"
#include"NotePadMetric.h"
#include"TextMetric.h"
#include"SelectModifier.h"
#include"NotePadFormControlWnd.h"
#include"NotePadMetric.h"
#include"ContentsFinder.h"
#include"MatchIndexCollector.h"
#include"ScrollControllerSupporter.h"

ScrollController::ScrollController(Scroll* scroll, NotePadForm* notePadForm) {

	this->scroll = scroll;
	this->notePadForm = notePadForm;
	this->hPosition = 0;
	this->vPosition = 0;
	this->hMaximum = 0;
	this->vMaximum = 0;
	this->isHScrollOn = false;
	this->isVScrollOn=false;

	((Subject*)(this->notePadForm))->Attach(this);
}


ScrollController::~ScrollController() {
	((Subject*)(this->notePadForm))->Detach(this);
}


void ScrollController::SetHScroll() {

	SCROLLINFO horizontalScrollInfo = { 0, };//가로스크롤 생성먼저
	//CDC* dc = this->notePadForm->GetDC();
	LOGFONT* logFont = 0;//구조체 초기화

	NotePadMetric notePadMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	horizontalScrollInfo.cbSize = sizeof(horizontalScrollInfo);
	horizontalScrollInfo.fMask = SIF_ALL;
	horizontalScrollInfo.nMin = 0;
	this->hMaximum = notePadMetric.GetLongestX()+tm.tmAveCharWidth/4;
	horizontalScrollInfo.nMax = this->hMaximum;
	horizontalScrollInfo.nPage = (this->scroll->GetScrollWidth()/ (tm.tmAveCharWidth/2)) * (tm.tmAveCharWidth/2);
	horizontalScrollInfo.nPos = this->hPosition;
	this->notePadForm->SetScrollInfo(SB_HORZ, &horizontalScrollInfo, TRUE);
	this->notePadForm->ShowScrollBar(SB_HORZ, TRUE);
}

void ScrollController::SetVScroll() {

	SCROLLINFO verticalScrollInfo = { 0, };
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	verticalScrollInfo.cbSize = sizeof(verticalScrollInfo);
	verticalScrollInfo.fMask = SIF_ALL;
	verticalScrollInfo.nMin = 0;
	this->vMaximum = textMetric.GetY(this->notePadForm->notePad->GetLength());
	verticalScrollInfo.nMax = this->vMaximum;
	verticalScrollInfo.nPage = (this->scroll->GetScrollHeight() / (tm.tmHeight+5))* (tm.tmHeight + 5);
	verticalScrollInfo.nPos = this->vPosition;

	this->notePadForm->SetScrollInfo(SB_VERT, &verticalScrollInfo, TRUE);
	this->notePadForm->ShowScrollBar(SB_VERT, TRUE);
}

void ScrollController::SetIsHScrollOn(bool isHScrollOn) {
	this->isHScrollOn = isHScrollOn;
}


void ScrollController::SetHPos(Long hPosition) {
	this->hPosition = hPosition;
}

void ScrollController::SetVPos(Long vPosition) {
	this->vPosition = vPosition;
}

void ScrollController::MoveHScrFirst() {
	
	this->hPosition=0;
}

void ScrollController::MoveHScrLast() {

	this->hPosition = this->notePadForm->GetScrollLimit(SB_HORZ);
}

void ScrollController::MoveHScrNext() {

	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	if (this->hPosition < this->notePadForm->GetScrollLimit(SB_HORZ)) {

		if (this->notePadForm->GetScrollLimit(SB_HORZ) -this->hPosition < tm.tmAveCharWidth) {
			this->hPosition = this->notePadForm->GetScrollLimit(SB_HORZ);
		}
		else {
			this->hPosition += tm.tmAveCharWidth;
		}
	}
}


void ScrollController::MoveHScrPrevious() {

	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	if (this->hPosition > 0) {//일일이 구해줘야 하는지 뻑나면보기
		if (this->hPosition<tm.tmAveCharWidth) {
			this->hPosition = 0;
		}
		else {
			this->hPosition -= tm.tmAveCharWidth;
		}
	}
}


void ScrollController::MoveHScrPageLeft() {
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	if (this->hPosition > 0) {
		this->hPosition = max(0, this->hPosition - (this->scroll->GetScrollWidth() / tm.tmAveCharWidth)*(tm.tmAveCharWidth));
	}
}


void ScrollController::MoveHScrPageRight() {
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	if (this->hPosition< this->notePadForm->GetScrollLimit(SB_HORZ)) {

		this->hPosition = min(this->notePadForm->GetScrollLimit(SB_HORZ),
							  this->hPosition + (this->scroll->GetScrollWidth() / tm.tmAveCharWidth)*(tm.tmAveCharWidth));
	}
}


void ScrollController::MoveHScrThumb() {
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	SCROLLINFO si = { 0, };
	this->notePadForm->GetScrollInfo(SB_HORZ, &si, SIF_TRACKPOS);

	this->hPosition = si.nTrackPos;
}

void ScrollController::MoveVScrFirst() {
	this->vPosition =0;
}

void ScrollController::MoveVScrLast() {
	this->vPosition = this->notePadForm->GetScrollLimit(SB_VERT);
}

void ScrollController::MoveVScrNext() {
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	if (this->vMaximum-(this->scroll->GetScrollHeight() + this->vPosition) < tm.tmHeight+5) {
		this->vPosition =this->notePadForm->GetScrollLimit(SB_VERT);
	}
	else {
		if (this->vMaximum - (this->scroll->GetScrollHeight() + this->vPosition) >=2*( tm.tmHeight + 5)) {//두줄이상여유있을때는 앞으로 가는데 한줄만 남았으면 그냥 끝까지 가는걸로 한다 이상하게 짜투리가 항상남아서 
			this->vPosition += (tm.tmHeight + 5);
		}
		else {
			this->vPosition = this->notePadForm->GetScrollLimit(SB_VERT);
		}
	}
}

void ScrollController::MoveVScrPrevious() {

	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	if (this->vPosition> 0) {
		if (this->vPosition< tm.tmHeight + 5) {
			this->vPosition=0;
		}
		else {
			if (this->vPosition>2*(tm.tmHeight+5)) {
				this->vPosition -= tm.tmHeight + 5;
			}
			else {
				this->vPosition = 0;
			}
		}
	}
}

void ScrollController::MoveVScrPageUp() {
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	
	if (this->vPosition > 0) {
		Long vPosition = max(0,
							this->vPosition - ((this->scroll->GetScrollHeight() / (tm.tmHeight + 5)) * (tm.tmHeight + 5)));
		this->vPosition= vPosition;
		
	}
}

void ScrollController::MoveVScrPageDown() {
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	if (this->scroll->GetScrollHeight() + this->vPosition < this->vMaximum) {
		Long vPosition = min(this->notePadForm->GetScrollLimit(SB_VERT),
							 this->vPosition + (this->scroll->GetScrollHeight() / (tm.tmHeight + 5)) * (tm.tmHeight + 5));
		this->vPosition= vPosition;
	}
}

void ScrollController::MoveVScrThumb() {
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	SCROLLINFO si = { 0, };
	this->notePadForm->GetScrollInfo(SB_VERT, &si, SIF_TRACKPOS);
	
	this->vPosition=si.nTrackPos;
}


void ScrollController::RemoveHScroll() {
	this->notePadForm->ShowScrollBar(SB_HORZ, FALSE);

}


void ScrollController::RemoveVScroll() {
	this->notePadForm->ShowScrollBar(SB_VERT, FALSE);
}


void ScrollController::Update(Subject* theChangedSubject) {
	
	if (this->notePadForm == theChangedSubject && this->notePadForm->GetNotePadFormControlWnd()->GetNoNeedToScroll()==false) {
		ScrollControllerSupporter scrollControllerSupporter(this->notePadForm, this);
		TextMetric textMetric(this->notePadForm);
		NotePadMetric notePadMetric(this->notePadForm);
		Font font(this->notePadForm);
		TEXTMETRIC tm = { 0, };
		tm = font.CalculateFontMetric();
		
		if (this->notePadForm->GetIsAutoLineBreak() == false) {

			if (this->notePadForm->GetIsOnSizing() == true || this->notePadForm->GetIsFontSizing()==true) {
				if (notePadMetric.GetLongestX() + tm.tmAveCharWidth / 4 > this->scroll->GetScrollWidth() - tm.tmAveCharWidth / 2) {
					this->SetHScroll();
					if (notePadMetric.GetLongestX() + tm.tmAveCharWidth / 4 < this->scroll->GetScrollWidth() + this->hPosition) {
						
						this->hPosition=this->notePadForm->GetScrollLimit(SB_HORZ);
						this->SetHScroll();
					}
					if (this->notePadForm->GetIsFontSizing()==true) {
						scrollControllerSupporter.MoveHScrollToCurrent();
					}
					this->isHScrollOn = true;
				}
				else {
					this->hPosition = 0;
					this->RemoveHScroll();
					this->isHScrollOn = false;
				}
				if (textMetric.GetY(this->notePadForm->notePad->GetLength()) > this->scroll->GetScrollHeight()) {
					
					this->SetVScroll();
					while (textMetric.GetY(this->notePadForm->notePad->GetLength()) + tm.tmHeight + 5 < this->scroll->GetScrollHeight() + this->vPosition) {
						this->MoveVScrNext();
					}
					this->SetVScroll();
					if (this->notePadForm->GetIsFontSizing() == true) {
						scrollControllerSupporter.MoveVScrollToCurrent();
					}
					this->isVScrollOn = true;
				}
				else {
					this->vPosition = 0;
					this->RemoveVScroll();
					this->isVScrollOn = false;
				}
			}
			else {
				if (notePadMetric.GetLongestX() + tm.tmAveCharWidth / 4 > this->scroll->GetScrollWidth() - tm.tmAveCharWidth / 2) {
					this->SetHScroll();
					this->isHScrollOn = true;

					if (this->notePadForm->GetIsFindingContents() == true) {
						scrollControllerSupporter.MoveHScrollForFindingContents();
					}
					else if (this->notePadForm->GetIsScrolling() == false && this->notePadForm->GetIsMouseSelecting() == false) {

					    scrollControllerSupporter.MoveHScrollToCurrent();
					}
				}
				else {
					this->hPosition = 0;
					this->RemoveHScroll();
					this->isHScrollOn = false;
				}
				if (textMetric.GetY(this->notePadForm->notePad->GetLength())> this->scroll->GetScrollHeight()) {
					this->SetVScroll();
					this->isVScrollOn = true;

					if (this->notePadForm->GetIsFindingContents() == true) {								
						scrollControllerSupporter.MoveVScrollForFindingContents();
					}
					else if (this->notePadForm->GetIsScrolling() == false && this->notePadForm->GetIsMouseSelecting() == false) {

						scrollControllerSupporter.MoveVScrollToCurrent();
					}
					
				}
				else {
					this->vPosition = 0;
					this->RemoveVScroll();
					this->isVScrollOn = false;
				}
			}
		}
		else {
			this->hPosition = 0;
			this->RemoveHScroll();
			this->isHScrollOn = false;
			if (textMetric.GetY(this->notePadForm->notePad->GetLength()) > this->scroll->GetScrollHeight()) {
				if (this->notePadForm->GetIsOnSizing()==true) {
					this->SetVScroll();
					while (textMetric.GetY(this->notePadForm->notePad->GetLength())+tm.tmHeight+5 <this->scroll->GetScrollHeight()+this->vPosition ) {
						this-> MoveVScrNext();
					}
					this->SetVScroll();
					this->isVScrollOn = true;
					
					if (this->notePadForm->GetIsFontSizing() == true) {
						scrollControllerSupporter.MoveVScrollToCurrent();
					}
				}
				else {
					this->SetVScroll();
					this->isVScrollOn = true;
					if (this->notePadForm->GetIsFindingContents() == true) {
						
						scrollControllerSupporter.MoveVScrollForFindingContents();
					}
					else if (this->notePadForm->GetIsScrolling() == false && this->notePadForm->GetIsMouseSelecting() == false) {
								
						scrollControllerSupporter.MoveVScrollToCurrent();
					}
				}
			}
			else {
				this->vPosition = 0;
				this->RemoveVScroll();
				this->isVScrollOn = false;
			}
		}
	}
}