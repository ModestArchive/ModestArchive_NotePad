//Row.cpp

#include"Row.h"
#include"SingleByteCharacter.h"
#include"ArrayIterator.h"
#include"Glyph.h"

Row::Row(Long capacity) :Composite(capacity) {

}

Row::Row(const Row& source) :Composite(source){
	
}

Row::~Row() {
	
}

Iterator<Glyph*>* Row::CreateIterator() {
	return new ArrayIterator<Glyph*>(&this->glyphs);
}

Long Row::Add(Glyph* glyph) {
	Long index;

	if (this->capacity > this->length) {

		index = this->glyphs.Store(this->length, glyph);
	}
	else {
		index = this->glyphs.AppendFromRear(glyph);
		this->capacity++;
	}
	this->length++;
	this->current++;
		
	return index;
}

Long Row::Put(Long index, Glyph* glyph) {
	index = this->glyphs.Insert(index, glyph);
	this->capacity++;
	this->length++;
	this->current++;

	return index;
}

string Row::GetContents() {
	
	Iterator<Glyph*>* arrayIterator = 0;
	arrayIterator = this->CreateIterator();
	string contents="";
	
	arrayIterator->First();
    
	while (!(arrayIterator->IsDone())) {

		Glyph* glyph = 0;
		glyph = arrayIterator->CurrentItem();
		contents += glyph->GetContents();
		arrayIterator->Next();
	}
	return contents;
}

Glyph* Row::Clone() {
	return new Row(*this);
}


void Row::SearchMatchCharDuplicate(string* findWhatContents,Long* (*indexes),Long* count, int(*compare)(void*, void*)) {
	this->glyphs.LinearSearchDuplicate(findWhatContents, indexes, count, compare);
}