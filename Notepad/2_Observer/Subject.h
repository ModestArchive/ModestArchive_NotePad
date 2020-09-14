//Subject.h

#ifndef _SUBJECT_H
#define _SUBJECT_H
#include"Array.h"


class Observer;

class Subject {
public:
	virtual ~Subject();
	virtual void Attach(Observer* observer);
	virtual void AttachFromFront(Observer* observer);
	virtual void Detach(Observer* observer);
	virtual void Notify();

protected:

	Subject(Long capacity=256);

private:

	Array<Observer*> observers ;
	Long capacity;
	Long length;
	Long current;

};

	
#endif // _SUBJECT_H

