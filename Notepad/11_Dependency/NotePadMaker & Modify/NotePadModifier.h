//NotePadModifier.h

#ifndef _NOTEPADMODIFIER_H
#define _NOTEPADMODIFIER_H

class NotePadForm;
class Glyph;
typedef signed long int Long;

class NotePadModifier {
public:
	NotePadModifier(NotePadForm* notePadForm = 0);
	~NotePadModifier();
#if 0;
	void RelocateContentsInClientArea();
	void RelocateContentsInClientAreaAfterErasingAndAddCharacter();
	void RelocateContentsInClientAreaAfterEraseingAndAddTab();
	void RelocateContentsInClientAreaWhenHaveRemainClientArea();
	void AddNextRowContentsToCurrentRow(Glyph* nextRow);
#endif 0;
	void Combine();
	void Split();
	void SplitForPrinter(Long viewerPortHorzOrg,Long splitBoundary);
	Long CountRowFromStartToCurrent();
	Long CountRowFromStartToDesignatedRowIndex(Long designatedRowIndex);
	//Long CombineAfterAction();
	//void SplitAfterAction(Long rowCount,Long rowLength);
	
private:
	NotePadForm* notePadForm;

};
#endif // !_NOTEPADMODIFIER_H