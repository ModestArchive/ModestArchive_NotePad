//ConstraintSolverMemento.h

#ifndef _CONSTRAINTSOLVERMEMENTO_H
#define _CONSTRAINTSOLVERMEMENTO_H

#include"ConstraintSolver.h"
class NotePadState;

class ConstraintSolverMemento {
public:
	virtual	~ConstraintSolverMemento();
private:
	friend class ConstraintSolver;
	ConstraintSolverMemento(NotePadState* notePadState);
	void SetState(NotePadState* notePadState);
	NotePadState* GetState();

private:
	NotePadState* notePadState;
};
#endif // !_CONSTRAINTSOLVERMEMENTO_H

