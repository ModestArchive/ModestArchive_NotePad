//SelectModifier.cpp

#include"SelectModifier.h"
#include"Selector.h"
#include"Glyph.h"
#include"TextMetric.h"
#include"Font.h"
#include"ScrollController.h"
#include"DummyRow.h"
#include"SelectedAreaMetric.h"
#include"SingleByteCharacter.h"


SelectModifier::SelectModifier(Selector* selector){
	this->selector = selector;
	this->offsetedHPosition = selector->GetOffsetedHPosition();
	this->offsetedVPosition = selector->GetOffsetedVPosition();
}


SelectModifier::~SelectModifier() {

}


void SelectModifier::MoveSumRegionMatchToScrollPosition(Long hPosition, Long vPosition) {
	//TextMetric textMetric(this->notePadForm);
	//Font font(this->notePadForm);
	//TEXTMETRIC tm = { 0, };
	//tm = font.CalculateFontMetric();
	CPoint cPoint;
	
	if (hPosition > this->offsetedHPosition) {
		
		if (vPosition > this->offsetedVPosition) {
			cPoint.SetPoint(-hPosition + this->offsetedHPosition, -vPosition + this->offsetedVPosition);
		}
		else {
			cPoint.SetPoint(-hPosition + this->offsetedHPosition, this->offsetedVPosition - vPosition);
		}
		this->selector->GetSumRegion()->OffsetRgn(cPoint);
	}
	else {
		if (vPosition > this->offsetedVPosition) {
				cPoint.SetPoint(this->offsetedHPosition - hPosition, -vPosition + this->offsetedVPosition);
		}
		else {
				cPoint.SetPoint(this->offsetedHPosition - hPosition, this->offsetedVPosition - vPosition);
		}
		this->selector->GetSumRegion()->OffsetRgn(cPoint);
	}
	
}


void SelectModifier::MoveCopyOfSumRegionMatchToScrollPosition(Long hPosition, Long vPosition) {
	CPoint cPoint;

	if (hPosition > this->offsetedHPosition) {

		if (vPosition > this->offsetedVPosition) {
			cPoint.SetPoint(-hPosition + this->offsetedHPosition, -vPosition + this->offsetedVPosition);
		}
		else {
			cPoint.SetPoint(-hPosition + this->offsetedHPosition, this->offsetedVPosition - vPosition);
		}
	}
	else {
		if (vPosition > this->offsetedVPosition) {
			cPoint.SetPoint(this->offsetedHPosition - hPosition, -vPosition + this->offsetedVPosition);
		}
		else {
			cPoint.SetPoint(this->offsetedHPosition - hPosition, this->offsetedVPosition - vPosition);
		}
	}
	this->selector->GetCopyOfSumRegion()->OffsetRgn(cPoint);
}


void SelectModifier::ChangeRightDownwardSelectedAreaStartPointAfterAction(Long rowCountInFirstToSelectedAreaStartPoint) {
	NotePadForm* notePadForm = this->selector->GetNotePadForm();
	TextMetric textMetric(notePadForm);
	Long lengthToSelectedArea = 0;
	Long i = 0;
	Long j = 0;
	Glyph* row = notePadForm->notePad->GetAt(i);
	bool alreadyRowCounted = false;

	while (lengthToSelectedArea < this->selector->GetLengthToSelectedArea()) {
		if (alreadyRowCounted == false && dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(i)) == 0) {
			rowCountInFirstToSelectedAreaStartPoint--;
			alreadyRowCounted = true;
		}
		if (row->GetLength() <= j) {	
			i++;
			row = notePadForm->notePad->GetAt(i);
			if (dynamic_cast<DummyRow*>(row)) {
				if (((DummyRow*)(row))->GetIsTabErased()==true) {
					lengthToSelectedArea += textMetric.GetTextWidth(32) * 8;
				}
			}
			j = 0;
			alreadyRowCounted = false;
		}
		else {
			if (dynamic_cast<SingleByteCharacter*>(row->GetAt(j))) {
				if (((SingleByteCharacter*)(row->GetAt(j)))->GetSingleByteContent() == '\t') {
					lengthToSelectedArea += textMetric.GetTextWidth(32) * 8;
					j += 8;
				}
				else {
					lengthToSelectedArea += textMetric.GetCurrentTextWidth(row, j);//한글자를 검사하는데 그게 텝이면 *8,좌표도+8 처리해주기.
					j++;
				}
			}
			else {
				lengthToSelectedArea += textMetric.GetCurrentTextWidth(row, j);//한글자를 검사하는데 그게 텝이면 *8,좌표도+8 처리해주기.
				j++;
			}
		}
	}
	if (lengthToSelectedArea>0) {
		if (rowCountInFirstToSelectedAreaStartPoint>0) {
			while (rowCountInFirstToSelectedAreaStartPoint > 0) {
				i++;
				j = 0;
				rowCountInFirstToSelectedAreaStartPoint--;
			}
		}
		else if (rowCountInFirstToSelectedAreaStartPoint==0&& row->GetLength()==j) {
			i++;
			j = 0; 
		}
	}
	this->selector->SetOriginRowIndex(i);
	this->selector->SetOriginColumnIndex(j);
}


void SelectModifier::ChangeRightDownwardSelectedAreaEndPointAfterAction(Long rowCountInSelectedArea) {
	NotePadForm* notePadForm = this->selector->GetNotePadForm();
	TextMetric textMetric(notePadForm);
	Long i = this->selector->GetOriginRowIndex();
	Long j = this->selector->GetOriginColumnIndex();
	Long selectedAreaLength = 0;
	Glyph* row = this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex());
	bool alreadyRowCounted = false;

	if (dynamic_cast<DummyRow*>(row) && ((DummyRow*)(row))->GetIsTabErased()==true &&
		this->selector->GetOriginColumnIndex()==0 && this->selector->GetIsFirstContentTab()==true) {
		selectedAreaLength += textMetric.GetTextWidth(32) * 8;
	}
	while (selectedAreaLength < this->selector->GetSelectedAreaLength()) {
		if (alreadyRowCounted == false && dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(i)) == 0) {
			rowCountInSelectedArea--;
			alreadyRowCounted = true;
		}
		if(row->GetLength() > j) {
			if (dynamic_cast<SingleByteCharacter*>(row->GetAt(j))) {
				if (((SingleByteCharacter*)(row->GetAt(j)))->GetSingleByteContent() == '\t') {
					selectedAreaLength += textMetric.GetTextWidth(32) * 8;
					j += 8;
				}
				else {
					selectedAreaLength += textMetric.GetCurrentTextWidth(row, j);//한글자를 검사하는데 그게 텝이면 *8,좌표도+8 처리해주기.
					j++;
				}
			}
			else {
				selectedAreaLength += textMetric.GetCurrentTextWidth(row, j);//한글자를 검사하는데 그게 텝이면 *8,좌표도+8 처리해주기.
				j++;
			}
		}
		else  {
			i++;
			if (i<this->selector->GetNotePadForm()->notePad->GetLength()) {
				row = notePadForm->notePad->GetAt(i);
				alreadyRowCounted = false;
				if (dynamic_cast<DummyRow*>(row)) {
					if (((DummyRow*)(row))->GetIsTabErased() == true) {
						selectedAreaLength += textMetric.GetTextWidth(32) * 8;
					}
				}
				j = 0;
				alreadyRowCounted = false;
			}
		}
	}	
	while (rowCountInSelectedArea > 0) {
		i++;
		j = 0;
		rowCountInSelectedArea--;
	
	}
	this->selector->SetEndRowIndex(i);
	this->selector->SetEndColumnIndex(j);
}


void SelectModifier::ChangeLeftUpwardSelectedAreaStartPointAfterAction(Long rowCountInFirstToSelectedAreaStartPoint) {
	NotePadForm* notePadForm = this->selector->GetNotePadForm();
	TextMetric textMetric(notePadForm);
	Long lengthToSelectedArea = 0;
	Long i = 0;
	Long j = 0;
	Glyph* row = notePadForm->notePad->GetAt(i);
	bool alreadyRowCounted = false;

	while (lengthToSelectedArea < this->selector->GetLengthToSelectedArea()) {
		if (alreadyRowCounted == false && dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(i)) == 0) {
			rowCountInFirstToSelectedAreaStartPoint--;
			alreadyRowCounted = true;
		}
		if (row->GetLength() <= j) {
			i++;
			row = notePadForm->notePad->GetAt(i);
			if (dynamic_cast<DummyRow*>(row)) {
				if (((DummyRow*)(row))->GetIsTabErased() == true) {
					lengthToSelectedArea += textMetric.GetTextWidth(32) * 8;
				}
			}
			j = 0;
			alreadyRowCounted = false;
		}
		else {
			if (dynamic_cast<SingleByteCharacter*>(row->GetAt(j))) {
				if (((SingleByteCharacter*)(row->GetAt(j)))->GetSingleByteContent() == '\t') {
					lengthToSelectedArea += textMetric.GetTextWidth(32) * 8;
					j += 8;
				}
				else {
					lengthToSelectedArea += textMetric.GetCurrentTextWidth(row, j);//한글자를 검사하는데 그게 텝이면 *8,좌표도+8 처리해주기.
					j++;
				}
			}
			else {
				lengthToSelectedArea += textMetric.GetCurrentTextWidth(row, j);//한글자를 검사하는데 그게 텝이면 *8,좌표도+8 처리해주기.
				j++;
			}
		}
	}
	if (lengthToSelectedArea > 0) {
		if (rowCountInFirstToSelectedAreaStartPoint > 0) {
			while (rowCountInFirstToSelectedAreaStartPoint > 0) {
				i++;
				j = 0;
				rowCountInFirstToSelectedAreaStartPoint--;
			}
		}
		else if (rowCountInFirstToSelectedAreaStartPoint == 0 && row->GetLength() == j) {
			i++;
			j = 0;
		}
	}
	this->selector->SetEndRowIndex(i);
	this->selector->SetEndColumnIndex(j);
}


void SelectModifier::ChangeLeftUpwardSelectedAreaEndPointAfterAction(Long rowCountInSelectedArea) {
	NotePadForm* notePadForm = this->selector->GetNotePadForm();
	TextMetric textMetric(notePadForm);
	Long i = this->selector->GetEndRowIndex();
	Long j = this->selector->GetEndColumnIndex();
	Long selectedAreaLength = 0;
	Glyph* row = this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex());
	bool alreadyRowCounted = false;

	if (dynamic_cast<DummyRow*>(row) && ((DummyRow*)(row))->GetIsTabErased() == true &&
		this->selector->GetEndColumnIndex() == 0 && this->selector->GetIsFirstContentTab() == true) {
		selectedAreaLength += textMetric.GetTextWidth(32) * 8;
	}
	while (selectedAreaLength < this->selector->GetSelectedAreaLength()) {
		if (alreadyRowCounted == false && dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(i)) == 0) {
			rowCountInSelectedArea--;
			alreadyRowCounted = true;
		}
		if (row->GetLength() > j) {
			if (dynamic_cast<SingleByteCharacter*>(row->GetAt(j))) {
				if (((SingleByteCharacter*)(row->GetAt(j)))->GetSingleByteContent() == '\t') {
					selectedAreaLength += textMetric.GetTextWidth(32) * 8;
					j += 8;
				}
				else {
					selectedAreaLength += textMetric.GetCurrentTextWidth(row, j);//한글자를 검사하는데 그게 텝이면 *8,좌표도+8 처리해주기.
					j++;
				}
			}
			else {
				selectedAreaLength += textMetric.GetCurrentTextWidth(row, j);//한글자를 검사하는데 그게 텝이면 *8,좌표도+8 처리해주기.
				j++;
			}
		}
		else {
			i++;
			if (i < this->selector->GetNotePadForm()->notePad->GetLength()) {
				row = notePadForm->notePad->GetAt(i);
				alreadyRowCounted = false;
				if (dynamic_cast<DummyRow*>(row)) {
					if (((DummyRow*)(row))->GetIsTabErased() == true) {
						selectedAreaLength += textMetric.GetTextWidth(32) * 8;
					}
				}
				j = 0;
				alreadyRowCounted = false;
			}
		}
	}
	while (rowCountInSelectedArea > 0) {
		i++;
		j = 0;
		rowCountInSelectedArea--;

	}
	this->selector->SetOriginRowIndex(i);
	this->selector->SetOriginColumnIndex(j);
}

void SelectModifier::SetAbsoluteSelectionInformation() {
	SelectedAreaMetric selectedAreaMetric(this->selector);
	bool isRightDownWardSelectedArea = this->selector->IsRightDownWardSelectedArea();
	Long selectedAreaLength = 0;
	Long lengthToSelectedArea = 0;

	if (isRightDownWardSelectedArea == true) {
		this->selector->SetSelectedAreaLength(selectedAreaMetric.GetSelectedAreaLengthWhenRightDownwardSelected());
		this->selector->SetLengthToSelectedArea(selectedAreaMetric.GetLengthToSelectedAreaWhenRightDownwardSelected());

	}
	else {
		this->selector->SetSelectedAreaLength(selectedAreaMetric.GetSelectedAreaLengthWhenLeftUpwardSelected());
		this->selector->SetLengthToSelectedArea(selectedAreaMetric.GetLengthToSelectedAreaWhenLeftUpwardSelected());
	}
}


Long SelectModifier::CountRowInSelectedArea() {
	Long rowCount = 0;
	Long i = 0;
	
	bool isRightDownwardSelectedArea = this->selector->IsRightDownWardSelectedArea();

	if (isRightDownwardSelectedArea==true) {
		i = this->selector->GetOriginRowIndex();
		while (i <= this->selector->GetEndRowIndex()) {
			if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(i)) == 0) {
				rowCount++;
			}
			i++;
		}
	}
	else {
		i = this->selector->GetEndRowIndex();
		while (i <= this->selector->GetOriginRowIndex()) {
			if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(i)) == 0) {
				rowCount++;
			}
			i++;
		}
	}
	
	return rowCount;
}



Long SelectModifier::CountRowInFirstToSelectedAreaStartPoint() {
	Long rowCount = 0;
	Long i = 0;

	bool isRightDownwardSelectedArea = this->selector->IsRightDownWardSelectedArea();

	if (isRightDownwardSelectedArea == true) {
		while (i <=this->selector->GetOriginRowIndex()) {
			if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(i)) == 0) {
				rowCount++;
			}
			i++;
		}
#if 0;
		if (this->selector->GetOriginColumnIndex()==0) {
			if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex())) == 0) {
				rowCount--;
			}
		}
#endif 0;
	}
	else {
		
		while (i <= this->selector->GetEndRowIndex()) {
			if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(i)) == 0) {
				rowCount++;
			}
			i++;
		}
#if 0;
		if (this->selector->GetEndColumnIndex()== 0) {
			if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex())) == 0) {
				rowCount--;
			}
		}
#endif 0;
	}

	return rowCount;
}

bool SelectModifier::isFirstLineInSelectedAreaDummyRow(Long index) {

	bool isFirstLineInSelectedAreaDummyRow = false;
	
	if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(index))){
		isFirstLineInSelectedAreaDummyRow = true;
	}

	return isFirstLineInSelectedAreaDummyRow;
}