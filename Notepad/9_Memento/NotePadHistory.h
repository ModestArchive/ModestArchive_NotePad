//NotePadHistory.h

#ifndef _NOTEPADHISTORY_H
#define _NOTEPADHISTORY_H
#include"Array.h"
typedef signed long int Long;

class ConstraintSolverMemento;
class NotePadHistory { 
public:
	NotePadHistory(Long capacity=1024);
	~NotePadHistory();
	Long AddHistory(ConstraintSolverMemento* ConstraintSolverMemento);
	Long PutHistory(Long index,ConstraintSolverMemento* constraintSolverMemento);
	Long RemoveHistory(Long index);
	ConstraintSolverMemento* GetAt(Long index);
	Long MoveLastHistory();
	Long MovePreviousHistory();
	Long MoveNextHistory();
	Long MoveFirstHistory();
	Long GetCapacity() const;
	Long GetLength() const;
	Long GetCurrent() const;

private:
	Array<ConstraintSolverMemento*> constraintSolverMementoes;
	Long capacity;
	Long length;
	Long current;
};

inline Long NotePadHistory::GetCapacity() const {
	return this->capacity;
}
inline Long NotePadHistory::GetLength() const {
	return this->length;
}
inline Long NotePadHistory::GetCurrent() const {
	return this->current;
}
#endif//_NOTEPADHISTORY_H