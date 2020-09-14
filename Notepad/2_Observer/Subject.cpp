//Subject.cpp

#include"Subject.h"
#include"Array.h"
#include "ArrayIterator.h"
#include"Observer.h"


Subject::Subject(Long capacity): observers(capacity) {//콜론초기화는 디폴트 생성자를 안부를때 하는거

	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
}


Subject:: ~Subject() {
	Long i = 0;
	while (i < this->length) {
		delete this->observers[i];
		i++;
	}
}


void Subject::Attach(Observer* observer) {
	
	Long i = 0;
	while (i<this->length && this->observers[i] != observer ) {

		i++;
	}

	if (i == this->length) {
		if (this->capacity > this->length) {
		    this->observers.Store(this->length, observer);
		}
		else {
			this->observers.AppendFromRear(observer);
			this->capacity++;
		}
		this->length++;
		this->current++;
	}
}


void Subject::AttachFromFront(Observer* observer) {
	
	this->observers.AppendFromFront(observer);
	
	this->capacity++;
	this->length++;
	this->current++;
	
}


void Subject::Detach(Observer* observer) {
	int CompareObservers(void* one, void* other);
	Long index= this->observers.LinearSearchUnique(observer, CompareObservers);

	this->observers.Delete(index);
	this->capacity--;
	this->length--;
	this->current--;
}


void Subject::Notify() {
	ArrayIterator<Observer*> arrayIterator(&this->observers);
	arrayIterator.First();
	while (arrayIterator.IsDone()!=true) {
		arrayIterator.CurrentItem()->Update(this);
		arrayIterator.Next();
	}
}


int CompareObservers(void* one, void* other){
	
	int ret = -1;
	if (*(static_cast<Observer**>(one))== static_cast<Observer*>(other)) {
		ret = 0;
	}

	return ret;
}