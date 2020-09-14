//MouseLButtonOneClick.cpp
#include"MouseLButtonOneClick.h"
#include"NotePadForm.h"
#include"TextMetric.h"
#include"SingleByteCharacter.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"Font.h"
#include"MouseTrackTextMetric.h"
#include"Selector.h"
#include"NotePadFormControlWnd.h"
#include"FindReplaceSupervisor.h"


MouseLButtonOneClick::MouseLButtonOneClick(NotePadForm* notePadForm) :MouseLButtonAction(notePadForm){

}


MouseLButtonOneClick::~MouseLButtonOneClick() {

}


void MouseLButtonOneClick::OnLButtonDown(UINT nFlags, CPoint point) {
	if (this->notePadForm->GetIsSelected()== true) {
		this->notePadForm->SetIsSelected(false);
		if (this->notePadForm->GetSelector()!= 0) {
			delete this->notePadForm->GetSelector();
		}
		this->notePadForm->SetSelector(new Selector(this->notePadForm));
		if (this->notePadForm->GetNotePadFormControlWnd()->GetContentsFinder() != 0) {
			FindReplaceSupervisor findReplaceSupervisor(this->notePadForm->GetNotePadFormControlWnd(), this->notePadForm,
				this->notePadForm->GetNotePadFormControlWnd()->GetContentsFinder(), 0, 0);
			findReplaceSupervisor.DeleteMatchIndexCollector();
		}
	}
	MouseTrackTextMetric mouseTrackTextMetric(this->notePadForm);
	mouseTrackTextMetric.TransferMouseCoordinateToNotePadLocation(nFlags, point);
	this->notePadForm->SetNoNeedToAutoLineBreak(true);
}