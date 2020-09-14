//HScrollCodeActionFactory.cpp

#include "HScrollCodeActionFactory.h"
#include "HLeftCode.h"
#include "HEndScrollCode.h"
#include "HLineLeftCode.h"
#include "HLineRightCode.h"
#include "HPageLeftCode.h"
#include "HPageRightCode.h"
#include "HRightCode.h"
#include "HThumbPositionCode.h"
#include "HThumbTrackCode.h"
#include<afxwin.h>

HScrollCodeActionFactory::HScrollCodeActionFactory(NotePadForm* notePadForm) {
	this->notePadForm= notePadForm;
}

HScrollCodeActionFactory::~HScrollCodeActionFactory() {

}

HScrollCodeAction* HScrollCodeActionFactory::MakeCodeAction(UINT nSBCode) {
	HScrollCodeAction* hScrollCodeAction = 0;

	if (nSBCode==SB_LEFT) {
		hScrollCodeAction = new HLeftCode(this->notePadForm);
	}
	else if (nSBCode == SB_RIGHT) {
		hScrollCodeAction = new HRightCode(this->notePadForm);
	}
	else if (nSBCode == SB_ENDSCROLL) {
		hScrollCodeAction = new HEndScrollCode(this->notePadForm);
	}
	else if (nSBCode == SB_LINELEFT) {
		hScrollCodeAction = new HLineLeftCode(this->notePadForm);
	}
	else if (nSBCode == SB_LINERIGHT) {
		hScrollCodeAction = new HLineRightCode(this->notePadForm);
	}
	else if (nSBCode == SB_PAGELEFT) {
		hScrollCodeAction = new HPageLeftCode(this->notePadForm);
	}
	else if (nSBCode == SB_PAGERIGHT) {
		hScrollCodeAction = new HPageRightCode(this->notePadForm);
	}
	else if (nSBCode == SB_THUMBPOSITION) {
		hScrollCodeAction = new HThumbPositionCode(this->notePadForm);
	}
	else if (nSBCode == SB_THUMBTRACK) {
		hScrollCodeAction = new HThumbTrackCode(this->notePadForm);
	}

	return hScrollCodeAction;
}