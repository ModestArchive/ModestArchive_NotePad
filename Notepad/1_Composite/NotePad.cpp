//NotePad.cpp

#include<iostream>
#include"NotePad.h"
#include"Row.h"
#include"SingleByteCharacter.h"
#include"DoubleByteCharacter.h"
#include"Glyph.h"
#include<afxwin.h>
#include"GlyphFactory.h"
#include"ArrayIterator.h"
#include"TextMetric.h"
#include"NotePadMetric.h"
#include"DummyRow.h"
#include"Font.h"
#include<string>

using namespace std;

NotePad::NotePad(Long capacity) :Composite(capacity) {

}

NotePad::NotePad(const NotePad& source):Composite(source) {

	
}


NotePad::~NotePad() {

}

Iterator<Glyph*>* NotePad::CreateIterator(){// const 뺏음
	return new ArrayIterator<Glyph*>(&this->glyphs);
}

Long NotePad::Add(Glyph* glyph) {

	Long index = 0;
	if (this->capacity > this->length) {
		
		index=this->glyphs.Store(this->length, glyph);
	}
	else {
		index = this->glyphs.AppendFromRear(glyph);
		this->capacity++;
	}
	this->length++;
	
	if (this->glyphs[this->current]->GetCurrent() < this->glyphs[this->current]->GetLength()) {
		Long i = this->glyphs[this->current]->GetCurrent();

		while (i < this->glyphs[this->current]->GetLength()) {
			glyph->Add(this->glyphs[this->current]->GetAt(i)->Clone());
			i++;
		}
		Long j = 0;
		Long rowCurrent = this->glyphs[this->current]->GetCurrent();
		Long rowLength = this->glyphs[this->current]->GetLength();

		while (j < rowLength - rowCurrent) {
			this->glyphs[this->current]->Remove(this->glyphs[this->current]->GetCurrent());
			this->glyphs[this->current]->Next();
			j++;
		}
		glyph->First();
	}

	this->current++;
	return index;
}

Long NotePad::Put(Long index, Glyph* glyph) {

	
	if (this->GetAt(this->current)->GetCurrent() >= this->GetAt(this->current)->GetLength()) {
		
		Long rowIndex = this->glyphs.Insert(index, glyph);
	
	}
	else {
		
		Long i = this->GetAt(current)->GetCurrent();
		while (i < this->GetAt(current)->GetLength()) {
			glyph->Add(this->GetAt(current)->GetAt(i)->Clone());
			i++;
		}
		
		Long j = 0;
		Long rowLength = this->GetAt(current)->GetLength();
		Long rowCurrent = this->GetAt(current)->GetCurrent();
		while (j < rowLength - rowCurrent) {
			this->GetAt(current)->Remove(this->GetAt(current)->GetCurrent());
			this->GetAt(current)->Next();
			j++;
		}
		glyph->First();
		Long rowIndex = this->glyphs.Insert(index, glyph);
		
	}
	this->capacity++;
	this->length++;
	this->current++;
	return index;
}


Glyph* NotePad::Clone() {
	return new NotePad(*this);
}

string NotePad::GetContents() {

	Iterator<Glyph*>* arrayIterator = 0;
	arrayIterator = this->CreateIterator();
	string contentsBuffer = "";

	arrayIterator->First();

	while (!(arrayIterator->IsDone())) {
		Glyph* glyph = 0;
		glyph = arrayIterator->CurrentItem();
		Long j = 0;
		while (j < glyph->GetLength()) {
			if (dynamic_cast<SingleByteCharacter*>(glyph->GetAt(j))) {
				if (((SingleByteCharacter*)(glyph->GetAt(j)))->GetSingleByteContent() == '\t') {

					char buffer[2];
					buffer[0] = '\t';
					buffer[1] = '\0';
					contentsBuffer += buffer;
				}
				else {
					contentsBuffer += glyph->GetAt(j)->GetContents();
				}
			}
			else {
				contentsBuffer += glyph->GetAt(j)->GetContents();
			}
			j++;
		}
		arrayIterator->Next();
		if (!(arrayIterator->IsDone())) {
			glyph = arrayIterator->CurrentItem();
			if (!(dynamic_cast<DummyRow*>(glyph))) {
				contentsBuffer += "\r\n";
			}
		}
		arrayIterator->Previous();
		arrayIterator->Next();
	}
	//contentsBuffer.pop_back();
	//contentsBuffer.pop_back();
	
	return contentsBuffer;
}


string NotePad::GetContentsForString() {

	Iterator<Glyph*>* arrayIterator = 0;
	arrayIterator = this->CreateIterator();
	string contentsBuffer = "";

	arrayIterator->First();

	while (!(arrayIterator->IsDone())) {
		Glyph* glyph = 0;
		glyph = arrayIterator->CurrentItem();
		Long j = 0;
		while (j < glyph->GetLength()) {
			if (dynamic_cast<SingleByteCharacter*>(glyph->GetAt(j))) {
				if (((SingleByteCharacter*)(glyph->GetAt(j)))->GetSingleByteContent() == '\t') {

					char buffer[2];
					buffer[0] = '\t';
					buffer[1] = '\0';
					contentsBuffer += buffer;
					j += 8;
				}
				else {
					contentsBuffer += glyph->GetAt(j)->GetContents();
					j++;
				}
			}
			else {
				contentsBuffer += glyph->GetAt(j)->GetContents();
				j++;
			}
		}
		arrayIterator->Next();
		if (!(arrayIterator->IsDone())) {
			glyph = arrayIterator->CurrentItem();
			if (!(dynamic_cast<DummyRow*>(glyph))) {
				contentsBuffer += "\r\n";
			}
		}
		arrayIterator->Previous();
		arrayIterator->Next();
	}
	//contentsBuffer.pop_back();
	//contentsBuffer.pop_back();

	return contentsBuffer;
}


string NotePad::SaveModeGetContents() {
	Iterator<Glyph*>* arrayIterator = 0;
	arrayIterator = this->CreateIterator();
	string contentsBuffer = "";

	arrayIterator->First();

	while (!(arrayIterator->IsDone())) {
		Glyph* glyph = 0;
		glyph = arrayIterator->CurrentItem();
		Long j = 0;
		while (j < glyph->GetLength()) {
			if (dynamic_cast<SingleByteCharacter*>(glyph->GetAt(j))) {
				if (((SingleByteCharacter*)(glyph->GetAt(j)))->GetSingleByteContent() == '\t') {

					char buffer[2];
					buffer[0] = '\t';
					buffer[1] = '\0';
					contentsBuffer += buffer;
				}
				else {
					contentsBuffer += glyph->GetAt(j)->GetContents();
				}
			}
			else {
				contentsBuffer += glyph->GetAt(j)->GetContents();
			}
			j++;
		}
		arrayIterator->Next();
		if (!(arrayIterator->IsDone())) {
			glyph = arrayIterator->CurrentItem();
			if (!(dynamic_cast<DummyRow*>(glyph))) {
				contentsBuffer += "\n";
			}
		}
		arrayIterator->Previous();
		arrayIterator->Next();
	}
	//contentsBuffer.pop_back();
	//contentsBuffer.pop_back();

	return contentsBuffer;
}


Long NotePad::Last() {
	Composite::Last();
	if (this->length == this->current) {
		this->current--;
	}
	return this->current;
}



int main(int argc, char* argv[]) {
	GlyphFactory glyphFactory;
	Glyph* notePad;
	Glyph* row;
	Glyph* glyph;
	Long rowIndex = 0;
	Long columnIndex = 0;

	notePad = glyphFactory.MakeGlyph((char*)(""));
	row = glyphFactory.MakeGlyph((char*)("\r\n"));
	rowIndex = notePad->Add(row);
	
	glyph = glyphFactory.MakeGlyph((char*)("a"));
	columnIndex = row->Add(glyph);
	cout << row->GetContents() << endl;

	glyph = glyphFactory.MakeGlyph((char*)("가"));
	columnIndex = row->Add(glyph);                               
	cout << row->GetContents() << endl;

	cout<< notePad->GetContents() << endl;

	return 0;



	
	 /*Glyph* notePad = new NotePad; //GlyphFactory 하기전
	
	Glyph* glyph;
	Long rowIndex;
	
	

	
	glyph = new Row;
	rowIndex = notePad->Add(glyph);
	
	

	Glyph* singleByteContentGlyph;

	singleByteContentGlyph = new SingleByteCharacter('a');

	Long columnIndex;
	
	columnIndex = glyph->Add(singleByteContentGlyph);

	Glyph* characterGlyph;
	characterGlyph = glyph->GetAt(columnIndex);

	if (characterGlyph == singleByteContentGlyph) {
		cout << "같은단어주소값입니다." << endl;
	}

	cout << characterGlyph->GetContents() << endl;

	Glyph* doubleByteContentGlyph;

	doubleByteContentGlyph = new DoubleByteCharacter((char*)("한"));
	
	columnIndex = glyph->Add(doubleByteContentGlyph);

	characterGlyph = glyph->GetAt(columnIndex);
	if (doubleByteContentGlyph == characterGlyph) {

		cout << "같은단어주소값입니다." << endl;
	}

	cout << characterGlyph->GetContents() << endl;
	cout << "-----------------------------------------" << endl;
	cout << glyph->GetContents() << endl;
	glyph = new Row;

	notePad->Add(glyph);
	glyph->Add(new SingleByteCharacter('b'));
	glyph->Add(new DoubleByteCharacter((char*)("국")));
	cout << "-----------------------------------------" << endl;
	cout << glyph->GetContents() << endl;
	cout << "-----------------------------------------" << endl;
	cout << notePad->GetContents() << endl;
	
	Glyph* other = new NotePad(*(dynamic_cast<NotePad*>(notePad)));
	cout << "-----------------------------------------" << endl;
	cout << other->GetContents() << endl;
	if (other != 0) {
		delete other;
	}
	if (notePad != 0) {
		delete notePad;//delete[]는 배열 삭제하는거 delete는 우리가 다 일일이 만들어준거를 지우는거
	}
	
	
	
		
	return 0;  */

	
}