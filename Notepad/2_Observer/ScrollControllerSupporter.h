//ScrollControllerSupporter.h

#ifndef _SCROLLCONTROLLERSUPPORTER_H
#define _SCROLLCONTROLLERSUPPORTER_H

#include"NotePadForm.h"
#include"ScrollController.h"

class ScrollControllerSupporter {
public:
	ScrollControllerSupporter(NotePadForm* notePadForm, ScrollController* scrollController);
	~ScrollControllerSupporter();

	void MoveHScrollForFindingContents();
	void MoveVScrollForFindingContents();
	void MoveHScrollToCurrent();
	void MoveVScrollToCurrent();

private:
	NotePadForm* notePadForm;
	ScrollController* scrollController;
};
#endif // !_SCROLLCONTROLLERSUPPORTER_H


