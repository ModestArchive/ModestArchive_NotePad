//NotePadMaker.cpp

#include"NotePadMaker.h"
#include"GlyphFactory.h"
#include"Glyph.h"
#include"GlyphFactory.h"
#include"SingleByteCharacter.h"
#include"Font.h"
#include"TextMetric.h"
#include"NotePadMetric.h"
#include"ScrollController.h"
#include"NotePadModifier.h"
#include"DummyRow.h"
#include"NotePadMementoMaker.h"
#include"ConstraintSolver.h"
#include"ConstraintSolverMemento.h"
#include"NotePadState.h"
#include"NotePadRestorer.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
#include"HistoryReconstructor.h"
#include"PasteSupervisor.h"



NotePadMaker::NotePadMaker(NotePadForm* notePadForm ) {
	this->notePadForm = notePadForm;
}


NotePadMaker::~NotePadMaker() {

}


void NotePadMaker::MakeNotePad(string contents) {
	
	char(*buffer) = 0;
	buffer = (char*)contents.c_str();
	GlyphFactory glyphFactory;
	Glyph* glyph = 0;
	Long i = 0;
	
	this->notePadForm->notePad = glyphFactory.MakeGlyph((char*)(""));
	this->notePadForm->row = glyphFactory.MakeGlyph((char*)("\r\n"));
	this->notePadForm->notePad->Add(this->notePadForm->row);

	while (buffer[i] != '\0') {
		if (buffer[i] == '\n') {
			TCHAR rowBuffer[3];
			rowBuffer[0] = '\r';
			rowBuffer[1] = '\n';
			rowBuffer[2] = '\0';

			glyph = glyphFactory.MakeGlyph(rowBuffer);
			this->notePadForm->row = glyph;
			this->notePadForm->notePad->Add(this->notePadForm->row);
			i ++;
		}
		else if (buffer[i] & 0x80) {
			TCHAR rowBuffer[3];
			rowBuffer[0] = buffer[i];
			rowBuffer[1] = buffer[i + 1];
			rowBuffer[2] = '\0';

			glyph = glyphFactory.MakeGlyph(rowBuffer);
			this->notePadForm->row->Add(glyph);
			i += 2;
		}
		else {
			TCHAR charBuffer[2];
			charBuffer[0] = buffer[i];
			charBuffer[1] = '\0';

			glyph = glyphFactory.MakeGlyph(charBuffer);
			this->notePadForm->row->Add(glyph);
			i++;
		}
	}
	this->notePadForm->notePad->First();
	this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
	this->notePadForm->row->First();
}


void NotePadMaker::PlusRowInNotePad() {
	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();
	GlyphFactory glyphFactory;
	Glyph* glyph;
	TCHAR buffer[3];
	
	buffer[0] = '\r';
	buffer[1] = '\n';
	buffer[2] = '\0';
	glyph = glyphFactory.MakeGlyph(buffer);

	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent()!= this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	notePadRestorer->GetNotePadHistory()->MoveLastHistory();
	constraintSolverMemento=notePadMementoMaker.MakeMemento(true, false,false,0);
	notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

	//히스토리에 추가해주기 추가할때는 히스토리를 맨앞에다가 위치 옮겨놓고 추가해주기
	
	if (this->notePadForm->notePad->GetCurrent() >= this->notePadForm->notePad->GetLength() - 1) {
		this->notePadForm->notePad->Add(glyph);
	}
	else {
		this->notePadForm->notePad->Put(this->notePadForm->notePad->GetCurrent() + 1, glyph);
	}
	this->notePadForm->row = glyph;
	
	this->notePadForm->GetScrollController()->SetHPos(0);
}


void NotePadMaker::WriteTabInRow(char(*contents)) {
	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();

	GlyphFactory glyphFactory;
	Glyph* glyph;
	
	Long hPosition = 0;
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	glyph = glyphFactory.MakeGlyph(contents);
	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	notePadRestorer->GetNotePadHistory()->MoveLastHistory();
	constraintSolverMemento = notePadMementoMaker.MakeMemento(true,false, false, glyph->Clone());
	notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

	Long i = 0;
	while (i < 8) {
		
		glyph = glyphFactory.MakeGlyph(contents);
		
		if (this->notePadForm->row->GetCurrent() >= this->notePadForm->row->GetLength()) {
			this->notePadForm->row->Add(glyph);
		}
		else {
			this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
		}
		i++;
	}
}

void NotePadMaker::WriteSingleByteCharacterInRow(char(*contents)) {
	
		NotePadMementoMaker notePadMementoMaker(this->notePadForm);
		ConstraintSolverMemento* constraintSolverMemento = 0;
		NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();

		GlyphFactory glyphFactory;
		Glyph* glyph;

		Long hPosition = 0;
		TextMetric textMetric(this->notePadForm);
		NotePadMetric notePadMetric(this->notePadForm);
		Font font(this->notePadForm);
		TEXTMETRIC tm = { 0, };
		tm = font.CalculateFontMetric();

		glyph = glyphFactory.MakeGlyph(contents);

		if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
			HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
			historyReconstructor.ReconstructHistory();
		}
		notePadRestorer->GetNotePadHistory()->MoveLastHistory();
		constraintSolverMemento = notePadMementoMaker.MakeMemento(true, false, false, glyph->Clone());
		notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

		if (this->notePadForm->row->GetCurrent() == this->notePadForm->row->GetLength()) {
			this->notePadForm->row->Add(glyph);
		}
		else {
			this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
		}
	
}

void NotePadMaker::WriteDoubleByteCharacterInRow(char(*contents)) {
	if (!(GetKeyState(VK_CONTROL) & 0x8000)) {
	
		GlyphFactory glyphFactory;
		Glyph* glyph = 0;
		TextMetric textMetric(this->notePadForm);
		NotePadMetric notePadMetric(this->notePadForm);
		Font font(this->notePadForm);
		TEXTMETRIC tm = { 0, };
		tm = font.CalculateFontMetric();
		Long hPosition = 0;

		NotePadMementoMaker notePadMementoMaker(this->notePadForm);
		ConstraintSolverMemento* constraintSolverMemento = 0;
		NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();
		if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
			HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
			historyReconstructor.ReconstructHistory();
		}
		glyph = glyphFactory.MakeGlyph(contents);
	
		if (this->notePadForm->GetIsComposition() == true) {
			this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent() - 1);
			this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->RemoveHistory(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength() - 1);
		}
		if (contents[0] != '\0') {//백스페이스 입력시 처리
			notePadRestorer->GetNotePadHistory()->MoveLastHistory();
			constraintSolverMemento = notePadMementoMaker.MakeMemento(true,false, false, glyph->Clone());
			notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
		}
		if (this->notePadForm->row->GetCurrent() == this->notePadForm->row->GetLength()) {
			this->notePadForm->row->Add(glyph);
		}
		else {
			this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
		}
		
		if (contents[0] == '\0') {//백스페이스 입력시 처리
			this->notePadForm->SetIsComposition(false);
			this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent() - 1);
		}
		else {
			this->notePadForm->SetIsComposition(true);
		}
	
	}
}


void NotePadMaker::WriteCompleteDoubleByteCharacterInRow(char(*contents)) {
	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();

	Glyph* glyph = 0;
	GlyphFactory glyphFactory;
	glyph = glyphFactory.MakeGlyph(contents);
	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent() - 1);
	this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->RemoveHistory(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength() - 1);

	notePadRestorer->GetNotePadHistory()->MoveLastHistory();
	constraintSolverMemento = notePadMementoMaker.MakeMemento(true, false, false, glyph->Clone());
	notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

	if (this->notePadForm->row->GetCurrent() == this->notePadForm->row->GetLength()) {
		this->notePadForm->row->Add(glyph);
	}
	else {
		this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
	}
}

void NotePadMaker::EraseCurrentRowInNotePad() {
	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();

	TextMetric textMetric(this->notePadForm);
	GlyphFactory glyphFactory;
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	//여기서부터 콤바인을 해준다 
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

	Long i = 0;
	Glyph* previousRow = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent() - 1);
	Long previousRowLength = previousRow->GetLength();
	
	while (i < this->notePadForm->row->GetLength()) {
		previousRow->Add(this->notePadForm->row->GetAt(i)->Clone());
		i++;
	}
	i = 0;
	previousRow->First();
	while (i < previousRowLength) {
		previousRow->Next();
		i++;
	}
	this->notePadForm->notePad->Remove(this->notePadForm->notePad->GetCurrent());
	this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());

	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	notePadRestorer->GetNotePadHistory()->MoveLastHistory();
	constraintSolverMemento = notePadMementoMaker.MakeMemento(false, true, true, 0);
	notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
}


void NotePadMaker::EraseNextRowInNotePad() {
	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();

	TextMetric textMetric(this->notePadForm);
	GlyphFactory glyphFactory;
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();


	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	notePadRestorer->GetNotePadHistory()->MoveLastHistory();
	constraintSolverMemento = notePadMementoMaker.MakeMemento(false, true,false,0);
	notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

	Long i = 0;
	Glyph* nextRow = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent() + 1);
	Long index = nextRow->GetLength();
	Long previousIndex = this->notePadForm->row->GetCurrent();
	
	while (i < nextRow->GetLength()) {
		this->notePadForm->row->Add(nextRow->GetAt(i)->Clone());
		i++;
	}
	i = 0;
	this->notePadForm->row->First();
	while (i < previousIndex) {
		this->notePadForm->row->Next();
		i++;
	}
	this->notePadForm->notePad->Remove(this->notePadForm->notePad->GetCurrent() + 1);
	this->notePadForm->notePad->Next();
}


void NotePadMaker::ErasePreviousCharacterInRow() {
	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();

	TextMetric textMetric(this->notePadForm);
	GlyphFactory glyphFactory;

	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	//여기서부터 콤바인을 해준다 
	NotePadMetric notePadMetric(this->notePadForm);
	NotePadModifier notePadModifier(this->notePadForm);
	CoordinateCalculator coordinateCalculator(this->notePadForm);
	NotePadIndicator notePadIndicator(this->notePadForm);

	Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
	Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
	notePadModifier.Combine();
	CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
	notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
	
	Glyph* clone = this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent()-1)->Clone();
	if (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() - 1))) {
		if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() - 1)))->GetSingleByteContent()=='\t'){
			Long count = 0;
			while (count < 8 && ((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() - 1)))->GetSingleByteContent() == '\t') {
				this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent() - 1);
				count++;
			}
		}
		else {
			this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent() - 1);
		}
	}
	else {
		this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent() - 1);
	}
	
	

	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	notePadRestorer->GetNotePadHistory()->MoveLastHistory();
	constraintSolverMemento = notePadMementoMaker.MakeMemento(false,true,true, clone);
	notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
}


void NotePadMaker::EraseCurrentCharactorInRow() {
	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();
	NotePadMetric notePadMetric(this->notePadForm);


	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	notePadRestorer->GetNotePadHistory()->MoveLastHistory();      
	constraintSolverMemento = notePadMementoMaker.MakeMemento(false,true,false,this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())->Clone());
	notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
	
	if (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent()))) {
		if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())))->GetSingleByteContent() == '\t') {
				Long count = 0;
				while (count < 8 && ((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())))->GetSingleByteContent() == '\t') {
					this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent());
					this->notePadForm->row->Next();
					count++;
				}
		}
		else {
				this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent());
				this->notePadForm->row->Next();
		}
	}
	else {
		this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent());
		this->notePadForm->row->Next();
	}
	
}


void NotePadMaker::PlusRowInNotePadForUndoRedo() {

	GlyphFactory glyphFactory;
	Glyph* glyph;
	TCHAR buffer[3];

	buffer[0] = '\r';
	buffer[1] = '\n';
	buffer[2] = '\0';
	glyph = glyphFactory.MakeGlyph(buffer);

	if (this->notePadForm->notePad->GetCurrent() >= this->notePadForm->notePad->GetLength() - 1) {
		this->notePadForm->notePad->Add(glyph);
	}
	else {
		this->notePadForm->notePad->Put(this->notePadForm->notePad->GetCurrent() + 1, glyph);
	}
	this->notePadForm->row = glyph;

	this->notePadForm->GetScrollController()->SetHPos(0);
}


void NotePadMaker::PlusRowInNotePadNoCurrentMoveForUndoRedo() {
	GlyphFactory glyphFactory;
	Glyph* glyph;
	TCHAR buffer[3];

	buffer[0] = '\r';
	buffer[1] = '\n';
	buffer[2] = '\0';
	glyph = glyphFactory.MakeGlyph(buffer);

	if (this->notePadForm->notePad->GetCurrent() >= this->notePadForm->notePad->GetLength() - 1) {
		this->notePadForm->notePad->Add(glyph);
	}
	else {
		this->notePadForm->notePad->Put(this->notePadForm->notePad->GetCurrent() + 1, glyph);
	}
	this->notePadForm->notePad->Previous();
	
}


void NotePadMaker::WriteTabInRowForUndoRedo(Glyph* contents) {
	
	GlyphFactory glyphFactory;
	Glyph* glyph;
	Long hPosition = 0;
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	Long i = 0;
	while (i < 8) {
		glyph = contents->Clone();
		if (this->notePadForm->row->GetCurrent() >= this->notePadForm->row->GetLength()) {
			this->notePadForm->row->Add(glyph);
		}
		else {
			this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
		}
		i++;
	}
}


void NotePadMaker::WriteTabInRowNoCurrentMoveForUndoRedo(Glyph* contents) {
	GlyphFactory glyphFactory;
	Glyph* glyph;

	Long hPosition = 0;
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	Long i = 0;
	while (i < 8) {

		glyph = contents->Clone();
		if (this->notePadForm->row->GetCurrent() >= this->notePadForm->row->GetLength()) {
			this->notePadForm->row->Add(glyph);
		}
		else {
			this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
		}
		this->notePadForm->row->Previous();
		i++;
	}
}


void NotePadMaker::WriteContentsInRowForUndoRedo(Glyph* contents) {
	GlyphFactory glyphFactory;
	Glyph* glyph;

	Long hPosition = 0;
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	glyph = contents->Clone();

	if (this->notePadForm->row->GetCurrent() == this->notePadForm->row->GetLength()) {
		this->notePadForm->row->Add(glyph);
	}
	else {
		this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
	}
}


void NotePadMaker::WriteContentsInRowNoCurrentMoveForUndoRedo(Glyph* contents) {
	GlyphFactory glyphFactory;
	Glyph* glyph;

	Long hPosition = 0;
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	glyph = contents->Clone();

	if (this->notePadForm->row->GetCurrent() == this->notePadForm->row->GetLength()) {
		this->notePadForm->row->Add(glyph);
	}
	else {
		this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
	}
	this->notePadForm->row->Previous();
}


void NotePadMaker::EraseCurrentRowInNotePadForUndoRedo() {
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	GlyphFactory glyphFactory;
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	Long i = 0;
	Glyph* previousRow = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent() - 1);
	Long previousRowLength = previousRow->GetLength();

	while (i < this->notePadForm->row->GetLength()) {
		previousRow->Add(this->notePadForm->row->GetAt(i)->Clone());
		i++;
	}
	i = 0;
	previousRow->First();
	while (i < previousRowLength) {
		previousRow->Next();
		i++;
	}

	this->notePadForm->notePad->Remove(this->notePadForm->notePad->GetCurrent());
	this->notePadForm->row = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent());
}


void NotePadMaker::EraseNextRowInNotePadForUndoRedo() {
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	GlyphFactory glyphFactory;
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	
	Long i = 0;
	Glyph* nextRow = this->notePadForm->notePad->GetAt(this->notePadForm->notePad->GetCurrent() + 1);
	Long index = nextRow->GetLength();
	Long previousIndex = this->notePadForm->row->GetCurrent();

	while (i < nextRow->GetLength()) {
		this ->notePadForm->row->Add(nextRow->GetAt(i)->Clone());
		i++;
	}
	i = 0;
	this->notePadForm->row->First();
	while (i < previousIndex) {
		this->notePadForm->row->Next();
		i++;
	}
	this->notePadForm->notePad->Remove(this->notePadForm->notePad->GetCurrent() + 1);
	this->notePadForm->notePad->Next();

}


void NotePadMaker::ErasePreviousCharacterInRowForUndoRedo() {
	
	TextMetric textMetric(this->notePadForm);
	NotePadMetric notePadMetric(this->notePadForm);
	GlyphFactory glyphFactory;
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	bool isNotePadLengthDiffer = false;
	Long notePadLengthBeforeNotify = this->notePadForm->notePad->GetLength();
	Long notePadLengthAfterNotify = 0;

	if (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() - 1))) {
		if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() - 1)))->GetSingleByteContent() == '\t') {
			Long count = 0;
			while (count < 8 && ((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent() - 1)))->GetSingleByteContent() == '\t') {
				this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent() - 1);
				count++;
			}
		}
		else {
			this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent() - 1);
		}
	}
	else {
		this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent() - 1);
	}
}


void NotePadMaker::EraseCurrentCharactorInRowForUndoRedo() {

	if (dynamic_cast<SingleByteCharacter*>(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent()))) {
		if (((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())))->GetSingleByteContent() == '\t') {
			Long count = 0;
			while (count < 8 && ((SingleByteCharacter*)(this->notePadForm->row->GetAt(this->notePadForm->row->GetCurrent())))->GetSingleByteContent() == '\t') {
				this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent());
				this->notePadForm->row->Next();
				count++;
			}
		}
		else {
			this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent());
			this->notePadForm->row->Next();
		}
	}
	else {
		this->notePadForm->row->Remove(this->notePadForm->row->GetCurrent());
		this->notePadForm->row->Next();
	}
}


void NotePadMaker::WriteContentsFromStringForUndoRedo(string* contents) {
	string cloneContents(*contents);
	char(*buffer) = 0;
	buffer = (char*)(cloneContents.c_str());
	PasteSupervisor pasteSupervisor(this->notePadForm);
	if (this->notePadForm->GetIsComposition() == true) {
		this->notePadForm->SetIsComposition(false);
	}
	pasteSupervisor.PasteContentsForUnDoReDo(buffer);
}


void NotePadMaker::EraseDesignatedAreaForUndoPaste(Long rowIndexRelatedWithAfterAction, Long columnIndexRelatedWithAfterAction) {
	Long i = 0;//전체 처리해야할 줄갯수에 관한 변수
	Long j = 0;//현재까지 처리된 줄갯수에 관한 변수
	Long k = 0;//글자하나씩 삭제해줄때 반복제어변수
	Long l = 0;//줄삭제에 관련한 반복제어변수
	bool isFirstRowRemoved = false;
	Long erasedRowCount = 0;
	Glyph* row = 0;
	Long rowLength = 0;
	Long rowIndexRelatedWithBeforeAction = this->notePadForm->notePad->GetCurrent();
	Long columnIndexRelatedWithBeforeAction = this->notePadForm->row->GetCurrent();
	i = rowIndexRelatedWithAfterAction - this->notePadForm->notePad->GetCurrent()+1;
	while (j < i) {
		if (i - 1 == 0) {//선택줄이 1줄이란뜻
			row = this->notePadForm->notePad->GetAt(rowIndexRelatedWithBeforeAction);
			while (k < columnIndexRelatedWithAfterAction- columnIndexRelatedWithBeforeAction) {
				row->Remove(columnIndexRelatedWithBeforeAction);
				k++;
			}
		}
		else {
			k = 0;
			
			if (j == 0) {
				l = rowIndexRelatedWithBeforeAction;
				row = this->notePadForm->notePad->GetAt(l);
				rowLength = row->GetLength();
				while (k < rowLength - columnIndexRelatedWithBeforeAction) {
					row->Remove(columnIndexRelatedWithBeforeAction);
					k++;
				}
				if (row->GetLength() == 0) {
					this->notePadForm->notePad->Remove(l);
					isFirstRowRemoved = true;
					erasedRowCount++;
				}
				else {
					l++;
				}
			}
			else if (j == i - 1) {
				row = this->notePadForm->notePad->GetAt(l);
				while (k < columnIndexRelatedWithAfterAction) {
					row->Remove(0);
					k++;
				}
				if (erasedRowCount < i - 1 && row->GetLength() == 0) {
					this->notePadForm->notePad->Remove(l);
				}
				else {
					if (isFirstRowRemoved == false && columnIndexRelatedWithAfterAction >= 0 ) {
						Glyph* previousRow = this->notePadForm->notePad->GetAt(rowIndexRelatedWithBeforeAction);
						Long c = 0;
						while (row->GetLength() > 0) {
							previousRow->Add(row->GetAt(0)->Clone());
							row->Remove(0);
							c++;
						}
						this->notePadForm->notePad->Remove(l);
					}
				}
			}
			else {
				this->notePadForm->notePad->Remove(l);
				erasedRowCount++;
			}
		}
		j++;
	}
	NotePadIndicator notePadIndicator(this->notePadForm);
	notePadIndicator.GoToCoordinate(rowIndexRelatedWithBeforeAction, columnIndexRelatedWithBeforeAction);
}

void NotePadMaker::EraseDesignatedAreaForRedoCutOut(Long rowIndexRelatedWithBeforeAction, Long columnIndexRelatedWithBeforeAction) {

	Long i = 0;//전체 처리해야할 줄갯수에 관한 변수
	Long j = 0;//현재까지 처리된 줄갯수에 관한 변수
	Long k = 0;//글자하나씩 삭제해줄때 반복제어변수
	Long l = 0;//줄삭제에 관련한 반복제어변수
	bool isFirstRowRemoved = false;
	Long erasedRowCount = 0;
	Glyph* row = 0;
	Long rowLength = 0;
	Long rowIndexRelatedWithAfterAction = this->notePadForm->notePad->GetCurrent();
	Long columnIndexRelatedWithAfterAction = this->notePadForm->row->GetCurrent();
	i = rowIndexRelatedWithBeforeAction - rowIndexRelatedWithAfterAction + 1;
	while (j < i) {
		if (i - 1 == 0) {//선택줄이 1줄이란뜻
			row = this->notePadForm->notePad->GetAt(rowIndexRelatedWithAfterAction);
			while (k < columnIndexRelatedWithBeforeAction- columnIndexRelatedWithAfterAction) {
				row->Remove(columnIndexRelatedWithAfterAction);
				k++;
			}
		}
		else {
			k = 0;
			
			if (j == 0) {
				l =  rowIndexRelatedWithAfterAction;
				row = this->notePadForm->notePad->GetAt(l);
				rowLength = row->GetLength();
				while (k < rowLength - columnIndexRelatedWithAfterAction) {
					row->Remove(columnIndexRelatedWithAfterAction);
					k++;
				}
				if (row->GetLength() == 0) {
					this->notePadForm->notePad->Remove(l);
					isFirstRowRemoved = true;
					erasedRowCount++;
				}
				else {
					l++;
				}
			}
			else if (j == i - 1) {
			
				row = this->notePadForm->notePad->GetAt(l);
				while (k < columnIndexRelatedWithBeforeAction) {
					row->Remove(0);
					k++;
				}
				if (erasedRowCount < i - 1 && row->GetLength() == 0) {
					this->notePadForm->notePad->Remove(l);
				}
				else {
					if (isFirstRowRemoved == false && columnIndexRelatedWithBeforeAction >= 0) {
						Glyph* previousRow = this->notePadForm->notePad->GetAt(rowIndexRelatedWithAfterAction);
						Long c = 0;
						while (row->GetLength() > 0) {
							previousRow->Add(row->GetAt(0)->Clone());
							row->Remove(0);
							c++;
						}
						this->notePadForm->notePad->Remove(l);
					}
				}
			}
			else {
				this->notePadForm->notePad->Remove(l);
				erasedRowCount++;
			}
		}
		j++;
	}
	NotePadIndicator notePadIndicator(this->notePadForm);
	notePadIndicator.GoToCoordinate(rowIndexRelatedWithAfterAction, columnIndexRelatedWithAfterAction);
}