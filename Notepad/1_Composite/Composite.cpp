//Composite.cpp

#include"Composite.h"
#include"Glyph.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif
//ġȯ������, ��������ڿ����� Ŭ��


Composite::Composite(Long capacity) :glyphs(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = 0 ;
}

Composite::Composite(const Composite& source) : glyphs(source.glyphs) {
	
	Glyph* clone = 0;
	Long i = 0;
	while (i < this->glyphs.GetLength()) {

		clone = this->glyphs[i]->Clone();
		this->glyphs.Modify(i, clone);
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

Composite::~Composite() {
	Long i = 0;
	while (i < this->length) {
		delete this->glyphs[i];
		i++;
	}
}

/*Long Composite::Add(Glyph* glyph) {

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
}*/

Long Composite::Change(Long index, Glyph* glyph) {
	
	index=this->glyphs.Modify(index, glyph);
	return index;
}


Glyph* Composite::GetAt(Long index) {
	return this->glyphs.GetAt(index);
}


Long Composite::Remove(Long index) { // @@ ����� �޼���� �׳� ����� ������ ������. �ٸ��� �� ��������� �����̾����� @@
								     // @@ ����� ���� ����� ���� ������ �� �ٸ� ��� ��������� �����ϰ� �װ͵� �����ִ� ������ ������ @@ 
	Glyph* glyph = 0;
	glyph = this->glyphs[index];

	if (glyph != 0) {
		delete glyph;
	}
	this->glyphs.Delete(index); 
	this->capacity--;
	this->length--;
	this->current--;
	
	return this->current;
}


Long Composite::First() {
	this->current = 0;
	return this->current;

}


Long Composite::Last() {
	this->current = this->length;

	return this->current;
}


Long Composite::Previous() {
	this->current--;
	return this->current;
}
 

Long Composite::Next() {
	this->current++;
	return this->current;
}


Composite& Composite::operator=(const Composite& source) {
	Long i = 0;
	while (i < this->length) {
		delete this->glyphs[i];
		i++;
	}
	Glyph* rowGlyphClone = 0;
	
	while (i < this->glyphs.GetLength()) {

		rowGlyphClone = this->glyphs[i]->Clone();
		this->glyphs.Modify(i, rowGlyphClone);
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
	return *this;
}


Glyph* Composite::operator[](Long index) {
	return this->glyphs[index];
}