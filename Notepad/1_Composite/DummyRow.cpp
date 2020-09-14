//DummyRow.cpp

#include"DummyRow.h"
#include"SingleByteCharacter.h"
#include"ArrayIterator.h"
#include"Glyph.h"


DummyRow::DummyRow(Long capacity) :Row(capacity) {
	this->isSubjectedHyphenationRule = false;
	this->isTabErased = false;
}


DummyRow::DummyRow(const DummyRow& source) : Row(source) {
	this->isSubjectedHyphenationRule = source.isSubjectedHyphenationRule;
	this->isTabErased = source.isTabErased;
}


DummyRow::~DummyRow() {

}


Iterator<Glyph*>* DummyRow::CreateIterator() {
	
	return Row::CreateIterator();
}


Long DummyRow::Put(Long index, Glyph* glyph) {

	return Row::Put(index, glyph);
}


string DummyRow::GetContents() {

	return Row::GetContents();
}


Glyph* DummyRow::Clone() {
	
	return Row::Clone();
}

void DummyRow::SetIsTabErasedTrue() {
	this->isTabErased = true;
}

void DummyRow::SetIsTabErasedFalse() {
	this->isTabErased = false;
}

void DummyRow::SetIsSubjectedHyphenationRuleTrue() {
	this->isSubjectedHyphenationRule = true;
}
