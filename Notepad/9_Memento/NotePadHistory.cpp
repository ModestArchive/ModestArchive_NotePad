//NotePadHistory.cpp

#include"NotePadHistory.h"

NotePadHistory::NotePadHistory(Long capacity):constraintSolverMementoes(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = 0;
}


NotePadHistory::~NotePadHistory() {
	Long i = 0;
	while (i < this->length) {
		delete this->constraintSolverMementoes[i];
		i++;
	}
}


Long NotePadHistory::AddHistory(ConstraintSolverMemento* constraintSolverMemento) {
	Long index;

	if (this->capacity > this->length) {
		index = this->constraintSolverMementoes.Store(this->length, constraintSolverMemento);
	}
	else {
		index = this->constraintSolverMementoes.AppendFromRear(constraintSolverMemento);
		this->capacity++;
	}
	this->length++;
	this->current++;

	return index;
}


Long NotePadHistory::PutHistory(Long index,ConstraintSolverMemento* constraintSolverMemento) {
	index = this->constraintSolverMementoes.Insert(index,constraintSolverMemento);
	this->capacity++;

	this->length++;
	this->current++;
	return index;
}

Long NotePadHistory::RemoveHistory(Long index) {

	ConstraintSolverMemento* constraintSolverMemento= this->constraintSolverMementoes[index];
	if (constraintSolverMemento!= 0) {
		delete constraintSolverMemento;
	}
	this->constraintSolverMementoes.Delete(index);
	this->capacity--;
	this->length--;
	this->current--;

	return this->current;
}


ConstraintSolverMemento* NotePadHistory::GetAt(Long index) {
	return this->constraintSolverMementoes.GetAt(index);
}


Long NotePadHistory::MoveLastHistory() {
	this->current = this->length;
	return this->current;
}


Long NotePadHistory::MovePreviousHistory() {
	this->current--;
	return this->current;
}


Long NotePadHistory::MoveNextHistory() {
	this->current++;
	return this->current;
}


Long NotePadHistory::MoveFirstHistory() {
	this->current = 0;
	return this->current;
}
