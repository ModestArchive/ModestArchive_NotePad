//NotePadIndicator.cpp
#include"NotePadIndicator.h"
#include"TextMetric.h"
#include"NotePadForm.h"
#include"DummyRow.h"

NotePadIndicator::NotePadIndicator(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}


NotePadIndicator::~NotePadIndicator() {
	
}


void NotePadIndicator::GoToCoordinate(Long rowIndex, Long columnIndex ) {

	this->notePadForm->notePad->First();

	while (this->notePadForm->notePad->GetCurrent() < rowIndex) {
		this->notePadForm->notePad->Next();
	}
	this->notePadForm->row = this->notePadForm->notePad->GetAt(rowIndex);
	this->notePadForm->row->First();
	while (this->notePadForm->row->GetCurrent() < columnIndex) {
		this->notePadForm->row->Next();
	}
}

