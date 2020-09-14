//FontSizeExpandCommand.cpp
#include"FontSizeExpandCommand.h"
#include"NotePadForm.h"
#include"Font.h"
#include"Selector.h"

FontSizeExpandCommand::FontSizeExpandCommand(NotePadForm* notePadForm) :Command(notePadForm){
	this->notePadForm = notePadForm;
}


FontSizeExpandCommand::~FontSizeExpandCommand() {

}

void FontSizeExpandCommand::Execute() {

	this->notePadForm->SetIsFontSizing(true);

	LOGFONT expandLogfont = this->notePadForm->GetLogFont();
	expandLogfont.lfHeight -= 20;
	if (expandLogfont.lfHeight<-300) {
		expandLogfont.lfHeight = -300;
	}
	this->notePadForm->SetLogFont(expandLogfont);
	if (this->notePadForm->GetIsSelected() == TRUE) {

		if (this->notePadForm->GetSelector()->IsRightDownWardSelectedArea() == true) {
			this->notePadForm->GetSelector()->ReHighLightRightDownwardSumRegionMatchToClientArea();
		}
		else {
			this->notePadForm->GetSelector()->ReHighLightLeftUpwardSumRegionMatchToClientArea();
		}
	}
}