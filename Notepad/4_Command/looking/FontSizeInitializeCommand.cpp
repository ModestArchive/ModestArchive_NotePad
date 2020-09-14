//FontSizeInitializeCommand.cpp
#include"NotePadForm.h"
#include"FontSizeInitializeCommand.h"
#include"Font.h"
#include"Selector.h"


FontSizeInitializeCommand::FontSizeInitializeCommand(NotePadForm* notePadForm) :Command(notePadForm){
	this->notePadForm = notePadForm;
}


FontSizeInitializeCommand::~FontSizeInitializeCommand() {
	
}

void FontSizeInitializeCommand::Execute() {

	this->notePadForm->SetIsFontSizing(true);

	Font font;
	LOGFONT initialLogFont = font.MakeInitialLogFont();
	this->notePadForm->SetLogFont(initialLogFont);

	if (this->notePadForm->GetIsSelected()== TRUE) {

		if (this->notePadForm->GetSelector()->IsRightDownWardSelectedArea() == true) {
			this->notePadForm->GetSelector()->ReHighLightRightDownwardSumRegionMatchToClientArea();
		}
		else {
			this->notePadForm->GetSelector()->ReHighLightLeftUpwardSumRegionMatchToClientArea();
		}
	}
	
}