//ConstraintSolver.h

#ifndef _CONSTRAINTSOLVER_H
#define _CONSTRAINTSOLVER_H

class ConstraintSolverMemento;
class NotePadState;
class NotePadForm;
typedef signed long int Long;
class ConstraintSolver {

public:
	ConstraintSolver(NotePadForm* notePadForm = 0, NotePadState* notePadState=0);
	~ConstraintSolver();
	void SolveUnDoingWriteConstraint();
	void SolveUnDoingRemoveConstraint();
	void SolveUnDoingPasteConstraint(Long rowIndexRelatedWithAfterAction,Long columnIndexRelatedWithAfterAction);
	void SolveUnDoingCutOutConstraint();
	void SolveUnDoingSelectionErasedBeforeActionConstraint();
	void SolveReDoingWriteConstraint();
	void SolveReDoingRemoveConstraint();
	void SolveReDoingPasteConstraint();
	void SolveReDoingCutOutConstraint(Long rowIndexRelatedWithBeforeAction, Long columnIndexRelatedWithBeforeAction);
	void SolveReDoingSelectionErasedBeforeActionConstraint(Long rowIndexRelatedWithBeforeAction, Long columnIndexRelatedWithBeforeAction);
	ConstraintSolverMemento* CreateConstraintSolverMemento();
	void SetMemento(ConstraintSolverMemento* constraintSolverMemento);
	//인라인함수
	NotePadState* GetNotePadState() const;
private:
	NotePadForm* notePadForm;
	NotePadState* notePadState;
};

inline NotePadState* ConstraintSolver::GetNotePadState() const {
	return const_cast<NotePadState*>(this->notePadState);
}
#endif // !_CONSTRAINTSOLVER_H

