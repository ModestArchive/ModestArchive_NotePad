//NotePadMetric.cpp

#include"NotePadMetric.h"
#include"TextMetric.h"
#include"Glyph.h"
#include"Font.h"
#include"ScrollController.h"
#include"DummyRow.h"
#include"SingleByteCharacter.h"
#include"Selector.h"
#include"SelectModifier.h"


NotePadMetric::NotePadMetric(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}


NotePadMetric::~NotePadMetric() {

}


bool NotePadMetric::IsRowShorterThanClientAreaX(Glyph* row, Long hPos) {
	TextMetric textMetric(this->notePadForm);

	BOOL isRowShorterThanClientAreaX = false;

	if (textMetric.GetX(row, row->GetLength()) > hPos) {
		isRowShorterThanClientAreaX = false;
	}
	else {
		isRowShorterThanClientAreaX = true;
	}

	return isRowShorterThanClientAreaX;
}


Long NotePadMetric::GetFirstColumnIndexInClientArea(Glyph* row, Long hPos) {
	TextMetric textMetric(this->notePadForm);

	Long index = 0;
	Long firstColumnIndexInClientArea = 0;

	while (textMetric.GetX(row, index) < hPos) {
		index++;
	}
	if (index > 0) {
		index--;
	}
	firstColumnIndexInClientArea = index;
	return firstColumnIndexInClientArea;
}


bool NotePadMetric::IsRowLongerThanClientAreaX(Glyph* row, Long hPosPlusClientArea) {
	TextMetric textMetric(this->notePadForm);
	BOOL IsRowLongerThanClientAreaX = false;

	Long index = row->GetCurrent();
	while (index <= row->GetLength() && textMetric.GetX(row, index) <= hPosPlusClientArea) {
		index++;
	}

	if (index <= row->GetLength()) {
		IsRowLongerThanClientAreaX = true;
	}

	return IsRowLongerThanClientAreaX;
}


Long NotePadMetric::GetFirstColumnIndexOverClientArea(Glyph* row, Long hPosPlusClientArea) {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long firstColumnIndexOverClientArea = 0;

	Long index = 0;
	while (textMetric.GetX(row, index)+tm.tmAveCharWidth/4 <= hPosPlusClientArea - tm.tmAveCharWidth / 2) {
		index++;
	}
	firstColumnIndexOverClientArea = index-1;

	return firstColumnIndexOverClientArea;
}

Long NotePadMetric::GetFirstColumnIndexOverClientAreaForPrint(Glyph* row, Long viewerPortHorzOrg,Long hPosPlusClientArea) {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long firstColumnIndexOverClientArea = 0;

	Long index = 0;
	while (textMetric.GetX(row, index)+ viewerPortHorzOrg  <= hPosPlusClientArea ) {
		index++;
	}
	firstColumnIndexOverClientArea = index - 1;

	return firstColumnIndexOverClientArea;
}

bool NotePadMetric::IsNotePadLongerThanClientAreaY(Long index, Long vPosPlusClientArea) {
	TextMetric textMetric(this->notePadForm);
	BOOL isNotePadLongerThanClientAreaY = false;
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	while (index <= this->notePadForm->notePad->GetLength() - 1 && textMetric.GetY(index) + tm.tmHeight + 5 < vPosPlusClientArea) {
       index++;
	}
	if (index <= this->notePadForm->notePad->GetLength() - 1) {
		isNotePadLongerThanClientAreaY = true;
	}

	return isNotePadLongerThanClientAreaY;
}


Long NotePadMetric::GetFirstRowIndexOverClientArea(Long index, Long vPosPlusClientArea) {
	TextMetric textMetric(this->notePadForm);
	Long firstRowIndexOverClientArea = -1;
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	while (index <= this->notePadForm->notePad->GetLength() - 1 && textMetric.GetY(index) + tm.tmHeight + 5 < vPosPlusClientArea) {
		index++;
	}
	if (index <= this->notePadForm->notePad->GetLength() - 1) {
		firstRowIndexOverClientArea = index;
	}

	return firstRowIndexOverClientArea;
}


Long NotePadMetric::GetFirstRowIndexInClientArea(Long vPos) {
	TextMetric textMetric(this->notePadForm);
	Long index = 0;

	while (textMetric.GetY(index) < vPos) {
		index++;
	}
	if (index > 0) {
		index--;
	}
	return index;
}


Long NotePadMetric::GetLongestX() {
	TextMetric textMetric(this->notePadForm);
	Long i = 0; 
	Long longestX = 0;  
	Long currentX = 0;

	while (i < this->notePadForm->notePad->GetLength()) {
		currentX = textMetric.GetX(this->notePadForm->notePad->GetAt(i), this->notePadForm->notePad->GetAt(i)->GetLength());
		if (currentX > longestX) {
			longestX = currentX;
		}

		i++;
	}
	return longestX;
}


Long NotePadMetric::GetLongestXRowIndex() {
	TextMetric textMetric(this->notePadForm);
	Long i = 0; 
	Long longestX = 0;  
	Long currentX = 0; 
	Long index = 0;

	while (i < this->notePadForm->notePad->GetLength()) {
		currentX = textMetric.GetX(this->notePadForm->notePad->GetAt(i), this->notePadForm->notePad->GetAt(i)->GetLength());
		if (currentX > longestX) {
			longestX = currentX;
			index = i;
		}

		i++;
	}
	return index;
}


Long NotePadMetric::MoveLongestXRow(Long longestXRowIndex, Long vPos) {

	TextMetric textMetric(this->notePadForm);

	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long currentRowIndex = this->notePadForm->notePad->GetCurrent();

	while (currentRowIndex < longestXRowIndex) {
		this->notePadForm->notePad->Next();
		currentRowIndex = this->notePadForm->notePad->GetCurrent();
	}
	while (currentRowIndex > longestXRowIndex) {
		this->notePadForm->notePad->Previous();
		currentRowIndex = this->notePadForm->notePad->GetCurrent();
	}
	this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
	this->notePadForm->row->First();

	Long currentVPos = vPos;
	while (textMetric.GetY(longestXRowIndex) < currentVPos) {
		this->notePadForm->GetScrollController()->MoveVScrPrevious();
		currentVPos = this->notePadForm->GetScrollController()->GetVPosition();
	}
	while (textMetric.GetY(longestXRowIndex) + tm.tmHeight > currentVPos + this->notePadForm->GetCy()) {
		this->notePadForm->GetScrollController()->MoveVScrNext();
		currentVPos = this->notePadForm->GetScrollController()->GetVPosition();
	}
	this->notePadForm->SetScrollPos(SB_VERT, currentVPos, TRUE);

	return longestXRowIndex;
}


Long NotePadMetric::GetClientLongestX() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long clientLongestX = 0;
	Long clientCurrentX = 0;
	Long minimumOfRowIndex = 0;
	Long maximumOfRowIndex = 0;
	Long i = 0;

	while (textMetric.GetY(i) < this->notePadForm->GetScrollController()->GetVPosition()) {
		i++;
	}
	minimumOfRowIndex = i;
	maximumOfRowIndex = i;

	while (textMetric.GetY(i) + tm.tmHeight + 5 < this->notePadForm->GetScrollController()->GetVPosition() + this->notePadForm->GetCy()) {
		i++;
	}
	maximumOfRowIndex = i;
	i = minimumOfRowIndex;

	while (i <= maximumOfRowIndex) {
		clientCurrentX = textMetric.GetX(this->notePadForm->notePad->GetAt(i), this->notePadForm->notePad->GetAt(i)->GetLength());

		if (clientCurrentX > clientLongestX) {
			clientLongestX = clientCurrentX;
		}
		i++;
	}
	return clientLongestX;
}


Long NotePadMetric::GetClientLongestXRowIndex() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	Long clientLongestX = 0;
	Long clientLongestXRowIndex = 0;
	Long clientCurrentX = 0;
	Long minimumOfRowIndex = 0;
	Long maximumOfRowIndex = 0;
	Long i = 0;

	while (textMetric.GetY(i) < this->notePadForm->GetScrollController()->GetVPosition()) {
		i++;
	}
	minimumOfRowIndex = i;
	maximumOfRowIndex = i;

	while (i < this->notePadForm->notePad->GetLength() - 1 && textMetric.GetY(i) + tm.tmHeight + 5 < this->notePadForm->GetScrollController()->GetVPosition() + this->notePadForm->GetCy()) {
		i++;
	}
	maximumOfRowIndex = i;
	i = minimumOfRowIndex;

	while (i <= maximumOfRowIndex) {
		clientCurrentX = textMetric.GetX(this->notePadForm->notePad->GetAt(i), this->notePadForm->notePad->GetAt(i)->GetLength());

		if (clientCurrentX > clientLongestX) {
			clientLongestX = clientCurrentX;
			clientLongestXRowIndex = i;
		}
		i++;
	}
	return clientLongestXRowIndex;
}

Long NotePadMetric::GetFirstTabColumnIndexWhenTabBeyondClientArea(Glyph* row, Long firstColumnIndexOverClientArea) {
	Long firstTabColumnIndex = firstColumnIndexOverClientArea;
	while (firstTabColumnIndex<this->notePadForm->row->GetLength()&&
		  dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(firstTabColumnIndex)) &&
		  ((SingleByteCharacter*)(this->notePadForm->row->GetAt(firstTabColumnIndex)))->GetSingleByteContent() == '\t') {
			firstTabColumnIndex++;
	}
	firstTabColumnIndex-=8;
	return firstTabColumnIndex;
}


Long NotePadMetric::GetRemainClientWidthArea(Glyph* row, Long clientWidthArea) {
	TextMetric textMetric(this->notePadForm);
	Long remainClientWidthArea = 0;
	Long x = textMetric.GetX(row, row->GetLength());

	if (clientWidthArea-x>0) {
		remainClientWidthArea = clientWidthArea - x;
	}
	else {
		remainClientWidthArea = -1;
	}

	return remainClientWidthArea;
}


Long NotePadMetric::GetAddibleCharacterNumberProportionalToRemainWidthClientArea(Glyph* row, Long remainClientArea) {

	TextMetric textMetric(this->notePadForm); 
	Long addibleCharacterNumber = 0;
	Long x = 0;
	if(remainClientArea>0){
		while (addibleCharacterNumber<=row->GetLength() && x<remainClientArea) {
			addibleCharacterNumber++;
			if (addibleCharacterNumber <= row->GetLength()) {
				x=textMetric.GetX(row, addibleCharacterNumber);
			}
		}
		addibleCharacterNumber--;
		
		if (addibleCharacterNumber>0) {
			if (dynamic_cast<SingleByteCharacter*>(row->GetAt(addibleCharacterNumber - 1))) {
				if (((SingleByteCharacter*)(row->GetAt(addibleCharacterNumber - 1)))->GetSingleByteContent() == '\t') {
					if (addibleCharacterNumber < row->GetLength() && ((SingleByteCharacter*)(row->GetAt(addibleCharacterNumber)))->GetSingleByteContent() == '\t') {
						while (addibleCharacterNumber - 1 >= 0 && ((SingleByteCharacter*)(row->GetAt(addibleCharacterNumber - 1)))->GetSingleByteContent() == '\t') {
							addibleCharacterNumber--;
						}
					}
				}
			}
		}
	}
	return addibleCharacterNumber;
}


Long NotePadMetric::MoveClientLongestXRow(Long clientLongestXRowIndex, Long vPos) {

	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long currentRowIndex = this->notePadForm->notePad->GetCurrent();

	while (currentRowIndex < clientLongestXRowIndex) {
		this->notePadForm->notePad->Next();
		currentRowIndex = this->notePadForm->notePad->GetCurrent();
	}
	while (currentRowIndex > clientLongestXRowIndex) {
		this->notePadForm->notePad->Previous();
		currentRowIndex = this->notePadForm->notePad->GetCurrent();
	}
	this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
	this->notePadForm->row->First();

	Long currentVPos = vPos;

	while (textMetric.GetY(clientLongestXRowIndex) + tm.tmHeight + 5 > currentVPos + this->notePadForm->GetCy()) {
		this->notePadForm->GetScrollController()->MoveHScrNext();
		currentVPos = this->notePadForm->GetScrollController()->GetVPosition();
	}
	this->notePadForm->SetScrollPos(SB_VERT, currentVPos, TRUE);

	return clientLongestXRowIndex;
}


void NotePadMetric::MoveColumnOverHPos(Long hPos) {
	TextMetric textMetric(this->notePadForm);
	while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) <= hPos &&
		this->notePadForm->row->GetCurrent() < this->notePadForm->row->GetLength()) {
		this->notePadForm->row->Next();
	}
}


void NotePadMetric::MoveVScrollAfterAddedContents() {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	if (textMetric.GetY(this->notePadForm->notePad->GetCurrent()) + tm.tmHeight+5 > this->notePadForm->GetScrollController()->GetVPosition() + this->notePadForm->GetCy()) {

		if (this->notePadForm->notePad->GetCurrent() >= this->notePadForm->notePad->GetLength() - 1) {
			this->notePadForm->GetScrollController()->SetVPos(this->notePadForm->GetScrollLimit(SB_VERT));
		}
		else {
			this->notePadForm->GetScrollController()->MoveVScrNext();
		}
	}
}


void NotePadMetric::MoveVScrollAfterRemovedContents(bool isNotePadLengthDiffer) {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	
	if (isNotePadLengthDiffer==true) {
		if (this->notePadForm->notePad->GetCurrent() >= this->notePadForm->notePad->GetLength() - 1) {
			this->notePadForm->GetScrollController()->SetVPos(this->notePadForm->GetScrollLimit(SB_VERT));
		}
		else {
			this->notePadForm->GetScrollController()->MoveVScrPrevious();
		}
    }
}


void NotePadMetric::MoveVScrollAfterOnSizingWhenAutoLineBreakOn() {
	
}


bool NotePadMetric::GetThereIsContents() {
	bool thereIsContents = false;
	Long i = 0;
	Long count = 0;
	while (i<this->notePadForm->notePad->GetLength()&&count==0) {
		count += this->notePadForm->notePad->GetAt(i)->GetLength();
		i++;
	}
	if (i>=this->notePadForm->notePad->GetLength()) {
		thereIsContents = false;
	}
	if (count>0) {
		thereIsContents = true;
	}
	return thereIsContents;
}


Long NotePadMetric::GetTotalLengthToCurrent() {
	//현재위치에 해당하는 오야지줄위치를 구한다.
	TextMetric textMetric(this->notePadForm);
	Long ownerRowIndex = this->notePadForm->notePad->GetCurrent();
	Glyph* ownerRow = this->notePadForm->notePad->GetAt(ownerRowIndex);
	Long totalLengthToCurrent = 0;
	
	//텝포함해서 현재위치의 줄길이를 구한다.
	Long i = this->notePadForm->notePad->GetCurrent();
	Long j = 0;
	while (j <=i) {
		if (j == this->notePadForm->notePad->GetCurrent()) {
			totalLengthToCurrent += textMetric.GetX(this->notePadForm->notePad->GetAt(j), this->notePadForm->row->GetCurrent());
			if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(j)) && ((DummyRow*)(this->notePadForm->notePad->GetAt(j)))->GetIsTabErased() == true) {
				totalLengthToCurrent += textMetric.GetTextWidth(32) * 8;
			}
		}
		else {
			totalLengthToCurrent += textMetric.GetX(this->notePadForm->notePad->GetAt(j), this->notePadForm->notePad->GetAt(j)->GetLength());
			if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(j)) && ((DummyRow*)(this->notePadForm->notePad->GetAt(j)))->GetIsTabErased() == true) {
				totalLengthToCurrent += textMetric.GetTextWidth(32) * 8;
			}
		}
		j++;
	}

	return totalLengthToCurrent;
}


Long NotePadMetric::GetTotalLengthToDesignatedCoordinate(Long rowIndex, Long columnIndex) {
	//현재위치에 해당하는 오야지줄위치를 구한다.
	TextMetric textMetric(this->notePadForm);
	Long totalLengthToCurrent = 0;

	//텝포함해서 현재위치의 줄길이를 구한다.
	Long i = rowIndex;
	while (i >= 0) {
		if (i == rowIndex) {
			totalLengthToCurrent += textMetric.GetX(this->notePadForm->notePad->GetAt(i), columnIndex);
			if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(i)) && ((DummyRow*)(this->notePadForm->notePad->GetAt(i)))->GetIsTabErased() == true) {
				totalLengthToCurrent += textMetric.GetTextWidth(32) * 8;
			}
		}
		else {
			totalLengthToCurrent += textMetric.GetX(this->notePadForm->notePad->GetAt(i), this->notePadForm->notePad->GetAt(i)->GetLength());
			if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(i)) && ((DummyRow*)(this->notePadForm->notePad->GetAt(i)))->GetIsTabErased() == true) {
				totalLengthToCurrent += textMetric.GetTextWidth(32) * 8;
			}
		}
		i--;
	}

	return totalLengthToCurrent;
}


void NotePadMetric::MoveHScrollAndSelectionAfterFindMatchContents() {
	ScrollController* scrollController = this->notePadForm->GetScrollController();
	Selector* selector = this->notePadForm->GetSelector();
	TextMetric textMetric(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	Font font(this->notePadForm);
	tm = font.CalculateFontMetric();

	bool isHScrollOn=scrollController->GetIsHScrollOn();
	if (isHScrollOn==true) {
		if (textMetric.GetX(this->notePadForm->notePad->GetAt(selector->GetOriginRowIndex()), selector->GetOriginColumnIndex()) + tm.tmAveCharWidth / 4
			< scrollController->GetHPosition() ) {
				while (textMetric.GetX(this->notePadForm->notePad->GetAt(selector->GetOriginRowIndex()),selector->GetOriginColumnIndex())+tm.tmAveCharWidth/4
						< scrollController->GetHPosition()) {
					scrollController->MoveHScrPrevious();
				}
		}
		else if(textMetric.GetX(this->notePadForm->notePad->GetAt(selector->GetEndRowIndex()), selector->GetEndColumnIndex()) + tm.tmAveCharWidth / 4
			     > this->notePadForm->GetCx() + scrollController->GetHPosition() ) {
					while (textMetric.GetX(this->notePadForm->notePad->GetAt(selector->GetEndRowIndex()), selector->GetEndColumnIndex()) + tm.tmAveCharWidth / 4
							> this->notePadForm->GetCx() + scrollController->GetHPosition() ) {
						scrollController->MoveHScrNext();
					}
			 }
		scrollController->SetHScroll();
		SelectModifier selectModifier(selector);
		selectModifier.MoveSumRegionMatchToScrollPosition(scrollController->GetHPosition(), scrollController->GetVPosition());
		selector->SetOffsetedHPosition(scrollController->GetHPosition());
		selector->SetOffsetedVPosition(scrollController->GetVPosition());
	}
}

void NotePadMetric::MoveVScrollAndSelectionAfterFindMatchContents() {
	ScrollController* scrollController = this->notePadForm->GetScrollController();
	Selector* selector = this->notePadForm->GetSelector();
	TextMetric textMetric(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	Font font(this->notePadForm);
	tm = font.CalculateFontMetric();

	bool isVScrollOn = scrollController->GetIsVScrollOn();
	if (isVScrollOn==true) {
		if (textMetric.GetY(selector->GetEndRowIndex()) + tm.tmHeight + 5 > this->notePadForm->GetCy() + scrollController->GetVPosition()) {
			while (textMetric.GetY(selector->GetEndRowIndex()) + tm.tmHeight + 5 > this->notePadForm->GetCy() + scrollController->GetVPosition()) {
				scrollController->MoveVScrNext();
			}
		}
		else if (textMetric.GetY(selector->GetOriginRowIndex()) + tm.tmHeight + 5 < scrollController->GetVPosition()) {
			while (textMetric.GetY(selector->GetOriginRowIndex()) + tm.tmHeight + 5 <  scrollController->GetVPosition()) {
				scrollController->MoveVScrPrevious();
			}
		}
		scrollController->SetVScroll();
		SelectModifier selectModifier(selector);
		selectModifier.MoveSumRegionMatchToScrollPosition(scrollController->GetHPosition(), scrollController->GetVPosition());
		selector->SetOffsetedHPosition(scrollController->GetHPosition());
		selector->SetOffsetedVPosition(scrollController->GetVPosition());
	}
}

Long NotePadMetric::GetHowManyTabInToCurrentColumnInCurrentRow() {
	Long tabCount = 0;
	Glyph* row = this->notePadForm->row;
	Long i = 0;
	
	while (i<this->notePadForm->row->GetCurrent()) {
		if (dynamic_cast<SingleByteCharacter*>(row->GetAt(i))) {
			if (((SingleByteCharacter*)(row->GetAt(i)))->GetSingleByteContent() == '\t') {
				tabCount++;
				i += 8;
			}
			else {
				i++;
			}
		}
		else {
			i++;
		}
	}
	return tabCount;
}