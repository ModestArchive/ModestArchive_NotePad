//MouseActionFactory.h

#ifndef _MOUSELBUTTONACTIONFACTORY_H
#define _MOUSELBUTTONACTIONFACTORY_H
#include<afxwin.h>
#include "MouseLButtonAction.h"

class MouseLButtonActionFactory{

public:
	MouseLButtonActionFactory(NotePadForm* notePadForm);
	~MouseLButtonActionFactory();
	MouseLButtonAction* MakeMouseAction();
private:
	NotePadForm* notePadForm;
};
#endif // !_MOUSELBUTTONACTIONFACTORY_H
