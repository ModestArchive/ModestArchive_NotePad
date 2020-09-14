//AutoLineBreak.h

#ifndef _AUTOLINEBREAK_H
#define _AUTOLINEBREAK_H
#include"Observer.h"

class NotePadForm;

class AutoLineBreak : public Observer {

public:
	AutoLineBreak(NotePadForm* notePadForm);
	~AutoLineBreak();
	virtual void Update(Subject* theChangedSubject);

private:
	NotePadForm* notePadForm;
};
#endif // !_AUTOLINEBREAK_H


