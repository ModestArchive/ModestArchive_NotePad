//NotePadModifier.cpp
#include"NotePadModifier.h"
#include"TextMetric.h"
#include"NotePadMetric.h"
#include"Font.h"
#include"DummyRow.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"SingleByteCharacter.h"
#include"GlyphFactory.h"


NotePadModifier::NotePadModifier(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}


NotePadModifier::~NotePadModifier() {

}


void NotePadModifier::Combine() {

	this->notePadForm->notePad->First();
	Glyph* row= this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
	row->Last();
	this->notePadForm->notePad->Next();
	Long i = 0;
	while (this->notePadForm->notePad->GetCurrent() < this->notePadForm->notePad->GetLength()) {
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		if (dynamic_cast<DummyRow*>(this->notePadForm->row)) {
			if(((DummyRow*)(this->notePadForm->row))->GetIsTabErased() == true) {
				i = 0;
				while (i<8) {
					GlyphFactory glyphFactory;
					char tab[2];
					tab[0] = '\t';
					tab[1] = '\0';
					Glyph* glyph = glyphFactory.MakeGlyph(tab);
					row->Add(glyph);
					i++;
				}
			}
			i = 0;
			while (i<this->notePadForm->row->GetLength()) {
				row->Add(this->notePadForm->row->GetAt(i)->Clone());
				i++;
			}
			this->notePadForm->notePad->Remove(this->notePadForm->notePad->GetCurrent());	
		}
		else {
			row = this->notePadForm->row;
		}
		this->notePadForm->notePad->Next();
	}
	this->notePadForm->notePad->First();
	this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
	this->notePadForm->row->First();
}

void NotePadModifier::Split() {//한방에 생각하지 말자!!! 논리적으로 따져서 제일 우선적으로 할것먼저하고 그다음 그다음 진행하자~!~!~!깨달음@@@
	
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	this->notePadForm->notePad->First();
	
	while (this->notePadForm->notePad->GetCurrent()<this->notePadForm->notePad->GetLength()) {
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->Last();
		if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength())+tm.tmAveCharWidth/4 > this->notePadForm->GetCx()-tm.tmAveCharWidth/2) {
			Glyph* dummyRow = new DummyRow();
			if (this->notePadForm->notePad->GetCurrent() >= this->notePadForm->notePad->GetLength() - 1) {
				this->notePadForm->notePad->Add(dummyRow);
			}
			else {
				this->notePadForm->notePad->Put(this->notePadForm->notePad->GetCurrent() + 1, dummyRow);
			}
			this->notePadForm->notePad->Previous();
			Long firstColumnIndexOverClientArea=notePadMetric.GetFirstColumnIndexOverClientArea(this->notePadForm->row, this->notePadForm->GetCx());
			while (firstColumnIndexOverClientArea < this->notePadForm->row->GetLength()) {
				dummyRow->Add(this->notePadForm->row->GetAt(firstColumnIndexOverClientArea)->Clone());
				this->notePadForm->row->Remove(firstColumnIndexOverClientArea);
			}
			this->notePadForm->row->Last();
			dummyRow->First();
			
			if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent()-1)))->GetSingleByteContent() == '\t' &&
			    ((SingleByteCharacter*)(dummyRow->GetAt(dummyRow->GetCurrent())))->GetSingleByteContent() == '\t') {

				Long chainTabCount = 0;
				Long checkPoint = this->notePadForm->row->GetCurrent()-1;
				while (checkPoint >= 0 &&
					   ((SingleByteCharacter*)(this->notePadForm->row->GetAt(checkPoint)))->GetSingleByteContent() == '\t') {
					checkPoint--;
					chainTabCount++;
				}
				Long erasedTabCount = 0;
				Long currentRowTabCountBreakPoint = chainTabCount % 8;
				Long k = 0;
				while (k < currentRowTabCountBreakPoint && this->notePadForm->row->GetCurrent()-1>=0 &&
					    ((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() - 1)))->GetSingleByteContent() == '\t') {
					this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent() - 1);
					k++;
				}
				Long i = 0;
				while (/*dummyRow->GetCurrent()<dummyRow->GetLength()&&((SingleByteCharacter*)(dummyRow->GetAt(dummyRow->GetCurrent())))->GetSingleByteContent() == '\t'*/
					    i<8-currentRowTabCountBreakPoint) {
					dummyRow->Remove(dummyRow->GetCurrent());
					dummyRow->Next();
					i++;
				}
				((DummyRow*)(dummyRow))->SetIsSubjectedHyphenationRuleTrue();
				((DummyRow*)(dummyRow))->SetIsTabErasedTrue();
			}
	        else if (((SingleByteCharacter*)(dummyRow->GetAt(dummyRow->GetCurrent())))->GetSingleByteContent() == '\t') {
				Long i = 0;
				while (/*((SingleByteCharacter*)(dummyRow->GetAt(dummyRow->GetCurrent())))->GetSingleByteContent() == '\t'*/
					   i<8 ) {
					dummyRow->Remove(dummyRow->GetCurrent());
					dummyRow->Next();
					i++;
				}
				((DummyRow*)(dummyRow))->SetIsSubjectedHyphenationRuleTrue();
				((DummyRow*)(dummyRow))->SetIsTabErasedTrue();
			}
		}
		this->notePadForm->notePad->Next();
	}
	this->notePadForm->notePad->First();
	this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
	this->notePadForm->row->First();
}


void NotePadModifier::SplitForPrinter(Long viewerPortHorzOrg,Long splitBoundary) {
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	
	this->notePadForm->notePad->First();

	while (this->notePadForm->notePad->GetCurrent() < this->notePadForm->notePad->GetLength()) {
		this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
		this->notePadForm->row->Last();
		if (textMetric.GetX(this->notePadForm->row, this->notePadForm->row->GetLength())+viewerPortHorzOrg> splitBoundary ) {
			Glyph* dummyRow = new DummyRow();
			if (this->notePadForm->notePad->GetCurrent() >= this->notePadForm->notePad->GetLength() - 1) {
				this->notePadForm->notePad->Add(dummyRow);
			}
			else {
				this->notePadForm->notePad->Put(this->notePadForm->notePad->GetCurrent() + 1, dummyRow);
			}
			this->notePadForm->notePad->Previous();
			Long firstColumnIndexOverClientArea = notePadMetric.GetFirstColumnIndexOverClientAreaForPrint(this->notePadForm->row, viewerPortHorzOrg, splitBoundary);
			while (firstColumnIndexOverClientArea < this->notePadForm->row->GetLength()) {
				dummyRow->Add(this->notePadForm->row->GetAt(firstColumnIndexOverClientArea)->Clone());
				this->notePadForm->row->Remove(firstColumnIndexOverClientArea);
			}
			this->notePadForm->row->Last();
			dummyRow->First();

			if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() - 1)))->GetSingleByteContent() == '\t' &&
				((SingleByteCharacter*)(dummyRow->GetAt(dummyRow->GetCurrent())))->GetSingleByteContent() == '\t') {

				Long erasedTabCount = 0;
				while (this->notePadForm->row->GetCurrent() - 1 >= 0 && ((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() - 1)))->GetSingleByteContent() == '\t') {
					this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent() - 1);
					erasedTabCount++;
				}
				Long i = 0;
				while (/*dummyRow->GetCurrent()<dummyRow->GetLength()&&((SingleByteCharacter*)(dummyRow->GetAt(dummyRow->GetCurrent())))->GetSingleByteContent() == '\t'*/
					i < 8 - erasedTabCount) {
					dummyRow->Remove(dummyRow->GetCurrent());
					dummyRow->Next();
					i++;
				}
				((DummyRow*)(dummyRow))->SetIsSubjectedHyphenationRuleTrue();
				((DummyRow*)(dummyRow))->SetIsTabErasedTrue();
			}
			else if (((SingleByteCharacter*)(dummyRow->GetAt(dummyRow->GetCurrent())))->GetSingleByteContent() == '\t') {
				Long i = 0;
				while (/*((SingleByteCharacter*)(dummyRow->GetAt(dummyRow->GetCurrent())))->GetSingleByteContent() == '\t'*/
					i < 8) {
					dummyRow->Remove(dummyRow->GetCurrent());
					dummyRow->Next();
					i++;
				}
				((DummyRow*)(dummyRow))->SetIsSubjectedHyphenationRuleTrue();
				((DummyRow*)(dummyRow))->SetIsTabErasedTrue();
			}
		}
		this->notePadForm->notePad->Next();
	}
	this->notePadForm->notePad->First();
	this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
	this->notePadForm->row->First();
}

Long NotePadModifier::CountRowFromStartToCurrent() {
	Long rowCount = 0;
	Long i = 0;

	while (i<=this->notePadForm->notePad->GetCurrent()) {
		if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(i))==0) {
			rowCount++;
		}
		i++;
	}
	return rowCount;
}


Long NotePadModifier::CountRowFromStartToDesignatedRowIndex(Long designatedRowIndex) {
	Long rowCount = 0;
	Long i = 0;

	while (i <= designatedRowIndex) {
		if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(i)) == 0) {
			rowCount++;
		}
		i++;
	}
	return rowCount;
}