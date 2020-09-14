//VScrollCodeActionFactory.h

#ifndef _VSCROLLCODEACTIONFACTORY_H
#define _VSCROLLCODEACTIONFACTORY_H

class VScrollCodeAction;
class NotePadForm;
typedef unsigned int UINT;

class VScrollCodeActionFactory {
public:
	VScrollCodeActionFactory(NotePadForm* notePadForm=0);
	~VScrollCodeActionFactory();
	VScrollCodeAction* MakeCodeAction(UINT nSBCode);

private:
	NotePadForm* notePadForm;
};
#endif // !_VSCROLLCODEACTIONFACTORY_H


