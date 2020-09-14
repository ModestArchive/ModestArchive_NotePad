//HScrollCodeActionFactory.h

#ifndef _HSCROLLCODEACTIONFACTORY_H
#define _HSCROLLCODEACTIONFACTORY_H

class NotePadForm;
class HScrollCodeAction;
typedef unsigned int UINT;

class   HScrollCodeActionFactory {
public:
	HScrollCodeActionFactory(NotePadForm* notePadForm= 0);
	~HScrollCodeActionFactory();
	HScrollCodeAction* MakeCodeAction(UINT nSBCode);

private:
	NotePadForm* notePadForm;
};
#endif // !_HSCROLLCODEACTIONFACTORY_H

