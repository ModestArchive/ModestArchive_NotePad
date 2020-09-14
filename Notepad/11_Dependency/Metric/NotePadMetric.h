//NotePadMetric.h

#ifndef _NOTEPADMETRIC_H
#define _NOTEPADMETRIC_H

class NotePadForm;
class Glyph;
typedef signed long int Long;

class NotePadMetric {
public:
	NotePadMetric(NotePadForm* notePadForm = 0);
	~NotePadMetric();

	bool IsRowShorterThanClientAreaX(Glyph* row, Long hPos);
	Long GetFirstColumnIndexInClientArea(Glyph* row, Long hPos);
	bool IsRowLongerThanClientAreaX(Glyph* row, Long hPosPlusClientArea);
	Long GetFirstColumnIndexOverClientArea(Glyph* row, Long hPosPlusClientArea);
	Long GetFirstColumnIndexOverClientAreaForPrint(Glyph* row,Long viewerPortHorzOrg ,Long hPosPlusClientArea);
	bool IsNotePadLongerThanClientAreaY(Long index, Long vPosPlusClientArea);
	Long GetFirstRowIndexOverClientArea(Long index, Long vPosPlusClientArea);
	Long GetFirstRowIndexInClientArea(Long vPos);
	Long GetLongestX();
	Long GetLongestXRowIndex();
	Long GetClientLongestX();
	Long GetClientLongestXRowIndex();
	Long GetFirstTabColumnIndexWhenTabBeyondClientArea(Glyph* row,Long firstColumnIndexOverClientArea);
	Long GetRemainClientWidthArea(Glyph* row,Long clientWidthArea);
	Long GetAddibleCharacterNumberProportionalToRemainWidthClientArea(Glyph* row, Long remainClientArea);
	//추가적인 기능들.
	Long MoveClientLongestXRow(Long clientLongestXRowIndex, Long vPos);//
	Long MoveLongestXRow(Long LongestXRowIndex, Long vPos);
	void MoveColumnOverHPos(Long hPos);
	void MoveVScrollAfterAddedContents();
	void MoveVScrollAfterRemovedContents(bool isNotePadLengthDiffer);
	void MoveVScrollAfterOnSizingWhenAutoLineBreakOn();
	bool GetThereIsContents();
	Long GetTotalLengthToCurrent();
	Long GetTotalLengthToDesignatedCoordinate(Long rowIndex, Long columnIndex);
	void MoveHScrollAndSelectionAfterFindMatchContents();
	void MoveVScrollAndSelectionAfterFindMatchContents();
	Long GetHowManyTabInToCurrentColumnInCurrentRow();
	
private:
	NotePadForm* notePadForm;
};
#endif // !_NOTEPADMETRIC_H

