//SelectedAreaMetric.cpp
#include"SelectedAreaMetric.h"
#include"Glyph.h"
#include"SingleByteCharacter.h"
#include"DummyRow.h"
#include"NotePadForm.h"
#include"TextMetric.h"
#include"Selector.h"

SelectedAreaMetric::SelectedAreaMetric(Selector* selector) {
	this->selector = selector;
}


SelectedAreaMetric::~SelectedAreaMetric() {

}


Long SelectedAreaMetric::GetSelectedAreaLengthWhenRightDownwardSelected() {
	TextMetric textMetric(this->selector->GetNotePadForm());
	bool isRightDownwardSelected = false;
	Long lengthToEndIndex = 0;
	Long lengthToOriginIndex = 0;
	Long selectedAreaLength = 0;
	
	Long i = this->selector->GetEndRowIndex() - this->selector->GetOriginRowIndex() + 1;
	Long j = 0;
	while (j < i) {
		if (i - 1 == 0) {
			lengthToEndIndex = textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex()), this->selector->GetEndColumnIndex());
			lengthToOriginIndex = textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex()), this->selector->GetOriginColumnIndex());
			selectedAreaLength = lengthToEndIndex - lengthToOriginIndex;
			if (dynamic_cast<SingleByteCharacter*>(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex())->GetAt(this->selector->GetOriginColumnIndex()))) {
				if (((SingleByteCharacter*)(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex())->GetAt(this->selector->GetOriginColumnIndex())))->GetSingleByteContent() == '\t') {
					this->selector->SetIsFirstContentTab(true);	
				}
			}	
		}
		else {
			if (j == 0) {
				selectedAreaLength += textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex()), this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex())->GetLength()) 
									  -textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex()), this->selector->GetOriginColumnIndex());
				if (this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex())->GetLength()>0) {
					if (dynamic_cast<SingleByteCharacter*>(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex())->GetAt(this->selector->GetOriginColumnIndex()))) {
						if (((SingleByteCharacter*)(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex())->GetAt(this->selector->GetOriginColumnIndex())))->GetSingleByteContent() == '\t') {
							this->selector->SetIsFirstContentTab(true);
						}
					}
				}
			}
			else if (j == i - 1) {
				selectedAreaLength += textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex()), this->selector->GetEndColumnIndex());
				if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex()))) {
					if (((DummyRow*)(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex())))->GetIsTabErased() == true) {
						selectedAreaLength += textMetric.GetTextWidth(32) * 8;
					}
				}
			}
			else {
				selectedAreaLength += textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex() + j), this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex() + j)->GetLength());
				if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex() + j))) {
					if (((DummyRow*)(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex() + j)))->GetIsTabErased() == true) {
						selectedAreaLength += textMetric.GetTextWidth(32) * 8;
					}
				}
			}
		}
		j++;
	}
	return selectedAreaLength;
}


Long SelectedAreaMetric::GetSelectedAreaLengthWhenLeftUpwardSelected() {
	TextMetric textMetric(this->selector->GetNotePadForm());
	bool isRightDownwardSelected = false;
	Long lengthToEndIndex = 0;
	Long lengthToOriginIndex = 0;
	Long selectedAreaLength = 0;
	
	Long i = this->selector->GetOriginRowIndex() - this->selector->GetEndRowIndex() + 1;
	Long j = 0;
	while (j < i) {
		if (i - 1 == 0) {
			lengthToEndIndex = textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex()), this->selector->GetOriginColumnIndex());
			lengthToOriginIndex = textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex()), this->selector->GetEndColumnIndex());
			selectedAreaLength = lengthToEndIndex - lengthToOriginIndex;
			if (dynamic_cast<SingleByteCharacter*>(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex())->GetAt(this->selector->GetEndColumnIndex()))) {
				if (((SingleByteCharacter*)(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex())->GetAt(this->selector->GetEndColumnIndex())))->GetSingleByteContent() == '\t') {
					this->selector->SetIsFirstContentTab(true);
				}
			}
		}
		else {
			if (j == 0) {
				selectedAreaLength += textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex()), this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex())->GetLength())
									  -textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex()), this->selector->GetEndColumnIndex());

				if (this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex())->GetLength() > 0) {
					if (dynamic_cast<SingleByteCharacter*>(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex())->GetAt(this->selector->GetEndColumnIndex()))) {
						if (((SingleByteCharacter*)(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex())->GetAt(this->selector->GetEndColumnIndex())))->GetSingleByteContent() == '\t') {
							this->selector->SetIsFirstContentTab(true);
						}
					}
				}
			}
			else if (j == i - 1) {
				selectedAreaLength += textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex()), this->selector->GetOriginColumnIndex());
				if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex()))) {
					if (((DummyRow*)(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex())))->GetIsTabErased() == true) {
						selectedAreaLength += textMetric.GetTextWidth(32) * 8;
					}
				}
			}
			else {
				selectedAreaLength += textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex() + j), this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex() + j)->GetLength());
				if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex() + j))) {
					if (((DummyRow*)(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex() + j)))->GetIsTabErased() == true) {
						selectedAreaLength += textMetric.GetTextWidth(32) * 8;
					}
				}
			}
		}
		j++;
	}
	return selectedAreaLength;
}


Long SelectedAreaMetric::GetLengthToSelectedAreaWhenRightDownwardSelected() {
	TextMetric textMetric(this->selector->GetNotePadForm());
	Long lengthToSelectedAreaLength = 0;
	
	Long i = this->selector->GetOriginRowIndex()+ 1;
	Long j = 0;
	while (j < i) {
		if (i - 1 == 0) {
			lengthToSelectedAreaLength = textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex()), this->selector->GetOriginColumnIndex());			
		}
		else {
			if (j == i - 1) {
				lengthToSelectedAreaLength += textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetOriginRowIndex()), this->selector->GetOriginColumnIndex());
				if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(j))) {
					if (((DummyRow*)(this->selector->GetNotePadForm()->notePad->GetAt(j)))->GetIsTabErased() == true) {
							lengthToSelectedAreaLength += textMetric.GetTextWidth(32) * 8;
					}
				}
			}
			else {
				lengthToSelectedAreaLength += textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(j), this->selector->GetNotePadForm()->notePad->GetAt(j)->GetLength());
				if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(j))) {
					if (((DummyRow*)(this->selector->GetNotePadForm()->notePad->GetAt(j)))->GetIsTabErased() == true) {
							
						lengthToSelectedAreaLength += textMetric.GetTextWidth(32) * 8;
					}
				}
			}
		}
		j++;
	}
	return lengthToSelectedAreaLength;
}


Long SelectedAreaMetric::GetLengthToSelectedAreaWhenLeftUpwardSelected() {
	TextMetric textMetric(this->selector->GetNotePadForm());
	Long lengthToSelectedAreaLength = 0;

	Long i = this->selector->GetEndRowIndex() + 1;
	Long j = 0;
	while (j < i) {
		if (i - 1 == 0) {
			lengthToSelectedAreaLength = textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex()), this->selector->GetEndColumnIndex());
		}
		else {
			if (j == i - 1) {
				lengthToSelectedAreaLength += textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(this->selector->GetEndRowIndex()), this->selector->GetEndColumnIndex());
				if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(j))) {
					if (((DummyRow*)(this->selector->GetNotePadForm()->notePad->GetAt(j)))->GetIsTabErased() == true) {
						lengthToSelectedAreaLength += textMetric.GetTextWidth(32) * 8;
					}
				}
			}	
			else {
				lengthToSelectedAreaLength += textMetric.GetX(this->selector->GetNotePadForm()->notePad->GetAt(j), this->selector->GetNotePadForm()->notePad->GetAt(j)->GetLength());
				if (dynamic_cast<DummyRow*>(this->selector->GetNotePadForm()->notePad->GetAt(j))) {
					if (((DummyRow*)(this->selector->GetNotePadForm()->notePad->GetAt(j)))->GetIsTabErased() == true) {
						lengthToSelectedAreaLength += textMetric.GetTextWidth(32) * 8;
					}
				}
			}
		}
		j++;
	}
	return lengthToSelectedAreaLength;
}
