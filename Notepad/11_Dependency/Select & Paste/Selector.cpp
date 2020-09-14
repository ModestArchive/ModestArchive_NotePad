//Selector.cpp

#include"Selector.h"
#include"SelectModifier.h"
#include"Glyph.h"
#include"TextMetric.h"
#include"Font.h"
#include"ScrollController.h"



Selector::Selector(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
	this->originRowIndex = -1;
	this->originColumnIndex = -1;
	this->startRowIndex = -1;
	this->startColumnIndex = -1;
	this->endRowIndex = -1;
	this->endColumnIndex = -1;
	this->sumRegion = 0;
	this->copyOfSumRegion =0;
	this->combinedTwoRegions =0;
	this->primaryCurrentActionProcessedRegion = 0;
	this->secondaryCurrentActionProcessedRegion =0;
	
	this->offsetedHPosition = 0;
	this->offsetedVPosition = 0;
	this->selectedAreaLength = 0;
	this->lengthToSelectedArea = 0;
	this->isFirstContentTab = false;
	/*this->allRegion;
	::ZeroMemory(&this->allRegion, sizeof(this->allRegion));
	this->copyOfAllRegion;
	::ZeroMemory(&this->copyOfAllRegion, sizeof(this->copyOfAllRegion));
	this->combinedCurrentRegion;
	::ZeroMemory(&this->combinedCurrentRegion, sizeof(this->combinedCurrentRegion));
	this->primaryCurrentRegion;
	::ZeroMemory(&this->primaryCurrentRegion, sizeof(this->primaryCurrentRegion));
	this->secondaryCurrentRegion;
	::ZeroMemory(&this->secondaryCurrentRegion, sizeof(this->secondaryCurrentRegion));*/
}


Selector::~Selector() {
	if (this->sumRegion != 0) {
		delete this->sumRegion;
	}
	if (this->copyOfSumRegion != 0) {
		delete this->copyOfSumRegion;
	}
	if (this->combinedTwoRegions != 0) {
		delete this->combinedTwoRegions;
	}
	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	if (this->secondaryCurrentActionProcessedRegion != 0) {
		delete this->secondaryCurrentActionProcessedRegion;
	}
}


void Selector::SetRegionForHighLightNextCharWithinSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->startRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex)+ tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex)+ tm.tmAveCharWidth / 4 - hPosition;
	
	if (this->primaryCurrentActionProcessedRegion !=0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);                          
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
	/*if (this->notePadForm->GetScrollController()->GetHPosition() != 0 || this->notePadForm->GetScrollController()->GetVPosition() != 0) {
		SelectModifier selectModifier(this);
		selectModifier.MoveHighLightRegionMatchToScrollPosition(this->notePadForm->GetScrollController()->GetHPosition(),
			this->notePadForm->GetScrollController()->GetVPosition());
	    this->offsetedHPosition = this->notePadForm->GetScrollController()->GetHPosition();
		this->offsetedVPosition = this->notePadForm->GetScrollController()->GetVPosition();
	}*/
}


void Selector::SetRegionForHighLightNextCharBeyondSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	//모든 선택처리해주는 함수애 primaryregion하고 sumregion 합치기전에 sumregion 스크롤에맞게 움직여 주고 합치는 처리 다 해주기,스크롤 움직인거에 따라 선택되었으면 offset처리하고, 마우스 바깥으로 나갔을때 끝까지 움직여주는거vpos랑hpos랑 
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->endRowIndex)- vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, 0) + tm.tmAveCharWidth / 4 -hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
	
	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->secondaryCurrentActionProcessedRegion == 0) {
	//	this->secondaryCurrentActionProcessedRegion = new CRgn;
	//	this->secondaryCurrentActionProcessedRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	//this->secondaryCurrentActionProcessedRegion->CopyRgn(this->copyOfSumRegion);
	

	//if (this->combinedTwoRegions == 0) {
	//	this->combinedTwoRegions = new CRgn;
	//	this->combinedTwoRegions->CreateRectRgn(0, 0, 0, 0);
	//}
	//this->combinedTwoRegions->CombineRgn(this->primaryCurrentActionProcessedRegion, this->secondaryCurrentActionProcessedRegion, RGN_OR);
    SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	//this->sumRegion->CopyRgn(this->combinedTwoRegions);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);

}


void Selector::SetRegionForHighLightPreviousCharWithinSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->startRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightPreviousCharBeyondSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength()) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->secondaryCurrentActionProcessedRegion == 0) {
	//	this->secondaryCurrentActionProcessedRegion = new CRgn;
	//	this->secondaryCurrentActionProcessedRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	//this->secondaryCurrentActionProcessedRegion->CopyRgn(this->copyOfSumRegion);


	//if (this->combinedTwoRegions == 0) {
	//	this->combinedTwoRegions = new CRgn;
	//	this->combinedTwoRegions->CreateRectRgn(0, 0, 0, 0);
	//}
	//this->combinedTwoRegions->CombineRgn(this->primaryCurrentActionProcessedRegion, this->secondaryCurrentActionProcessedRegion, RGN_OR);
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	//this->sumRegion->CopyRgn(this->combinedTwoRegions);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightNextWordWithinSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->startRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightNextWordBeyondSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, 0) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->secondaryCurrentActionProcessedRegion == 0) {
	//	this->secondaryCurrentActionProcessedRegion = new CRgn;
	//	this->secondaryCurrentActionProcessedRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	//this->secondaryCurrentActionProcessedRegion->CopyRgn(this->copyOfSumRegion);


	//if (this->combinedTwoRegions == 0) {
	//	this->combinedTwoRegions = new CRgn;
	//	this->combinedTwoRegions->CreateRectRgn(0, 0, 0, 0);
	//}
	//this->combinedTwoRegions->CombineRgn(this->primaryCurrentActionProcessedRegion, this->secondaryCurrentActionProcessedRegion, RGN_OR);
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	//this->sumRegion->CopyRgn(this->combinedTwoRegions);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightPreviousWordWithinSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->startRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightPreviousWordBeyondSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength()) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->secondaryCurrentActionProcessedRegion == 0) {
	//	this->secondaryCurrentActionProcessedRegion = new CRgn;
	//	this->secondaryCurrentActionProcessedRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	//this->secondaryCurrentActionProcessedRegion->CopyRgn(this->copyOfSumRegion);


	//if (this->combinedTwoRegions == 0) {
	//	this->combinedTwoRegions = new CRgn;
	//	this->combinedTwoRegions->CreateRectRgn(0, 0, 0, 0);
	//}
	//this->combinedTwoRegions->CombineRgn(this->primaryCurrentActionProcessedRegion, this->secondaryCurrentActionProcessedRegion, RGN_OR);
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	//this->sumRegion->CopyRgn(this->combinedTwoRegions);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightFromCurrentColumnIndexToFirstColumnIndexInRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->notePadForm->notePad->GetCurrent())-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightFromCurrentColumnIndexToLastColumnIndexInRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	//origin으로 역방향삭제인지 정방향 누적선택인지 확인하는거고 영역선택하는것은 원래 줄위치 칸위치를 참조해서 하자!!
	upperLeftY = textMetric.GetY(this->notePadForm->notePad->GetCurrent())-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row,this->startColumnIndex ) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightFromCurrentIndexToNotePadFirst() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long rowIndex = this->startRowIndex;
	while (rowIndex >= 0) {
		Long upperLeftY;
		Long bottomRightY;
		Long upperLeftX;
		Long bottomRightX;
		
		if (rowIndex==this->startRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex)-vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4-hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
		}
		else {
			upperLeftY = textMetric.GetY(rowIndex)-vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4-hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;
		}
		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {
			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
		}
		this->offsetedHPosition = hPosition;
		this->offsetedVPosition = vPosition;
		rowIndex--;
	}
	
	if (this->copyOfSumRegion == 0) {
			this->copyOfSumRegion = new CRgn;
			this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	//this->copyOfSumRegion->CombineRgn(this->sumRegion,this->copyOfSumRegion,RGN_OR);
	//this->sumRegion->CopyRgn(this->copyOfSumRegion);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightFromCurrentIndexToNotePadLast() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long rowIndex = this->startRowIndex;
	while (rowIndex <= this->endRowIndex) {
		Long upperLeftY;
		Long bottomRightY;
		Long upperLeftX;
		Long bottomRightX;
		
		if (rowIndex == this->startRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex)-vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;
		}
		else {
			upperLeftY = textMetric.GetY(rowIndex)-vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4-hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;
		}
		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {
			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
		}
		
		this->offsetedHPosition = hPosition;
		this->offsetedVPosition = vPosition;
		rowIndex++;
	}
	if (this->copyOfSumRegion == 0) {
			this->copyOfSumRegion = new CRgn;
			this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	//this->copyOfSumRegion->CombineRgn(this->sumRegion,this->copyOfSumRegion,RGN_OR);
	//this->sumRegion->CopyRgn(this->copyOfSumRegion);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightFromCurrentIndexToDesignatedIndexOfPreviousRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->startRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex), 0) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex), this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->notePadForm->notePad->GetAt(this->endRowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;
	if (this->secondaryCurrentActionProcessedRegion != 0) {
		delete this->secondaryCurrentActionProcessedRegion;
	}
	this->secondaryCurrentActionProcessedRegion = new CRgn;
	this->secondaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->combinedTwoRegions == 0) {
		this->combinedTwoRegions = new CRgn;
		this->combinedTwoRegions->CreateRectRgn(0, 0, 0, 0);
	}
	this->combinedTwoRegions->CombineRgn(this->primaryCurrentActionProcessedRegion, this->secondaryCurrentActionProcessedRegion, RGN_OR);
	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->combinedTwoRegions);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		if (this->sumRegion->CombineRgn(this->sumRegion, this->combinedTwoRegions, RGN_OR)==COMPLEXREGION&&this->originColumnIndex<this->startColumnIndex) {
			
			if (this->originColumnIndex == 0) {
				this->originRowIndex = this->endRowIndex;
				this->originColumnIndex = this->notePadForm->notePad->GetAt(this->originRowIndex)->GetLength();
				this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
			}
			else {
				this->sumRegion->CombineRgn(this->sumRegion, this->copyOfSumRegion, RGN_XOR);
			}
		}
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightFromCurrentIndexToDesignatedIndexOfNextRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->startRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex),this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex),  this->notePadForm->notePad->GetAt(this->startRowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;
	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex),0 ) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	if (this->secondaryCurrentActionProcessedRegion != 0) {
		delete this->secondaryCurrentActionProcessedRegion;
	}
	this->secondaryCurrentActionProcessedRegion = new CRgn;
	this->secondaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->combinedTwoRegions == 0) {
		this->combinedTwoRegions = new CRgn;
		this->combinedTwoRegions->CreateRectRgn(0, 0, 0, 0);
	}
	this->combinedTwoRegions->CombineRgn(this->primaryCurrentActionProcessedRegion, this->secondaryCurrentActionProcessedRegion, RGN_OR);
	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->combinedTwoRegions);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		if (this->sumRegion->CombineRgn(this->sumRegion, this->combinedTwoRegions, RGN_OR)==COMPLEXREGION&&this->originColumnIndex>this->startColumnIndex) {
			
			if (this->originColumnIndex == this->notePadForm->notePad->GetAt(this->originRowIndex)->GetLength()) {
				this->originRowIndex = this->endRowIndex;
			    this->originColumnIndex = 0;
				this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
			}
			else {
				this->sumRegion->CombineRgn(this->sumRegion, this->copyOfSumRegion, RGN_XOR);
			}
		}
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightMousetoRightTracedInSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	
	upperLeftY = textMetric.GetY(this->originRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->originColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}

	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightMousetoLeftTracedInSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->startRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightMouseUpwardTraced() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	if (this->originRowIndex == this->startRowIndex && this->originColumnIndex < this->startColumnIndex) {
		if (this->originColumnIndex == 0) {
			this->originRowIndex = this->endRowIndex;
			this->originColumnIndex = this->notePadForm->notePad->GetAt(this->endRowIndex)->GetLength();
		}
		if (this->sumRegion != 0) {
			delete this->sumRegion;
			this->sumRegion = 0;
		}
	}
	Long rowIndex = this->originRowIndex;
	while (rowIndex >= this->endRowIndex) {
		Long upperLeftY;
		Long bottomRightY;
		Long upperLeftX;
		Long bottomRightX;

		if (rowIndex == this->originRowIndex && rowIndex == this->endRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
		}
		else if (rowIndex == this->originRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
		}
		else if (rowIndex == this->endRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
		}
		else {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
		}
		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {
			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
		}

		this->offsetedHPosition = hPosition;
		this->offsetedVPosition = vPosition;
		rowIndex--;
	}
	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	
	//this->copyOfSumRegion->CombineRgn(this->sumRegion,this->copyOfSumRegion,RGN_OR);
	//this->sumRegion->CopyRgn(this->copyOfSumRegion);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
	/*
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->startRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex), 0) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex), this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->notePadForm->notePad->GetAt(this->endRowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;
	if (this->secondaryCurrentActionProcessedRegion != 0) {
		delete this->secondaryCurrentActionProcessedRegion;
	}
	this->secondaryCurrentActionProcessedRegion = new CRgn;
	this->secondaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->combinedTwoRegions == 0) {
		this->combinedTwoRegions = new CRgn;
		this->combinedTwoRegions->CreateRectRgn(0, 0, 0, 0);
	}
	this->combinedTwoRegions->CombineRgn(this->primaryCurrentActionProcessedRegion, this->secondaryCurrentActionProcessedRegion, RGN_OR);
	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->combinedTwoRegions);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveHighLightRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->combinedTwoRegions, RGN_XOR);
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
	*/
}


void Selector::SetRegionForHightLightMouseDownwardTraced() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY=0;
	Long bottomRightY=0;
	Long upperLeftX=0;
	Long bottomRightX=0;

	if (this->originRowIndex==this->startRowIndex && this->originColumnIndex>this->startColumnIndex) {
		if (this->originColumnIndex == this->notePadForm->notePad->GetAt(this->originRowIndex)->GetLength()) {
			this->originRowIndex = this->endRowIndex;
			this->originColumnIndex = 0;
			
		}
		if (this->sumRegion != 0) {
			delete this->sumRegion;
			this->sumRegion = 0;
		}
	}
	Long rowIndex = this->originRowIndex;
	while (rowIndex <= this->endRowIndex) {

		if (rowIndex==this->originRowIndex&&rowIndex==this->endRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
		}
		else if (rowIndex == this->originRowIndex) {
			
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
			
		}
		else if (rowIndex == this->endRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
		}
		else {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
		}
		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
			this->primaryCurrentActionProcessedRegion = 0;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {
			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
			
		}

		this->offsetedHPosition = hPosition;
		this->offsetedVPosition = vPosition;
		rowIndex++;
	}
	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	//this->copyOfSumRegion->CombineRgn(this->sumRegion,this->copyOfSumRegion,RGN_OR);
	//this->sumRegion->CopyRgn(this->copyOfSumRegion);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
	/*
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->startRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex), this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex), this->notePadForm->notePad->GetAt(this->startRowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;
	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), 0) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	if (this->secondaryCurrentActionProcessedRegion != 0) {
		delete this->secondaryCurrentActionProcessedRegion;
	}
	this->secondaryCurrentActionProcessedRegion = new CRgn;
	this->secondaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->combinedTwoRegions == 0) {
		this->combinedTwoRegions = new CRgn;
		this->combinedTwoRegions->CreateRectRgn(0, 0, 0, 0);
	}
	this->combinedTwoRegions->CombineRgn(this->primaryCurrentActionProcessedRegion, this->secondaryCurrentActionProcessedRegion, RGN_OR);
	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->combinedTwoRegions);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveHighLightRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->combinedTwoRegions, RGN_XOR);
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
	*/
}


void Selector::SetRegionForHighLightWithMouseRightDownard(bool isFoward_FacingDirection) {

	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY = 0;
	Long bottomRightY = 0;
	Long upperLeftX = 0;
	Long bottomRightX = 0;

	Long j = this->endRowIndex-this->originRowIndex+1;
	Long i = 0;
	if (this->sumRegion != 0) {
		delete this->sumRegion;
		this->sumRegion = 0;
	}
	while (i < j) {
		if (j>1) {//선택영역 범위가 한줄이상이라는거
			if (i==0) {//첫번째 줄일때
				upperLeftY = textMetric.GetY(this->originRowIndex)-vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex),this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->notePadForm->notePad->GetAt(this->originRowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
			}
			else if (i==j-1) {//마지막 줄일떄
				upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex),0) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex),this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			}
			else {//첫번째 줄과 마지막줄 그 사이의 줄 일때
				upperLeftY = textMetric.GetY(this->originRowIndex+i) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex+i),0) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex + i), this->notePadForm->notePad->GetAt(this->originRowIndex + i)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
			}
		}
		else {//선택영역 범위가 한줄이라는것.
			upperLeftY = textMetric.GetY(this->originRowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex),this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
		}

		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
			this->primaryCurrentActionProcessedRegion = 0;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
		}
#if 0;
		else {
			
			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			
		}

		
#endif 0;
		i++;
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
#if 0;
	if (isFoward_FacingDirection==false) {
		SelectModifier selectModifier(this);
		selectModifier.MoveCopyOfSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion,this->copyOfSumRegion,RGN_AND);
	}
#endif 0;
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForHighLightWithMouseLeftUpward(bool isFoward_FacingDirection) {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	
	Long upperLeftY = 0;
	Long bottomRightY = 0;
	Long upperLeftX = 0;
	Long bottomRightX = 0;

	Long j = this->originRowIndex - this->endRowIndex + 1;
	Long i = 0;

	if (this->sumRegion != 0) {
		delete this->sumRegion;
		this->sumRegion = 0;
	}
	while (i < j) {
		if (j > 1) {//선택영역 범위가 한줄이상이라는거
			if (i == 0) {//첫번째 줄일때
				upperLeftY = textMetric.GetY(this->endRowIndex) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex),this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->notePadForm->notePad->GetAt(this->endRowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
			}
			else if (i == j - 1) {//마지막 줄일떄
				upperLeftY = textMetric.GetY(this->originRowIndex) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			}
			else {//첫번째 줄과 마지막줄 그 사이의 줄 일때
				upperLeftY = textMetric.GetY(this->endRowIndex+ i) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex + i), 0) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex + i), this->notePadForm->notePad->GetAt(this->endRowIndex + i)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
			}
		}
		else {//선택영역 범위가 한줄이라는것.
			upperLeftY = textMetric.GetY(this->originRowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
		}

		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
			this->primaryCurrentActionProcessedRegion = 0;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
		}
#if 0;
		else {
			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);

		}
#endif 0;
		
		i++;
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}

#if 0;
	if (isFoward_FacingDirection == false) {
		SelectModifier selectModifier(this);
		selectModifier.MoveCopyOfSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->copyOfSumRegion, RGN_AND);
	}
#endif 0;
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::ReHighLightRightDownwardSumRegionMatchToClientArea() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY = 0;
	Long bottomRightY = 0;
	Long upperLeftX = 0;
	Long bottomRightX = 0;

	Long j = this->endRowIndex - this->originRowIndex + 1;
	Long i = 0;
	if (this->sumRegion != 0) {
		delete this->sumRegion;
		this->sumRegion = 0;
	}
	while (i < j) {

		if (j > 1) {//선택영역 범위가 한줄이상이라는거
			if (i == 0) {//첫번째 줄일때
				upperLeftY = textMetric.GetY(this->originRowIndex) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->notePadForm->notePad->GetAt(this->originRowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
			}
			else if (i == j - 1) {//마지막 줄일떄
				upperLeftY = textMetric.GetY(this->endRowIndex) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			}
			else {//첫번째 줄과 마지막줄 그 사이의 줄 일때
				upperLeftY = textMetric.GetY(this->originRowIndex + i) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex + i), 0) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex + i), this->notePadForm->notePad->GetAt(this->originRowIndex + i)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
			}
		}
		else {//선택영역 범위가 한줄이라는것.
			upperLeftY = textMetric.GetY(this->originRowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
		}

		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
			this->primaryCurrentActionProcessedRegion = 0;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {

			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
		}

		this->offsetedHPosition = hPosition;
		this->offsetedVPosition = vPosition;
		i++;
	}

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}

	this->copyOfSumRegion->CopyRgn(this->sumRegion);
	
}



void Selector::ReHighLightLeftUpwardSumRegionMatchToClientArea() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY = 0;
	Long bottomRightY = 0;
	Long upperLeftX = 0;
	Long bottomRightX = 0;

	Long j = this->originRowIndex - this->endRowIndex + 1;
	Long i = 0;

	if (this->sumRegion != 0) {
		delete this->sumRegion;
		this->sumRegion = 0;
	}
	while (i < j) {
		if (j > 1) {//선택영역 범위가 한줄이상이라는거
			if (i == 0) {//첫번째 줄일때
				upperLeftY = textMetric.GetY(this->endRowIndex) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->notePadForm->notePad->GetAt(this->endRowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
			}
			else if (i == j - 1) {//마지막 줄일떄
				upperLeftY = textMetric.GetY(this->originRowIndex) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			}
			else {//첫번째 줄과 마지막줄 그 사이의 줄 일때
				upperLeftY = textMetric.GetY(this->endRowIndex + i) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex + i), 0) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex + i), this->notePadForm->notePad->GetAt(this->endRowIndex + i)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
			}
		}
		else {//선택영역 범위가 한줄이라는것.
			upperLeftY = textMetric.GetY(this->originRowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
		}

		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
			this->primaryCurrentActionProcessedRegion = 0;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {
			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);

		}
		this->offsetedHPosition = hPosition;
		this->offsetedVPosition = vPosition;
		i++;
	}

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}

	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}

void Selector::HighLightMatchContents() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long upperLeftY = 0;
	Long bottomRightY = 0;
	Long upperLeftX = 0;
	Long bottomRightX = 0;

	Long j = this->endRowIndex - this->originRowIndex + 1;
	Long i = 0;
	if (this->sumRegion != 0) {
		delete this->sumRegion;
		this->sumRegion = 0;
	}
	while (i < j) {

		if (j > 1) {//선택영역 범위가 한줄이상이라는거
			if (i == 0) {//첫번째 줄일때
				upperLeftY = textMetric.GetY(this->originRowIndex) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->notePadForm->notePad->GetAt(this->originRowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
			}
			else if (i == j - 1) {//마지막 줄일떄
				upperLeftY = textMetric.GetY(this->endRowIndex) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			}
			else {//첫번째 줄과 마지막줄 그 사이의 줄 일때
				upperLeftY = textMetric.GetY(this->originRowIndex + i) - vPosition;
				bottomRightY = upperLeftY + tm.tmHeight;
				upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex + i), 0) + tm.tmAveCharWidth / 4 - hPosition;
				bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex + i), this->notePadForm->notePad->GetAt(this->originRowIndex + i)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
			}
		}
		else {//선택영역 범위가 한줄이라는것.
			upperLeftY = textMetric.GetY(this->originRowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->originColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->originRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
		}

		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
			this->primaryCurrentActionProcessedRegion = 0;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {

			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_OR);
		}

		this->offsetedHPosition = hPosition;
		this->offsetedVPosition = vPosition;
		i++;
	}

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}

	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}

void Selector::SetRegionForUnHighLightNextCharWithinSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;
	
	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	if (this->endColumnIndex == 0) {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	else {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {
	
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}

void Selector::SetRegionForUnHighLightNextCharBeyondSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex - 1) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {

	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);

}

void Selector::SetRegionForUnHighLightPreviousCharWithinSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	if (this->startColumnIndex == 0) {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
		bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	else {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
		bottomRightX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	/*upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4;
	if (this->startColumnIndex==0) {
		bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4;
	}
	else {
		bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex + 1) + tm.tmAveCharWidth / 4;
	}*/
	
	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}

void Selector::SetRegionForUnHighLightPreviousCharBeyondSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex +1) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}

void Selector::SetRegionForUnHighLightNextWordWithinSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	if (this->endColumnIndex == 0) {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	else {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);

}

void Selector::SetRegionForUnHighLightNextWordBeyondSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	if (this->endColumnIndex == 0) {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	else {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;


	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);

}

void Selector::SetRegionForUnHighLightPreviousWordWithinSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	if (this->startColumnIndex == 0) {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
		bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	else {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
		bottomRightX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	
	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}

void Selector::SetRegionForUnHighLightPreviousWordBeyondSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	if (this->startColumnIndex == 0) {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
		bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	else {
		upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
		bottomRightX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	}
	

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForUnHighLightFromCurrentColumnIndexToFirstColumnIndexInSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}

	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);

}

void Selector::SetRegionForUnHighLightFromCurrentColumnIndexToFirstColumnIndexBeyondSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);

}


void Selector::SetRegionForUnHighLightFromCurrentColumnIndexToLastColumnIndexInSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}

	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);

}


void Selector::SetRegionForUnHighLightFromCurrentColumnIndexToLastColumnIndexBeyondSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row,this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength()) + tm.tmAveCharWidth / 4-hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}

	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->copyOfSumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}

	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);

}

void Selector::SetRegionForUnHighLightFromCurrentIndexToNotePadFirst() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long rowIndex = this->startRowIndex;
	while (rowIndex >= 0) {
		Long upperLeftY;
		Long bottomRightY;
		Long upperLeftX;
		Long bottomRightX;
	
		if (rowIndex == this->startRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex)-vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4-hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
		}
		else {
			upperLeftY = textMetric.GetY(rowIndex)-vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4-hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;
		}
		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
		}

		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {
			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
		}
		this->offsetedHPosition = hPosition;
		this->offsetedVPosition = vPosition;
		rowIndex--;
	}
	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	//this->copyOfSumRegion->CombineRgn(this->sumRegion, this->copyOfSumRegion, RGN_XOR);
	//this->sumRegion->CopyRgn(this->copyOfSumRegion);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}

void Selector::SetRegionForUnHighLightFromCurrentIndexToNotePadLast() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long rowIndex = this->startRowIndex;
	while (rowIndex <= this->endRowIndex) {
		Long upperLeftY;
		Long bottomRightY;
		Long upperLeftX;
		Long bottomRightX;
		
		if (rowIndex == this->startRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex)-vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;
		}
		else {
			upperLeftY = textMetric.GetY(rowIndex)-vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4-hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;
		}
		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {
			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
		}
		this->offsetedHPosition = hPosition;
		this->offsetedVPosition = vPosition;
		rowIndex++;
	}
	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	//this->copyOfSumRegion->CombineRgn(this->sumRegion, this->copyOfSumRegion, RGN_XOR);
	//this->sumRegion->CopyRgn(this->copyOfSumRegion);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);

}


void Selector::SetRegionForUnHighLightFromCurrentIndexToDesignatedIndexOfPreviousRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->startRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex), 0) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex), this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->notePadForm->notePad->GetAt(this->endRowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;	if (this->secondaryCurrentActionProcessedRegion != 0) {
		delete this->secondaryCurrentActionProcessedRegion;
	}
	this->secondaryCurrentActionProcessedRegion = new CRgn;
	this->secondaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->combinedTwoRegions == 0) {
		this->combinedTwoRegions = new CRgn;
		this->combinedTwoRegions->CreateRectRgn(0, 0, 0, 0);
	}
	this->combinedTwoRegions->CombineRgn(this->primaryCurrentActionProcessedRegion, this->secondaryCurrentActionProcessedRegion, RGN_OR);
	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->combinedTwoRegions);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->sumRegion, this->combinedTwoRegions, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	//}
	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForUnHighLightFromCurrentIndexToDesignatedIndexOfNextRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->startRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex), this->startColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->startRowIndex), this->notePadForm->notePad->GetAt(this->startRowIndex)->GetLength()) + tm.tmAveCharWidth / 4-hPosition;
	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	upperLeftY = textMetric.GetY(this->endRowIndex)-vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), 0) + tm.tmAveCharWidth / 4-hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(this->endRowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4-hPosition;
	if (this->secondaryCurrentActionProcessedRegion != 0) {
		delete this->secondaryCurrentActionProcessedRegion;
	}
	this->secondaryCurrentActionProcessedRegion = new CRgn;
	this->secondaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->combinedTwoRegions == 0) {
		this->combinedTwoRegions = new CRgn;
		this->combinedTwoRegions->CreateRectRgn(0, 0, 0, 0);
	}
	this->combinedTwoRegions->CombineRgn(this->primaryCurrentActionProcessedRegion, this->secondaryCurrentActionProcessedRegion, RGN_OR);
	//if (this->sumRegion == 0) {
	//	this->sumRegion = new CRgn;
	//	sumRegion->CreateRectRgn(0, 0, 0, 0);
	//	this->sumRegion->CopyRgn(this->combinedTwoRegions);
	//}
	//else {
	SelectModifier selectModifier(this);
	selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
	this->sumRegion->CombineRgn(this->sumRegion, this->combinedTwoRegions, RGN_XOR);
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;
	//}
	//if (this->copyOfSumRegion == 0) {
	//	this->copyOfSumRegion = new CRgn;
	//	this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	//}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);

}


void Selector::SetRegionForUnHighLightMousetoRightTracedInSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;


	upperLeftY = textMetric.GetY(this->startRowIndex) - vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}

	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForUnHighLightMousetoLeftTracedInSingleRow() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();
	Long upperLeftY;
	Long bottomRightY;
	Long upperLeftX;
	Long bottomRightX;

	upperLeftY = textMetric.GetY(this->startRowIndex) - vPosition;
	bottomRightY = upperLeftY + tm.tmHeight;
	upperLeftX = textMetric.GetX(this->notePadForm->row, this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
	bottomRightX = textMetric.GetX(this->notePadForm->row, this->startColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;

	if (this->primaryCurrentActionProcessedRegion != 0) {
		delete this->primaryCurrentActionProcessedRegion;
	}
	this->primaryCurrentActionProcessedRegion = new CRgn;
	this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

	if (this->sumRegion == 0) {
		this->sumRegion = new CRgn;
		sumRegion->CreateRectRgn(0, 0, 0, 0);
		this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
	}
	else {
		SelectModifier selectModifier(this);
		selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
		this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
	}
	this->offsetedHPosition = hPosition;
	this->offsetedVPosition = vPosition;

	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForUnHighLightMouseUpwardTraced() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long rowIndex = this->startRowIndex;
	while (rowIndex >= this->endRowIndex) {
		Long upperLeftY;
		Long bottomRightY;
		Long upperLeftX;
		Long bottomRightX;

		if (rowIndex == this->startRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->startColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
		}
		else if (rowIndex == this->endRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
		}
		else {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
		}
		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {
			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
		}

		this->offsetedHPosition = hPosition;
		this->offsetedVPosition = vPosition;
		rowIndex--;
	}
	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	//this->copyOfSumRegion->CombineRgn(this->sumRegion,this->copyOfSumRegion,RGN_OR);
	//this->sumRegion->CopyRgn(this->copyOfSumRegion);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}


void Selector::SetRegionForUnHighLightMouseDownwardTraced() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = this->notePadForm->GetScrollController()->GetHPosition();
	Long vPosition = this->notePadForm->GetScrollController()->GetVPosition();

	Long rowIndex = this->startRowIndex;
	while (rowIndex <= this->endRowIndex) {
		Long upperLeftY;
		Long bottomRightY;
		Long upperLeftX;
		Long bottomRightX;

		if (rowIndex == this->startRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->startColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
		}
		else if (rowIndex == this->endRowIndex) {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->endColumnIndex) + tm.tmAveCharWidth / 4 - hPosition;
		}
		else {
			upperLeftY = textMetric.GetY(rowIndex) - vPosition;
			bottomRightY = upperLeftY + tm.tmHeight;
			upperLeftX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), 0) + tm.tmAveCharWidth / 4 - hPosition;
			bottomRightX = textMetric.GetX(this->notePadForm->notePad->GetAt(rowIndex), this->notePadForm->notePad->GetAt(rowIndex)->GetLength()) + tm.tmAveCharWidth / 4 - hPosition;
		}
		if (this->primaryCurrentActionProcessedRegion != 0) {
			delete this->primaryCurrentActionProcessedRegion;
		}
		this->primaryCurrentActionProcessedRegion = new CRgn;
		this->primaryCurrentActionProcessedRegion->CreateRectRgn(upperLeftX, upperLeftY, bottomRightX, bottomRightY);

		if (this->sumRegion == 0) {
			this->sumRegion = new CRgn;
			sumRegion->CreateRectRgn(0, 0, 0, 0);
			this->sumRegion->CopyRgn(this->primaryCurrentActionProcessedRegion);
		}
		else {
			SelectModifier selectModifier(this);
			selectModifier.MoveSumRegionMatchToScrollPosition(hPosition, vPosition);
			this->sumRegion->CombineRgn(this->sumRegion, this->primaryCurrentActionProcessedRegion, RGN_XOR);
		}

		this->offsetedHPosition = hPosition;
		this->offsetedVPosition = vPosition;
		rowIndex++;
	}
	if (this->copyOfSumRegion == 0) {
		this->copyOfSumRegion = new CRgn;
		this->copyOfSumRegion->CreateRectRgn(0, 0, 0, 0);
	}
	//this->copyOfSumRegion->CombineRgn(this->sumRegion,this->copyOfSumRegion,RGN_OR);
	//this->sumRegion->CopyRgn(this->copyOfSumRegion);
	this->copyOfSumRegion->CopyRgn(this->sumRegion);
}



bool Selector::IsRightDownWardSelectedArea() {
	Long originRowIndex = this->GetOriginRowIndex();
	Long originColumnIndex = this->GetOriginColumnIndex();
	Long endRowIndex = this->GetEndRowIndex();
	Long endColumnIndex = this->GetEndColumnIndex();

	bool isRightDownwardSelected = false;
	
	if (originRowIndex == endRowIndex) {
		if (originColumnIndex < endColumnIndex){
			isRightDownwardSelected = true;
		}
	}
	else {
		if (originRowIndex < endRowIndex) {
			isRightDownwardSelected = true;
		}
	}

	return isRightDownwardSelected;
}

void Selector::SetStartRowIndex(Long startRowIndex) {
	this->startRowIndex = startRowIndex;
}


void Selector::SetStartColumnIndex(Long startColumnIndex) {
	this->startColumnIndex = startColumnIndex;
}


void Selector::SetEndRowIndex(Long endRowIndex) {
	this->endRowIndex = endRowIndex;
}


void Selector::SetEndColumnIndex(Long endColumnIndex) {
	this->endColumnIndex = endColumnIndex;
}

void Selector::SetOriginRowIndex(Long originRowIndex) {
	this->originRowIndex = originRowIndex;
}

void Selector::SetOriginColumnIndex(Long originColumnIndex) {
	this->originColumnIndex = originColumnIndex;
}


void Selector::SetOffsetedHPosition(Long offsetedHPosition) {
	this->offsetedHPosition = offsetedHPosition;
}


void Selector::SetOffsetedVPosition(Long offsetedVPosition) {
	this->offsetedVPosition = offsetedVPosition;
}

void Selector::SetSelectedAreaLength(Long selectedAreaLength) {
	this->selectedAreaLength = selectedAreaLength;
}

void Selector::SetLengthToSelectedArea(Long lengthToSelectedArea) {
	this->lengthToSelectedArea = lengthToSelectedArea;
}

void Selector::SetIsFirstContentTab(bool isFirstContentTab) {
	this->isFirstContentTab = isFirstContentTab;
}