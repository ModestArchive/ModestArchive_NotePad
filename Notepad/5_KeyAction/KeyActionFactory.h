//KeyActionFactory.h

#ifndef _KEYACTIONFACTORY_H
#define _KEYACTIONFACTORY_H
#include<afxwin.h>
#include "KeyAction.h"
class KeyActionFactory {

public:
	KeyActionFactory();
	KeyActionFactory(NotePadForm* notePadForm);
	~KeyActionFactory();
	KeyAction* MakeKey(UINT nChar);
private:
	NotePadForm* notePadForm;
};
#endif // !_KEYACTIONFACTORY_H
