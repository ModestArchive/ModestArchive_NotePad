//MatchIndex.cpp
#include"MatchIndex.h"

MatchIndex::MatchIndex(Long startRowIndex, Long startColumnIndex, Long endRowIndex, Long endColumnIndex) {
	this->startRowIndex = startRowIndex;
	this->startColumnIndex = startColumnIndex;
	this->endRowIndex = endRowIndex;
	this->endColumnIndex = endColumnIndex;
}

MatchIndex& MatchIndex::operator=(const MatchIndex& source) {
	this->startRowIndex = source.startRowIndex;
	this->startColumnIndex = source.startColumnIndex;
	this->endRowIndex = source.endRowIndex;
	this->endColumnIndex = source.endColumnIndex;

	return *this;
}
bool MatchIndex::operator==(const MatchIndex& other) {
	bool ret = false;
	if (this->startRowIndex==other.startRowIndex &&
		this->startColumnIndex==other.startColumnIndex &&
		this->endRowIndex==other.endRowIndex &&
		this->endColumnIndex==other.endColumnIndex) {

		ret = true;
	}
	
	return ret;
}

MatchIndex::~MatchIndex() {
	    
}