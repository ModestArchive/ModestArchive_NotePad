//SelectionJudge.cpp
#include"SelectionJudge.h"
#include"NotePadForm.h"
#include"Selector.h"
#include"SelectModifier.h"
#include"NotePadModifier.h"
#include"NotePadMetric.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
SelectionJudge::SelectionJudge(NotePadForm* notePadForm,Selector* selector) {
	this->notePadForm = notePadForm;
	this->selector = selector;
}


SelectionJudge::~SelectionJudge() {

}


void SelectionJudge::SelectionDecide() {
	bool isRightDownWardSelectedArea = false;
	bool isLeftUpwardSelectedArea = false;
	bool willNotSelected = false;
	if ((selector->GetOriginRowIndex() == selector->GetEndRowIndex() && selector->GetOriginColumnIndex() < selector->GetEndColumnIndex())
		|| (selector->GetOriginRowIndex() < selector->GetEndRowIndex())) {
		isRightDownWardSelectedArea = true;
	}
	else if ((selector->GetOriginRowIndex() == selector->GetEndRowIndex() && selector->GetOriginColumnIndex() > selector->GetEndColumnIndex())
		|| (selector->GetOriginRowIndex() > selector->GetEndRowIndex())) {
		isLeftUpwardSelectedArea = true;
	}

	if (isRightDownWardSelectedArea==false &&isLeftUpwardSelectedArea==false) {
		willNotSelected = true;
	}

	if (willNotSelected==false) {
		
		bool isFoward_FacingDirection;

		if (isRightDownWardSelectedArea == true) {
			if ((selector->GetStartRowIndex() == selector->GetEndRowIndex() && selector->GetStartColumnIndex() < selector->GetEndColumnIndex())
				|| (selector->GetStartRowIndex() < selector->GetEndRowIndex())) {
				isFoward_FacingDirection = true;
				selector->SetRegionForHighLightWithMouseRightDownard(isFoward_FacingDirection);
				this->notePadForm->SetIsSelected(true);
			}
			else if ((selector->GetStartRowIndex() == selector->GetEndRowIndex() && selector->GetStartColumnIndex() > selector->GetEndColumnIndex())
				|| (selector->GetStartRowIndex() > selector->GetEndRowIndex())) {
				isFoward_FacingDirection = false;
				selector->SetRegionForHighLightWithMouseRightDownard(isFoward_FacingDirection);
				this->notePadForm->SetIsSelected(true);
			}
		}
		else if (isLeftUpwardSelectedArea == true) {
			if ((selector->GetStartRowIndex() == selector->GetEndRowIndex() && selector->GetStartColumnIndex() < selector->GetEndColumnIndex())
				|| (selector->GetStartRowIndex() < selector->GetEndRowIndex())) {
				isFoward_FacingDirection = false;
				selector->SetRegionForHighLightWithMouseLeftUpward(isFoward_FacingDirection);
				this->notePadForm->SetIsSelected(true);
			}
			else if ((selector->GetStartRowIndex() == selector->GetEndRowIndex() && selector->GetStartColumnIndex() > selector->GetEndColumnIndex())
				|| (selector->GetStartRowIndex() > selector->GetEndRowIndex())) {
				isFoward_FacingDirection = true;
				selector->SetRegionForHighLightWithMouseLeftUpward(isFoward_FacingDirection);
				this->notePadForm->SetIsSelected(true);
			}
		}
	}
	else {
		if (this->notePadForm->GetIsSelected() == true) {
			this->notePadForm->SetIsSelected(false);
			if (this->notePadForm->GetSelector() != 0) {
				delete this->notePadForm->GetSelector();
			}
			Selector* selector = new Selector(this->notePadForm);
			this->notePadForm->SetSelector(selector);
		}
	}
}
