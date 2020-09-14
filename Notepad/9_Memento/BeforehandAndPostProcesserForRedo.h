//BeforehandAndPostProcesserForRedo.h

#ifndef _BEFOREHANDANDPOSTPROCESSERFORREDO_H
#define _BEFOREHANDANDPOSTPROCESSERFORREDO_H

#include"NotePadForm.h"
#include"NotePadHistory.h"

class BeforehandAndPostProcesserForRedo {
public:
	BeforehandAndPostProcesserForRedo(NotePadForm* notePadForm, NotePadHistory* notePadHistory);
	~BeforehandAndPostProcesserForRedo();

	bool DoBeforehandProcessForRedo();
	void DoPostProcessForRedo();

private:
	NotePadForm* notePadForm;
	NotePadHistory* notePadHistory;
};
#endif // !_BEFOREHANDANDPOSTPROCESSERFORREDO_H
