//NewFileMakeCommand.cpp
#include"NewFileMakeCommand.h"
#include"NotePadFormControlWnd.h"
#include"GlyphFactory.h"
#include"Glyph.h"
#include"File.h"
#include"CMyDialog.h"
#include"NotePad.h"


NewFileMakeCommand::NewFileMakeCommand(NotePadFormControlWnd* notePadFormControlWnd, NotePadForm* notePadForm) :Command(notePadForm){
	this->notePadFormControlWnd = notePadFormControlWnd;
	this->notePadForm = notePadForm;
}

NewFileMakeCommand::~NewFileMakeCommand() {

}


void NewFileMakeCommand::Execute() {
	File file(this->notePadForm);
	string contents = "";
	string fileContents = "";
	string nullString = "";
	string originalBuffer = " 제목 없음 - 메모장 ";
	string captionBuffer = "";
	this->notePadFormControlWnd->GetWindowText((char*)captionBuffer.c_str(), 100);
	int ret = -1;

	if (strcmp((char*)captionBuffer.c_str(), (char*)originalBuffer.c_str()) == 0) {
		if (strcmp((char*)this->notePadForm->notePad->GetContents().c_str(), (char*)nullString.c_str()) != 0) {
			CMyDialog cMyDialog(this->notePadForm);
			ret = cMyDialog.DoModal();
		}
		else {
			ret = 0;
		}
	}
	else {
		contents = ((NotePad*)(this->notePadForm->notePad))->SaveModeGetContents();
		fileContents = file.Load((char*)this->notePadForm->GetFilePath().c_str());
		if (strcmp((char*)contents.c_str(), (char*)fileContents.c_str()) != 0) {
			CMyDialog cMyDialog(this->notePadForm);
			ret = cMyDialog.DoModal();
		}
		else {
			ret = 0;
		}
	}
	if (ret==0) {
		this->notePadFormControlWnd->SetWindowText(originalBuffer.c_str());
		if (this->notePadForm->notePad != 0) {
			delete this->notePadForm->notePad;
		}
		GlyphFactory glyphFactory;
		this->notePadForm->notePad = glyphFactory.MakeGlyph((char*)(""));
		this->notePadForm->row = glyphFactory.MakeGlyph((char*)("\r\n"));
		this->notePadForm->notePad->Add(this->notePadForm->row);
		this->notePadForm->notePad->First();
		this->notePadForm->row->First();
	}
	else {
		this->notePadFormControlWnd->SetNoNeedToScroll(true);
	}

}