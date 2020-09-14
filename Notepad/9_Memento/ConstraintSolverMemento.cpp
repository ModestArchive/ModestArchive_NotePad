//ConstraintSolverMemento.cpp
#include"ConstraintSolverMemento.h"


ConstraintSolverMemento::~ConstraintSolverMemento() {
	if (this->notePadState!=0) {
		delete this->notePadState;
	}
}


ConstraintSolverMemento::ConstraintSolverMemento(NotePadState* notePadState) {
	this->notePadState = notePadState;
}


void ConstraintSolverMemento::SetState(NotePadState* notePadState) {
	this->notePadState = notePadState;
}


NotePadState* ConstraintSolverMemento::GetState() {
	return this->notePadState;
}
