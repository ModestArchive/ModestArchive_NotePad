//Observer.h
#ifndef OBSERVER_H
#define OBSERVER_H

#include"NotePadForm.h"
class Subject;

class Observer {

public:
	
	virtual ~Observer();
	virtual void Update(Subject* theChangedSubject)=0;
	
protected:

	Observer();
	
};
#endif // _OBSERVER_H
