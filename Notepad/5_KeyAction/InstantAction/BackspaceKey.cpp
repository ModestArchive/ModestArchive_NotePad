//BackspaceKey.cpp

#include"BackspaceKey.h"
#include"SelectionEraseSupervisor.h"
#include"Selector.h"
#include"SingleByteCharacter.h"
#include"Glyph.h"
#include"GlyphFactory.h"
#include"TextMetric.h"
#include"NotePadMetric.h"
#include"Font.h"
#include"ScrollController.h"
#include"NotePadMaker.h"
#include"DummyRow.h"
#include"StringMaker.h"


BackspaceKey::BackspaceKey(NotePadForm* notePadForm):KeyAction(notePadForm){

}


BackspaceKey::~BackspaceKey() {

}


void BackspaceKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	
	NotePadMaker notePadMaker(this->notePadForm);
	if (this->notePadForm->GetIsSelected()==true) {
		SelectionEraseSupervisor selectionEraseSupervisor(this->notePadForm);
		StringMaker stringMaker(this->notePadForm);
		string* contents = new string(stringMaker.MakeStringInSelectedArea());
		selectionEraseSupervisor.EraseContents(contents, true);
		
		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetSelector() != 0) {
			delete this->notePadForm->GetSelector();
		}
		Selector* selector = new Selector(this->notePadForm);
		this->notePadForm->SetSelector(selector);
	}
	else {

		if (this->notePadForm->notePad->GetCurrent() != 0 || this->notePadForm->row->GetCurrent() != 0) {
			this->notePadForm->SetIsBackRemove(true);

			if (this->notePadForm->row->GetCurrent() == 0 && this->notePadForm->notePad->GetCurrent() > 0) {
				if (dynamic_cast<DummyRow*>(this->notePadForm->row)) {
					notePadMaker.ErasePreviousCharacterInRow();
				}
				else {
					notePadMaker.EraseCurrentRowInNotePad();
				}
			}
			else if (this->notePadForm->row->GetCurrent() > 0) {
				notePadMaker.ErasePreviousCharacterInRow();
			}
		}
	}
}