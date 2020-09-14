//FontConfigureCommand.cpp
#include"FontConfigureCommand.h"
#include"NotePadFormControlWnd.h"
#include"NotePad.h"
#include"Glyph.h"
#include"Selector.h"
#include<afxdlgs.h>



FontConfigureCommand::FontConfigureCommand(NotePadForm* notePadForm) :Command(notePadForm) {
	this->notePadForm = notePadForm;
}

FontConfigureCommand::~FontConfigureCommand() {

}

void FontConfigureCommand::Execute() {
	CFontDialog cFontDialog(&this->notePadForm->GetLogFont(), CF_EFFECTS | CF_SCREENFONTS, 0, 0);

	if (cFontDialog.DoModal() == IDOK) {
		LOGFONT logFont;
		logFont = *cFontDialog.m_cf.lpLogFont;

		this->notePadForm->SetLogFont(logFont);//�ּҷ� �ѱ�� ���ؾ������� lpLogFont�� ������ �����ְڳ��Ӹ� ������ �Ѱܾ���
		
	}
	this->notePadForm->GetNotePadFormControlWnd()->SetNoNeedToScroll(true);
	
	if (this->notePadForm->GetIsSelected() == TRUE) {

		if (this->notePadForm->GetSelector()->IsRightDownWardSelectedArea() == true) {
			this->notePadForm->GetSelector()->ReHighLightRightDownwardSumRegionMatchToClientArea();
		}
		else {
			this->notePadForm->GetSelector()->ReHighLightLeftUpwardSumRegionMatchToClientArea();
		}
	}
}