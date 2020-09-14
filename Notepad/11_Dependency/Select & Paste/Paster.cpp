//Paster.cpp
#include"Paster.h"
#include"NotePadMaker.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"Selector.h"
#include"GlyphFactory.h"
#include"DummyRow.h"
#include"NotePadModifier.h"
#include"NotePadMetric.h"
#include"Font.h"
#include"notePadMetric.h"


Paster::Paster(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}


Paster::~Paster() {

}


void Paster::PasteRowInNotePad() {
	GlyphFactory glyphFactory;
	Glyph* glyph;
	TCHAR buffer[3];

	buffer[0] = '\r';
	buffer[1] = '\n';
	buffer[2] = '\0';
	glyph = glyphFactory.MakeGlyph(buffer);

	if (this->notePadForm->notePad->GetCurrent() >= this->notePadForm->notePad->GetLength() - 1) {
		this->notePadForm->notePad->Add(glyph);
	}
	else {
		this->notePadForm->notePad->Put(this->notePadForm->notePad->GetCurrent() + 1, glyph);
	}
	this->notePadForm->row = glyph;

	this->notePadForm->GetScrollController()->SetHPos(0);
	
}

void Paster::PasteDoubleByteCharacterInRow(char(*buffer)){
	Glyph* glyph = 0;
	NotePadMetric notePadMetric(this->notePadForm);
	GlyphFactory glyphFactory;
	glyph = glyphFactory.MakeGlyph(buffer);

	if (this->notePadForm->row->GetCurrent() == this->notePadForm->row->GetLength()) {
		this->notePadForm->row->Add(glyph);
	}
	else {
		this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
	}
	
}

void Paster::PasteSingleByteCharacterInRow(char(*buffer)) {
	GlyphFactory glyphFactory;
	Glyph* glyph;
	NotePadMetric notePadMetric(this->notePadForm);
	Long hPosition = 0;
	TextMetric textMetric(this->notePadForm);
	
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	glyph = glyphFactory.MakeGlyph(buffer);
	if (this->notePadForm->row->GetCurrent() == this->notePadForm->row->GetLength()) {
		this->notePadForm->row->Add(glyph);
	}
	else {
		this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
	}
}


void Paster::PasteTabInRow(char(*buffer)) {
	GlyphFactory glyphFactory;
	Glyph* glyph;
	NotePadMetric notePadMetric(this->notePadForm);
	
	Long hPosition = 0;
	TextMetric textMetric(this->notePadForm);
	
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	
	Long i = 0;
	while (i < 8) {

		glyph = glyphFactory.MakeGlyph(buffer);
		if (this->notePadForm->row->GetCurrent() >= this->notePadForm->row->GetLength()) {
			this->notePadForm->row->Add(glyph);
		}
		else {
			this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
		}
		i++;
	}
}

void Paster::PasteRowInNotePadForUnDoReDo() {
	GlyphFactory glyphFactory;
	Glyph* glyph;
	TCHAR buffer[3];

	buffer[0] = '\r';
	buffer[1] = '\n';
	buffer[2] = '\0';
	glyph = glyphFactory.MakeGlyph(buffer);

	if (this->notePadForm->notePad->GetCurrent() >= this->notePadForm->notePad->GetLength() - 1) {
		this->notePadForm->notePad->Add(glyph);
	}
	else {
		this->notePadForm->notePad->Put(this->notePadForm->notePad->GetCurrent() + 1, glyph);
	}
	this->notePadForm->row = glyph;

	this->notePadForm->GetScrollController()->SetHPos(0);

}

void Paster::PasteDoubleByteCharacterInRowForUnDoReDo(char(*buffer)) {
	TextMetric textMetric(this->notePadForm);
	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();
	Long hPosition = 0;

	Glyph* glyph = 0;
	NotePadMetric notePadMetric(this->notePadForm);
	GlyphFactory glyphFactory;
	glyph = glyphFactory.MakeGlyph(buffer);

	if (this->notePadForm->row->GetCurrent() == this->notePadForm->row->GetLength()) {
		this->notePadForm->row->Add(glyph);
	}
	else {
		this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
	}
}

void Paster::PasteSingleByteCharacterInRowForUnDoReDo(char(*buffer)) {
	GlyphFactory glyphFactory;
	Glyph* glyph;
	NotePadMetric notePadMetric(this->notePadForm);
	Long hPosition = 0;
	TextMetric textMetric(this->notePadForm);

	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	glyph = glyphFactory.MakeGlyph(buffer);
	if (this->notePadForm->row->GetCurrent() == this->notePadForm->row->GetLength()) {
		this->notePadForm->row->Add(glyph);
	}
	else {
		this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
	}
}

void Paster::PasteTabInRowForUnDoReDo(char(*buffer)) {
	GlyphFactory glyphFactory;
	Glyph* glyph;
	NotePadMetric notePadMetric(this->notePadForm);

	Long hPosition = 0;
	TextMetric textMetric(this->notePadForm);

	Font font(this->notePadForm);
	TEXTMETRIC tm = { 0, };
	tm = font.CalculateFontMetric();

	Long i = 0;
	while (i < 8) {

		glyph = glyphFactory.MakeGlyph(buffer);
		if (this->notePadForm->row->GetCurrent() >= this->notePadForm->row->GetLength()) {
			this->notePadForm->row->Add(glyph);
		}
		else {
			this->notePadForm->row->Put(this->notePadForm->row->GetCurrent(), glyph);
		}
		i++;
	}
}