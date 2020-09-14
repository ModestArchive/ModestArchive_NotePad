//VScrollCodeActionFactory.cpp

#include"VScrollCodeActionFactory.h"
#include "VBottomCode.h"
#include "VTopCode.h"
#include "VEndScrollCode.h"
#include "VLineDownCode.h"
#include "VLineUpCode.h"
#include "VPageDownCode.h"
#include "VPageUpCode.h"
#include "VThumbPositionCode.h"
#include "VThumbTrackCode.h"
#include<afxwin.h>

VScrollCodeActionFactory::VScrollCodeActionFactory(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}

VScrollCodeActionFactory::~VScrollCodeActionFactory() {

}

VScrollCodeAction* VScrollCodeActionFactory::MakeCodeAction(UINT nSBCode) {
	VScrollCodeAction* vScrollCodeAction = 0;

	if (nSBCode == SB_BOTTOM) {
		vScrollCodeAction = new VBottomCode(this->notePadForm);
	}
	else if (nSBCode == SB_ENDSCROLL) {
		vScrollCodeAction = new VEndScrollCode(this->notePadForm);
	}
	else if (nSBCode == SB_LINEDOWN) {
		vScrollCodeAction = new VLineDownCode(this->notePadForm);
	}
	else if (nSBCode == SB_LINEUP) {
		vScrollCodeAction = new VLineUpCode(this->notePadForm);
	}
	else if (nSBCode ==SB_PAGEDOWN) {
		vScrollCodeAction = new VPageDownCode(this->notePadForm);
	}
	else if (nSBCode == SB_PAGEUP) {
		vScrollCodeAction = new VPageUpCode(this->notePadForm);
	}
	else if (nSBCode == SB_TOP) {
		vScrollCodeAction = new VTopCode(this->notePadForm);
	}
	else if (nSBCode == SB_THUMBPOSITION) {
		vScrollCodeAction = new VThumbPositionCode(this->notePadForm);
	}
	else if (nSBCode == SB_THUMBTRACK) {
		vScrollCodeAction = new VThumbTrackCode(this->notePadForm);
	}

	return vScrollCodeAction;
}