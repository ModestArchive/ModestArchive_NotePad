//FontDownsizeCommand.cpp

#include"NotePadForm.h"
#include"FontSizeDownsizeCommand.h"
#include"Font.h"
#include"Selector.h"

FontSizeDownsizeCommand::FontSizeDownsizeCommand(NotePadForm* notePadForm) :Command(notePadForm){
	this->notePadForm = notePadForm;
}
FontSizeDownsizeCommand::~FontSizeDownsizeCommand() {

}
//¸Þ¼Òµå
void FontSizeDownsizeCommand::Execute() {

	this->notePadForm->SetIsFontSizing(true);

	LOGFONT downsizeLogfont = this->notePadForm->GetLogFont();
	downsizeLogfont.lfHeight += 20;
	if (downsizeLogfont.lfHeight > 20) {
		downsizeLogfont.lfHeight = 20;
	}
	this->notePadForm->SetLogFont(downsizeLogfont);
	if (this->notePadForm->GetIsSelected() == TRUE) {

		if (this->notePadForm->GetSelector()->IsRightDownWardSelectedArea() == true) {
			this->notePadForm->GetSelector()->ReHighLightRightDownwardSumRegionMatchToClientArea();
		}
		else {
			this->notePadForm->GetSelector()->ReHighLightLeftUpwardSumRegionMatchToClientArea();
		}
	}
}
