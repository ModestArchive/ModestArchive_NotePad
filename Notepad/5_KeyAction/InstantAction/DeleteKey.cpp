//DeleteKey.cpp
#include"DeleteKey.h"
#include"SelectionEraseSupervisor.h"
#include"Selector.h"
#include"SingleByteCharacter.h"
#include"Glyph.h"
#include"NotePadMaker.h"
#include"ScrollController.h"
#include"DummyRow.h"
#include"StringMaker.h"
#include"NotePadMetric.h"
#include"NotePadModifier.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"

DeleteKey::DeleteKey(NotePadForm* notePadForm) :KeyAction(notePadForm) {

}


DeleteKey::~DeleteKey() {

}


void DeleteKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	NotePadMaker notePadMaker(this->notePadForm);
	if (this->notePadForm->GetIsSelected() == true) {
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
		NotePadMetric notePadMetric(this->notePadForm);
		NotePadModifier notePadModifier(this->notePadForm);
		CoordinateCalculator coordinateCalculator(this->notePadForm);
		NotePadIndicator notePadIndicator(this->notePadForm);

		Long rowCountFromStartToCurrent = notePadModifier.CountRowFromStartToCurrent();
		Long totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
		notePadModifier.Combine();
		CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCountFromStartToCurrent);
		notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);

		if (this->notePadForm->notePad->GetCurrent() < this->notePadForm->notePad->GetLength() - 1 &&
			this->notePadForm->row->GetCurrent() == this->notePadForm->row->GetLength()) {
			if (dynamic_cast<DummyRow*>(this->notePadForm->row)) {
				notePadMaker.EraseCurrentCharactorInRow();
			}
			else {
				notePadMaker.EraseNextRowInNotePad();
			}
		}
		else if (this->notePadForm->row->GetCurrent() < this->notePadForm->row->GetLength()) {
			notePadMaker.EraseCurrentCharactorInRow();
		}
	}
}