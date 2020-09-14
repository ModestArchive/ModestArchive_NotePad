//MouseTrackTextMetric.cpp

#include"MouseTrackTextMetric.h"
#include"NotePadForm.h"
#include"TextMetric.h"
#include"SingleByteCharacter.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"Font.h"
#include"NotePadMetric.h"

MouseTrackTextMetric::MouseTrackTextMetric(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}

MouseTrackTextMetric::~MouseTrackTextMetric() {

}


void MouseTrackTextMetric::TransferMouseCoordinateToNotePadLocation(UINT nFlags, CPoint point) {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long rowIndex = 0;
	Long rowLength = 0;
	Long columnIndex = 0;
	Long columnLength = 0;
	bool isLastRow = false;
	
	if (this->notePadForm->GetScrollController()->GetIsVScrollOn()==true) {
		while (rowIndex < this->notePadForm->notePad->GetLength() && 
			textMetric.GetY(rowIndex) + tm.tmHeight + 5 < this->notePadForm->GetScrollController()->GetVPosition() + point.y) {
			rowIndex++;
		}
		this->notePadForm->notePad->First();
		if (rowIndex < this->notePadForm->notePad->GetLength()) {
			
			Long x = 0;
			while (x<rowIndex) {
				this->notePadForm->notePad->Next();
				x++;
			}
			this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
			
		}
		else {
			
			Long x = 0;
			while (x < rowIndex-1) {
				this->notePadForm->notePad->Next();
				x++;
			}
			this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetLength() - 1);
				
		}
	}
	else {
		while (rowIndex < this->notePadForm->notePad->GetLength() && textMetric.GetY(rowIndex) + tm.tmHeight + 5 < point.y) {
			rowIndex++;
		}
		this->notePadForm->notePad->First();
		if (rowIndex < this->notePadForm->notePad->GetLength()) {
			Long x = 0;
			while (x < rowIndex) {
				this->notePadForm->notePad->Next();
				x++;
			}
			this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		}
		else {
			this->notePadForm->notePad->Last();
			this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		}
	} 
	
	if (this->notePadForm->GetScrollController()->GetIsHScrollOn() == true) {///////////////////////HScroll있을때 처리
		while (columnIndex <= this->notePadForm->row->GetLength() && textMetric.GetX(this->notePadForm->row, columnIndex) + tm.tmAveCharWidth / 4 <
																	    this->notePadForm->GetScrollController()->GetHPosition() +point.x ) {
			columnIndex++;
		}
		this->notePadForm->row->First();
		if (columnIndex > this->notePadForm->row->GetLength()) {
			Long i = 0;
			while (i < this->notePadForm->row->GetLength()) {
				this->notePadForm->row->Next();
				i++;
			}
			NotePadMetric notePadMetric(this->notePadForm);
			Long rowIndex=notePadMetric.GetLongestXRowIndex();
			if (rowIndex==this->notePadForm->notePad->GetCurrent()) {
				this->notePadForm->GetScrollController()->MoveHScrLast();
			}
		}
		else {
			if (columnIndex != 0) {
				if (columnIndex < this->notePadForm->row->GetLength()) {
					if (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(columnIndex))) {
						if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(columnIndex)))->GetSingleByteContent() == '\t') {
							Long tabCountBehindColumnIndex = 0;//columnIndex기준 뒤에있는 텝갯수
							Long tabCountFrontColumnIndex = 0;//columnIndex기준 앞에있는 텝갯수
							Long exploringIndex = columnIndex;
							while (exploringIndex < this->notePadForm->row->GetLength() &&
								dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(exploringIndex)) &&
								((SingleByteCharacter*)(this->notePadForm->row->GetAt(exploringIndex)))->GetSingleByteContent() == '\t') {
								tabCountBehindColumnIndex++;
								exploringIndex++;
							}
							exploringIndex = columnIndex - 1;
							while (exploringIndex >= 0 &&
								dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(exploringIndex)) &&
								((SingleByteCharacter*)(this->notePadForm->row->GetAt(exploringIndex)))->GetSingleByteContent() == '\t') {
								tabCountFrontColumnIndex++;
								exploringIndex--;
							}
							Long realtabCountBehindColumnIndex = tabCountBehindColumnIndex % 8;
							Long realtabCountFrontColumnIndex = tabCountFrontColumnIndex % 8;
							if (realtabCountBehindColumnIndex <= tabCountFrontColumnIndex) {
								columnIndex += realtabCountBehindColumnIndex;
							}
							else {
								columnIndex -= realtabCountFrontColumnIndex;
							}

						}
						else {//현재글자위치보다 한칸아래에있는 글자길이를 반띵해서 반띵한 길이보다 길면 현재위치고수,
							  //그게 아니라면 columnIndex-1 해준다.
							Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
							Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
							if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4 > point.x + this->notePadForm->GetScrollController()->GetHPosition()) {
								columnIndex--;
							}
							
						}
					}
					else {
						Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
						Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
						if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4 > point.x + this->notePadForm->GetScrollController()->GetHPosition()) {
							columnIndex--;
						}
						
					}
				}
				else {
					Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
					Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
					if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4  > point.x+ this->notePadForm->GetScrollController()->GetHPosition()) {
						columnIndex--;
					}
				}
			}
			Long j = 0;
			while (j < columnIndex) {
				this->notePadForm->row->Next();
				j++;
			}
		}
	}/////////////////////////////////////////////H스크롤 없을때 처리
	else {
		while (columnIndex<=this->notePadForm->row->GetLength() && textMetric.GetX(this->notePadForm->row,columnIndex)+ tm.tmAveCharWidth / 4 < point.x ) {
			columnIndex++;
		}
		this->notePadForm->row->First(); 
		if (columnIndex>this->notePadForm->row->GetLength()) {
			Long i = 0;
			while (i<this->notePadForm->row->GetLength()) {
				this->notePadForm->row->Next();
				i++;
			}
		}
		else {
			if (columnIndex!=0) {
				if (columnIndex < this->notePadForm->row->GetLength()) {
					if (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(columnIndex))) {
						if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(columnIndex)))->GetSingleByteContent() == '\t') {
							Long tabCountBehindColumnIndex = 0;//columnIndex기준 뒤에있는 텝갯수
							Long tabCountFrontColumnIndex = 0;//columnIndex기준 앞에있는 텝갯수
							Long exploringIndex = columnIndex;
							while (exploringIndex < this->notePadForm->row->GetLength() &&
								dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(exploringIndex)) &&
								((SingleByteCharacter*)(this->notePadForm->row->GetAt(exploringIndex)))->GetSingleByteContent() == '\t') {
								tabCountBehindColumnIndex++;
								exploringIndex++;
							}
							exploringIndex = columnIndex - 1;
							while (exploringIndex >= 0 &&
								dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(exploringIndex)) &&
								((SingleByteCharacter*)(this->notePadForm->row->GetAt(exploringIndex)))->GetSingleByteContent() == '\t') {
								tabCountFrontColumnIndex++;
								exploringIndex--;
							}
							Long realtabCountBehindColumnIndex = tabCountBehindColumnIndex % 8;
							Long realtabCountFrontColumnIndex = tabCountFrontColumnIndex % 8;
							if (realtabCountBehindColumnIndex <= realtabCountFrontColumnIndex) {
								columnIndex += realtabCountBehindColumnIndex;
							}
							else {
								columnIndex -= realtabCountFrontColumnIndex;
							}

						}
						else {//현재글자위치보다 한칸아래에있는 글자길이를 반띵해서 반띵한 길이보다 길면 현재위치고수,
							  //그게 아니라면 columnIndex-1 해준다.
							Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
							Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
							if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4 > point.x) {
								columnIndex--;
							}
						}
					}
					else {
						Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
						Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
						if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4 > point.x) {
							columnIndex--;
						}
					}
				}
				else {
					Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
					Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
					if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4 > point.x) {
						columnIndex--;
					}
				}
			}
			Long j = 0;
			while (j<columnIndex) {
				this->notePadForm->row->Next();
				j++;
			}
		}
	}
}


void  MouseTrackTextMetric::TransferMouseCoordinateToNotePadLocaitonWhenMouseMove(UINT nFlags, CPoint point) {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long rowIndex = 0;
	Long rowLength = 0;
	Long columnIndex = 0;
	Long columnLength = 0;
	bool isLastRow = false;


	if (this->notePadForm->GetScrollController()->GetIsVScrollOn() == true) {
		while (rowIndex < this->notePadForm->notePad->GetLength() && textMetric.GetY(rowIndex) + tm.tmHeight + 5 <
			this->notePadForm->GetScrollController()->GetVPosition() + point.y) {
			rowIndex++;
		}
		this->notePadForm->notePad->First();
		if (rowIndex < this->notePadForm->notePad->GetLength()) {

			while (this->notePadForm->notePad->GetCurrent() < rowIndex) {
				this->notePadForm->notePad->Next();
			}
			this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());

			if (textMetric.GetY(this->notePadForm->notePad->GetCurrent())+2*(tm.tmHeight+5)>this->notePadForm->GetCy()+ this->notePadForm->GetScrollController()->GetVPosition()) {
				this->notePadForm->GetScrollController()->MoveVScrNext();

			}
			
			if (textMetric.GetY(this->notePadForm->notePad->GetCurrent())  <this->notePadForm->GetScrollController()->GetVPosition()) {
				
				this->notePadForm->GetScrollController()->MoveVScrPrevious();
			}

		}
		else {
			while (this->notePadForm->notePad->GetCurrent()< this->notePadForm->notePad->GetLength()-1) {
				this->notePadForm->notePad->Next();
				
			}
			this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetLength() - 1);
		}
	}
	else {
		while (rowIndex < this->notePadForm->notePad->GetLength() && textMetric.GetY(rowIndex) + tm.tmHeight + 5 < point.y) {
			rowIndex++;
		}
		this->notePadForm->notePad->First();
		if (rowIndex < this->notePadForm->notePad->GetLength()) {
			Long x = 0;
			while (x < rowIndex) {
				this->notePadForm->notePad->Next();
				x++;
			}
			this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		}
		else {
			this->notePadForm->notePad->Last();
			this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		}
	}

	if (this->notePadForm->GetScrollController()->GetIsHScrollOn() == true) {///////////////////////HScroll있을때 처리
		while (columnIndex <= this->notePadForm->row->GetLength() && 
			   textMetric.GetX(this->notePadForm->row, columnIndex) + tm.tmAveCharWidth / 4 < this->notePadForm->GetScrollController()->GetHPosition() + point.x) {
			columnIndex++;
		}
		this->notePadForm->row->First();
		if (columnIndex > this->notePadForm->row->GetLength()) {
			Long i = 0;
			while (i < this->notePadForm->row->GetLength()) {
				this->notePadForm->row->Next();
				i++;
			}
			NotePadMetric notePadMetric(this->notePadForm);
			Long rowIndex = notePadMetric.GetLongestXRowIndex();
			if (rowIndex == this->notePadForm->notePad->GetCurrent()) {
				this->notePadForm->GetScrollController()->MoveHScrLast();
			}
			else {
				if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) + tm.tmAveCharWidth / 4
					< this->notePadForm->GetScrollController()->GetHPosition()) {//삭제할때이고, 스크롤영역보다 짧아서 안보이는상황

					while (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) + tm.tmAveCharWidth / 4
						< this->notePadForm->GetScrollController()->GetHPosition()) {
						this->notePadForm->GetScrollController()->MoveHScrPrevious();
					}
					while (this->notePadForm->GetScrollController()->GetHPosition()>0 && 
						   this->notePadForm->GetCx()/2+this->notePadForm->GetScrollController()->GetHPosition()> textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetCurrent()) + tm.tmAveCharWidth / 4) {
						this->notePadForm->GetScrollController()->MoveHScrPrevious();
					}
				}
			}
		}
		else {
			if (columnIndex != 0) {
				if (columnIndex < this->notePadForm->row->GetLength()) {
					if (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(columnIndex))) {
						if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(columnIndex)))->GetSingleByteContent() == '\t') {
							Long tabCountBehindColumnIndex = 0;//columnIndex기준 뒤에있는 텝갯수
							Long tabCountFrontColumnIndex = 0;//columnIndex기준 앞에있는 텝갯수
							Long exploringIndex = columnIndex;
							while (exploringIndex < this->notePadForm->row->GetLength() &&
								dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(exploringIndex)) &&
								((SingleByteCharacter*)(this->notePadForm->row->GetAt(exploringIndex)))->GetSingleByteContent() == '\t') {
								tabCountBehindColumnIndex++;
								exploringIndex++;
							}
							exploringIndex = columnIndex - 1;
							while (exploringIndex >= 0 &&
								dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(exploringIndex)) &&
								((SingleByteCharacter*)(this->notePadForm->row->GetAt(exploringIndex)))->GetSingleByteContent() == '\t') {
								tabCountFrontColumnIndex++;
								exploringIndex--;
							}
							Long realtabCountBehindColumnIndex = tabCountBehindColumnIndex % 8;
							Long realtabCountFrontColumnIndex = tabCountFrontColumnIndex % 8;
							if (realtabCountBehindColumnIndex <= realtabCountFrontColumnIndex) {
								columnIndex += realtabCountBehindColumnIndex;
							}
							else {
								columnIndex -= realtabCountFrontColumnIndex;
							}
							if (textMetric.GetX(this->notePadForm->row,columnIndex)+tm.tmAveCharWidth/4 >
								this->notePadForm->GetCx()+this->notePadForm->GetScrollController()->GetHPosition()- 3*(tm.tmAveCharWidth / 2)) {
								this->notePadForm->GetScrollController()->MoveHScrNext();
								this->notePadForm->GetScrollController()->MoveHScrNext();
								this->notePadForm->GetScrollController()->MoveHScrNext();
							}
							else if (point.x < 30) {
								this->notePadForm->GetScrollController()->MoveHScrPrevious();
								this->notePadForm->GetScrollController()->MoveHScrPrevious();
								this->notePadForm->GetScrollController()->MoveHScrPrevious();
							}

						}
						else {//현재글자위치보다 한칸아래에있는 글자길이를 반띵해서 반띵한 길이보다 길면 현재위치고수,
							  //그게 아니라면 columnIndex-1 해준다.
							Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
							Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
							if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4 > point.x + this->notePadForm->GetScrollController()->GetHPosition()) {
								columnIndex--;
							}
							if (textMetric.GetX(this->notePadForm->row, columnIndex) + tm.tmAveCharWidth / 4 > this->notePadForm->GetScrollController()->GetHPosition() + this->notePadForm->GetCx() - 3 * (tm.tmAveCharWidth / 2)) {
								this->notePadForm->GetScrollController()->MoveHScrNext();
								this->notePadForm->GetScrollController()->MoveHScrNext();
								this->notePadForm->GetScrollController()->MoveHScrNext();

							}
							else if (point.x < 30) {
								this->notePadForm->GetScrollController()->MoveHScrPrevious();
								this->notePadForm->GetScrollController()->MoveHScrPrevious();
								this->notePadForm->GetScrollController()->MoveHScrPrevious();

							}
						}
					}
					else {
						Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
						Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
						if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4 > point.x + this->notePadForm->GetScrollController()->GetHPosition()) {
							columnIndex--;
						}
						if (textMetric.GetX(this->notePadForm->row, columnIndex) + tm.tmAveCharWidth / 4 > this->notePadForm->GetScrollController()->GetHPosition() + this->notePadForm->GetCx() - 3 * (tm.tmAveCharWidth / 2)) {
							this->notePadForm->GetScrollController()->MoveHScrNext();
							this->notePadForm->GetScrollController()->MoveHScrNext();
							this->notePadForm->GetScrollController()->MoveHScrNext();

						}
						else if (point.x < 30) {
							this->notePadForm->GetScrollController()->MoveHScrPrevious();
							this->notePadForm->GetScrollController()->MoveHScrPrevious();
							this->notePadForm->GetScrollController()->MoveHScrPrevious();

						}

					}
				}
				else {
					Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
					Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
					if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4 > point.x + this->notePadForm->GetScrollController()->GetHPosition()) {
						columnIndex--;
					}
					if (textMetric.GetX(this->notePadForm->row, columnIndex) + tm.tmAveCharWidth / 4 > this->notePadForm->GetScrollController()->GetHPosition() + this->notePadForm->GetCx() - 3 * (tm.tmAveCharWidth / 2)) {
						this->notePadForm->GetScrollController()->MoveHScrNext();
						this->notePadForm->GetScrollController()->MoveHScrNext();
						this->notePadForm->GetScrollController()->MoveHScrNext();

					}
					else if (point.x < 30) {
						this->notePadForm->GetScrollController()->MoveHScrPrevious();
						this->notePadForm->GetScrollController()->MoveHScrPrevious();
						this->notePadForm->GetScrollController()->MoveHScrPrevious();

					}
					
				}
			}
			Long j = 0;
			while (j < columnIndex) {
				this->notePadForm->row->Next();
				j++;
			}
		}
	}/////////////////////////////////////////////H스크롤 없을때 처리
	else {
		while (columnIndex <= this->notePadForm->row->GetLength() && textMetric.GetX(this->notePadForm->row, columnIndex) + tm.tmAveCharWidth / 4 < point.x) {
			columnIndex++;
		}
		this->notePadForm->row->First();
		if (columnIndex > this->notePadForm->row->GetLength()) {
			Long i = 0;
			while (i < this->notePadForm->row->GetLength()) {
				this->notePadForm->row->Next();
				i++;
			}
		}
		else {
			if (columnIndex != 0) {
				if (columnIndex < this->notePadForm->row->GetLength()) {
					if (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(columnIndex))) {
						if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(columnIndex)))->GetSingleByteContent() == '\t') {
							Long tabCountBehindColumnIndex = 0;//columnIndex기준 뒤에있는 텝갯수
							Long tabCountFrontColumnIndex = 0;//columnIndex기준 앞에있는 텝갯수
							Long exploringIndex = columnIndex;
							while (exploringIndex < this->notePadForm->row->GetLength() &&
								dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(exploringIndex)) &&
								((SingleByteCharacter*)(this->notePadForm->row->GetAt(exploringIndex)))->GetSingleByteContent() == '\t') {
								tabCountBehindColumnIndex++;
								exploringIndex++;
							}
							exploringIndex = columnIndex - 1;
							while (exploringIndex >= 0 &&
								dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(exploringIndex)) &&
								((SingleByteCharacter*)(this->notePadForm->row->GetAt(exploringIndex)))->GetSingleByteContent() == '\t') {
								tabCountFrontColumnIndex++;
								exploringIndex--;
							}
							Long realtabCountBehindColumnIndex = tabCountBehindColumnIndex % 8;
							Long realtabCountFrontColumnIndex = tabCountFrontColumnIndex % 8;
							if (realtabCountBehindColumnIndex <= realtabCountFrontColumnIndex) {
								columnIndex += realtabCountBehindColumnIndex;
							}
							else {
								columnIndex -= realtabCountFrontColumnIndex;
							}

						}
						else {//현재글자위치보다 한칸아래에있는 글자길이를 반띵해서 반띵한 길이보다 길면 현재위치고수,
							  //그게 아니라면 columnIndex-1 해준다.
							Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
							Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
							if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4 > point.x) {
								columnIndex--;
							}
						}
					}
					else {
						Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
						Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
						if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4 > point.x) {
							columnIndex--;
						}
					}
				}
				else {
					Long lengthToBeforeChar = textMetric.GetX(this->notePadForm->row, columnIndex - 1);
					Long HalfOfbeforeCharWidth = textMetric.GetCurrentTextWidth(this->notePadForm->row, columnIndex - 1) / 2;
					if (lengthToBeforeChar + HalfOfbeforeCharWidth + tm.tmAveCharWidth / 4 > point.x) {
						columnIndex--;
					}
				}
			}
			Long j = 0;
			while (j < columnIndex) {
				this->notePadForm->row->Next();
				j++;
			}
		}
	}
}

#if 0;
if (textMetric.GetY(rowIndex) + 2 * (tm.tmHeight + 5) > this->notePadForm->GetScrollController()->GetVPosition() + this->notePadForm->GetCy()) {
	this->notePadForm->GetScrollController()->MoveVScrNext();

}
#endif 0;