//MouseLButton.cpp

#include"MouseLButton.h"
#include"NotePadForm.h"
#include"TextMetric.h"
#include"SingleByteCharacter.h"
#include"Glyph.h"
#include"ScrollController.h"
#include"Font.h"
#include"MouseTrackTextMetric.h"

MouseLButton::MouseLButton(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}

MouseLButton::~MouseLButton() {

}

void MouseLButton::OnLButtonDown(UINT nFlags, CPoint point) {
	MouseTrackTextMetric mouseTrackTextMetric(this->notePadForm);
	mouseTrackTextMetric.TransferMouseCoordinateToNotePadLocation(nFlags, point);
	this->notePadForm->SetNoNeedToAutoLineBreak(true);
}