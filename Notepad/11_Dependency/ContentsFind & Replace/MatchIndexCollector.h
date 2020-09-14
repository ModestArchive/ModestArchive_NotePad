//MatchIndexCollector.h

#ifndef _MATCHINDEXCOLLECTOR_H
#define _MATCHINDEXCOLLECTOR_H

#include"Array.h"
class MatchIndex;
class MatchIndexCollector {
public:
	MatchIndexCollector(Long capacity = 1024);
	~MatchIndexCollector();
	Long AddMatchIndex(MatchIndex* matchIndex);
	MatchIndex* GetAt(Long index);
	Long MoveLastMatchIndex();
	Long MovePreviousMatchIndex();
	Long MoveNextMatchIndex();
	Long MoveFirstMatchIndex();
	//인라인 함수
	Long GetCapacity() const;
	Long GetLength() const;
	Long GetCurrent() const;
private:
	Array<MatchIndex*>matchIndexes;
	Long capacity;
	Long length;
	Long current;
};

inline Long MatchIndexCollector::GetCapacity() const {
	return this->capacity;
}
inline Long MatchIndexCollector::GetLength() const{
	return this->length;
}
inline Long MatchIndexCollector::GetCurrent() const {
	return this->current;
}
#endif // !_MATCHINDEXCOLLECTOR_H


