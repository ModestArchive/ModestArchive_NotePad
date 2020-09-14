//PasteSupervisor.cpp
#include"PasteSupervisor.h"
#include"Paster.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"TextMetric.h"
#include"GlyphFactory.h"
#include"DummyRow.h"
#include"NotePadMetric.h"
#include"Font.h"


PasteSupervisor::PasteSupervisor(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}


PasteSupervisor::~PasteSupervisor() {

}


void PasteSupervisor::PasteContents(char(*contents)) {
	Paster paster(this->notePadForm);

	Long i = 0;
	while (contents[i] != '\0') {//문자열끝에 도달할때까지 반복한다.

		if (contents[i] == '\r') {
			paster.PasteRowInNotePad();
			if (contents[i+1]== '\0' || contents[i+1]!='\n' ) {
				i++;
			}
			else {
				i += 2;
			}
		}
		else if (contents[i] & 0x80) {
			TCHAR buffer[3];
			buffer[0] = contents[i];
			buffer[1] = contents[i + 1];
			buffer[2] = '\0';
			paster.PasteDoubleByteCharacterInRow(buffer);
			i += 2;
		}
		else {
			TCHAR buffer[2];
			buffer[0] = contents[i];
			buffer[1] = '\0';
			if (contents[i] != '\t') {
				paster.PasteSingleByteCharacterInRow(buffer);
				i++;
			}
			else {
				paster.PasteTabInRow(buffer);
				i++;
			}
		}
	}
}

void PasteSupervisor::PasteContentsForUnDoReDo(char(*contents)) {
	Paster paster(this->notePadForm);

	Long i = 0;
	while (contents[i] != '\0') {//문자열끝에 도달할때까지 반복한다.

		if (contents[i] == '\r') {
			paster.PasteRowInNotePadForUnDoReDo();
			i += 2;
		}
		else if (contents[i] & 0x80) {
			TCHAR buffer[3];
			buffer[0] = contents[i];
			buffer[1] = contents[i + 1];
			buffer[2] = '\0';
			paster.PasteDoubleByteCharacterInRowForUnDoReDo(buffer);
			i += 2;
		}
		else {
			TCHAR buffer[2];
			buffer[0] = contents[i];
			buffer[1] = '\0';
			if (contents[i] != '\t') {
				paster.PasteSingleByteCharacterInRowForUnDoReDo(buffer);
				i++;
			}
			else {
				paster.PasteTabInRowForUnDoReDo(buffer);
				i++;
			}
		}
	}
}