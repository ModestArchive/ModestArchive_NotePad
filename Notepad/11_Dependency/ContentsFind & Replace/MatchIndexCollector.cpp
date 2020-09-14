//MatchIndexCollector.cpp
#include"MatchIndexCollector.h"
MatchIndexCollector::MatchIndexCollector(Long capacity) : matchIndexes(capacity){
	this->capacity = capacity;
	this->length = 0;
	this->current = 0;
}


MatchIndexCollector::~MatchIndexCollector() {
	Long i = 0;
	if (i<this->matchIndexes.GetLength()) {
		delete this->matchIndexes[i];
		i++;
	}
}


Long MatchIndexCollector::AddMatchIndex(MatchIndex* matchIndex) {
	Long index;
	if (this->capacity > this->length) {
		index = this->matchIndexes.Store(this->length, matchIndex);
	}
	else {
		index = this->matchIndexes.AppendFromRear(matchIndex);
		this->capacity++;
	}
	this->length++;
	this->current++;

	return index;
}


MatchIndex* MatchIndexCollector::GetAt(Long index) {
	MatchIndex* matchIndex = 0;
	matchIndex = this->matchIndexes.GetAt(index);

	return matchIndex;
}


Long MatchIndexCollector::MoveLastMatchIndex() {
	this->current = this->length;
	return this->current;
}
Long MatchIndexCollector::MovePreviousMatchIndex(){
	 this->current--;
	return this->current;
}
Long MatchIndexCollector::MoveNextMatchIndex() {
	this->current++;
	return this->current;
}
Long MatchIndexCollector::MoveFirstMatchIndex() {
	this->current = 0;
	return this->current;
}