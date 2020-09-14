//PasteSupervisor.h

#ifndef _PASTESUPERVISOR_H
#define _PASTESUPERVISOR_H

#include"NotePadForm.h"

class PasteSupervisor {
public:
	PasteSupervisor(NotePadForm* notePadForm = 0);
	~PasteSupervisor();
	void PasteContents(char(*contents));
	void PasteContentsForUnDoReDo(char(*contents));

private:
	NotePadForm* notePadForm;
};
#endif // !_PASTESUPERVISOR_H


