//MouseWheelActionFactory.h

#ifndef  _MOUSEWHEELACTIONFACTORY_H
#define  _MOUSEWHEELACTIONFACTORY_H

class MouseWheelAction;
class NotePadForm;

class MouseWheelActionFactory {
public:
	MouseWheelActionFactory(NotePadForm* notePadForm=0);
	~MouseWheelActionFactory();
	MouseWheelAction* MakeMouseWheel(short zDelta,bool isControlPushing);

private:
	NotePadForm* notePadForm;

};
#endif // ! _MOUSEWHEELACTIONFACTORY_H

