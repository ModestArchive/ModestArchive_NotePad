//ArrayIterator.h

#ifndef _ARRAYITERATOR_H
#define _ARRAYITERATOR_H
#include "ArrayIterator.h"
#include "Iterator.h"
#include "Composite.h"
#include "Glyph.h"
#include "Array.h"



template <typename T>
class ArrayIterator :public Iterator<T> {
public:
	ArrayIterator(Array<T> *aArray);
	virtual void First();
	virtual void Next();
	virtual void Previous();
	virtual bool IsDone() const;
	virtual T& CurrentItem() const;//����� ���Ǹ� �׻� �Ȱ��� ����!! ������ �ȵǸ� �װͺ��� ����!!!
	//�ζ����Լ�
	Long GetCurrent() const;

private:
	Array<T> *_array;
	Long _current;
	
};
template <typename T>
inline Long ArrayIterator<T> ::GetCurrent() const {
	return this->_current;
}
//�Լ�����
template<typename  T>
ArrayIterator<T> ::ArrayIterator(Array<T>* aArray) : _array(aArray), _current(0) {

}

template<typename  T>
void ArrayIterator<T> ::First() {
	this->_current = 0;
}
template<typename  T>
void ArrayIterator<T> ::Next() {
	this->_current++;
}

template<typename  T>
void ArrayIterator<T> ::Previous() {
	this->_current--;
}

template<typename  T>
bool ArrayIterator<T>::IsDone() const {
	return this->_current >= this->_array->GetLength();//�� �����İ� ����°��ڳ� �׷��� ������ �������;���
}

template<typename  T>
T& ArrayIterator<T> ::CurrentItem() const {
	
	return this->_array->GetAt(_current);
}

#endif//_ARRAYITERATOR_H