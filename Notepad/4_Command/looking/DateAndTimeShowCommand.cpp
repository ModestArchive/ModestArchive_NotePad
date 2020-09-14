//DateAndTimeShowCommand.cpp

#include"NotePadForm.h"
#include<string>
#include<iostream>
#include"DateAndTimeShowCommand.h"
#include"StringMaker.h"
#include"NotePadMementoMaker.h"
#include"NotePadRestorer.h"
#include"ConstraintSolver.h"
#include"HistoryReconstructor.h"
#include"PasteSupervisor.h"

DateAndTimeShowCommand::DateAndTimeShowCommand(NotePadForm* notePadForm):Command(notePadForm){

	this->notePadForm = notePadForm;
}

DateAndTimeShowCommand::~DateAndTimeShowCommand() {

}

void DateAndTimeShowCommand::Execute() {
	StringMaker stringMaker(this->notePadForm);
	string time="";
	time = stringMaker.MakeTimeString();
	char* buffer = 0;
	buffer = (char*)(time.c_str());

	NotePadMementoMaker notePadMementoMaker(this->notePadForm);
	ConstraintSolverMemento* constraintSolverMemento = 0;
	NotePadRestorer* notePadRestorer = this->notePadForm->GetNotePadRestorer();

	if (this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetCurrent() != this->notePadForm->GetNotePadRestorer()->GetNotePadHistory()->GetLength()) {
		HistoryReconstructor historyReconstructor(this->notePadForm->GetNotePadRestorer()->GetNotePadHistory(), this->notePadForm);
		historyReconstructor.ReconstructHistory();
	}
	notePadRestorer->GetNotePadHistory()->MoveLastHistory();
	string* cloneContents = new string(time);
	constraintSolverMemento = notePadMementoMaker.MakeMemento(true, false, -1, -1, cloneContents);
	notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);

	PasteSupervisor pasteSupervisor(this->notePadForm);
	pasteSupervisor.PasteContents(buffer);

	constraintSolverMemento = notePadMementoMaker.MakeMemento(true, false, -1, -1, cloneContents);
	notePadRestorer->GetNotePadHistory()->AddHistory(constraintSolverMemento);
}