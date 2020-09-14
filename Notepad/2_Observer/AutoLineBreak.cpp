//AutoLineBreak.cpp

#include"AutoLineBreak.h"
#include"NotePadModifier.h"
#include"NotePadMetric.h"
#include"CoordinateCalculator.h"
#include"NotePadIndicator.h"
#include"Selector.h"
#include"SelectModifier.h"
#include"SelectedAreaMetric.h"
#include"Glyph.h"
#include"NotePadFormControlWnd.h"
#include"MatchIndexCollector.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif
AutoLineBreak::AutoLineBreak(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
    ((Subject*)(this->notePadForm))->AttachFromFront(this);
}


AutoLineBreak::~AutoLineBreak() {
	((Subject*)(this->notePadForm))->Detach(this);
}


void AutoLineBreak::Update(Subject* theChangedSubject) {
	if (this->notePadForm == theChangedSubject) {
		NotePadModifier notePadModifier(this->notePadForm);
		NotePadMetric notePadMetric(this->notePadForm);
		CoordinateCalculator coordinateCalculator(this->notePadForm);
		NotePadIndicator notePadIndicator(this->notePadForm);
		//항상 뭔가 new해주었으면 할당해제를 어느 타이밍에 해줘야할지도 생각해줘야함~
		Long rowCount = 0;
		Long totalLengthToCurrent = 0;
		if (this->notePadForm->GetIsAutoLineBreak() == false) {
			notePadModifier.Split();
			this->notePadForm->SetIsAutoLineBreak(true);
		}
		else if(this->notePadForm->GetNoNeedToAutoLineBreak()==false){
			bool isSelected = this->notePadForm->GetIsSelected();
			bool isOnSizing = this->notePadForm->GetIsOnSizing();
			
			if (isSelected==true && (isOnSizing==true||this->notePadForm->GetIsFontSizing()==true)) {
				SelectedAreaMetric selectedAreaMetric(this->notePadForm->GetSelector());
				SelectModifier selectModifier(this->notePadForm->GetSelector());
				
				selectModifier.SetAbsoluteSelectionInformation();
				
				bool isFirstLineInSelectedAreaDummyRowBeforeAutoLineBreak = false;
				bool isFirstLineInSelectedAreaDummyRowAfterAutoLineBreak = false;
				bool isRightDownWardSelectedArea = this->notePadForm->GetSelector()->IsRightDownWardSelectedArea();

				Long rowCountInSelectedArea = selectModifier.CountRowInSelectedArea();
				Long rowCountInFirstToSelectedAreaStartPoint = selectModifier.CountRowInFirstToSelectedAreaStartPoint();
				if (isRightDownWardSelectedArea==true) {
					isFirstLineInSelectedAreaDummyRowBeforeAutoLineBreak = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetOriginRowIndex());
				}
				else {
					isFirstLineInSelectedAreaDummyRowBeforeAutoLineBreak = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetEndRowIndex());
				}
			
				rowCount = notePadModifier.CountRowFromStartToCurrent();
				totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
				notePadModifier.Combine();
				notePadModifier.Split();
				CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
				notePadIndicator.GoToCoordinate(cPoint.y,cPoint.x);

				
				if (isRightDownWardSelectedArea==true) {
					selectModifier.ChangeRightDownwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
					isFirstLineInSelectedAreaDummyRowAfterAutoLineBreak = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetOriginRowIndex());
					if (isFirstLineInSelectedAreaDummyRowBeforeAutoLineBreak==true&&isFirstLineInSelectedAreaDummyRowAfterAutoLineBreak==false) {
						rowCountInSelectedArea++;
					}
					else if(isFirstLineInSelectedAreaDummyRowBeforeAutoLineBreak==false&&isFirstLineInSelectedAreaDummyRowAfterAutoLineBreak == true) {
						rowCountInSelectedArea--;
					}
					selectModifier.ChangeRightDownwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
					this->notePadForm->GetSelector()->ReHighLightRightDownwardSumRegionMatchToClientArea();
				}
				else {
					selectModifier.ChangeLeftUpwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
					isFirstLineInSelectedAreaDummyRowAfterAutoLineBreak = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetEndRowIndex());
					if (isFirstLineInSelectedAreaDummyRowBeforeAutoLineBreak == true && isFirstLineInSelectedAreaDummyRowAfterAutoLineBreak == false) {
						rowCountInSelectedArea++;
					}
					else if (isFirstLineInSelectedAreaDummyRowBeforeAutoLineBreak == false && isFirstLineInSelectedAreaDummyRowAfterAutoLineBreak == true) {
						rowCountInSelectedArea--;
					}
					selectModifier.ChangeLeftUpwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
					this->notePadForm->GetSelector()->ReHighLightLeftUpwardSumRegionMatchToClientArea();
				}
			}
			else {
				if(this->notePadForm->GetIsSelected()==true&& 
				   (this->notePadForm->GetIsUnDoing()==true||
				    this->notePadForm->GetIsReDoing()==true||
					(this->notePadForm->GetNotePadFormControlWnd()->GetContentsFinder() != 0 && this->notePadForm->GetNotePadFormControlWnd()->GetContentsFinder()->GetMatchIndexCollector()->GetLength() > 0))){

					SelectModifier selectModifier(this->notePadForm->GetSelector());
					Long rowCountInFirstToSelectedAreaStartPoint = selectModifier.CountRowInFirstToSelectedAreaStartPoint();
					Long rowCountInSelectedArea = selectModifier.CountRowInSelectedArea();
					
					rowCount = notePadModifier.CountRowFromStartToCurrent();
					totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
					notePadModifier.Combine();
					notePadModifier.Split();
					CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
					notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
					
					selectModifier.ChangeRightDownwardSelectedAreaStartPointAfterAction(rowCountInFirstToSelectedAreaStartPoint);
			
					bool isFirstLineInSelectedAreaDummyRow = selectModifier.isFirstLineInSelectedAreaDummyRow(this->notePadForm->GetSelector()->GetOriginRowIndex());
					if (isFirstLineInSelectedAreaDummyRow==true) {
						rowCountInSelectedArea--;
					}
					selectModifier.ChangeRightDownwardSelectedAreaEndPointAfterAction(rowCountInSelectedArea);
					this->notePadForm->GetSelector()->ReHighLightRightDownwardSumRegionMatchToClientArea();
				}
				else {
					rowCount = notePadModifier.CountRowFromStartToCurrent();
					totalLengthToCurrent = notePadMetric.GetTotalLengthToCurrent();
					notePadModifier.Combine();
					notePadModifier.Split();
					CPoint cPoint = coordinateCalculator.CalculateCoordinateWithAbsoluteInformation(totalLengthToCurrent, rowCount);
					notePadIndicator.GoToCoordinate(cPoint.y, cPoint.x);
				}
			}
		}
	}
}