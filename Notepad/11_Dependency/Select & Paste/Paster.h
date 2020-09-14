//Paster.h

#ifndef _PASTER_H
#define _PASTER_H

#include"NotePadForm.h"

class Paster {
public:
	Paster(NotePadForm* notePadForm = 0);
	~Paster();
	void PasteRowInNotePad();
	void PasteDoubleByteCharacterInRow(char(*buffer));
	void PasteSingleByteCharacterInRow(char(*buffer));
	void PasteTabInRow(char(*buffer));

	void PasteRowInNotePadForUnDoReDo();
	void PasteDoubleByteCharacterInRowForUnDoReDo(char(*buffer));
	void PasteSingleByteCharacterInRowForUnDoReDo(char(*buffer));
	void PasteTabInRowForUnDoReDo(char(*buffer));
	
private:
	NotePadForm* notePadForm;
};
#endif // !_PASTER_H

