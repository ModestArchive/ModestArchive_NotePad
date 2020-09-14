//MatchIndex.h
#ifndef _MATCHINDEX_H
#define _MATCHINDEX_H
typedef signed long int Long;
class MatchIndex {
public:
	MatchIndex(Long startRowIndex,Long startColumnIndex,Long endRowIndex,Long endColumnIndex);
	~MatchIndex();
	MatchIndex& operator=(const MatchIndex& source);
	bool operator==(const MatchIndex& other);
	//인라인함수
	Long GetStartRowIndex() const;
	Long GetStartColumnIndex() const;
	Long GetEndRowIndex() const;
	Long GetEndColumnIndex() const;
private:
	Long startRowIndex;
	Long startColumnIndex;
	Long endRowIndex;
	Long endColumnIndex;
};

inline Long MatchIndex::GetStartRowIndex() const {
	return this->startRowIndex;
}
inline Long MatchIndex::GetStartColumnIndex() const {
	return this->startColumnIndex;
}
inline Long MatchIndex::GetEndRowIndex() const {
	return this->endRowIndex;
}
inline Long MatchIndex::GetEndColumnIndex() const {
	return this->endColumnIndex;
}
#endif // !_MATCHINDEX_H

