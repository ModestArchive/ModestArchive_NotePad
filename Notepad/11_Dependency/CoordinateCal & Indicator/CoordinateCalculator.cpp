//CoordinateCalculator.cpp
#include"CoordinateCalculator.h"
#include"TextMetric.h"
#include"DummyRow.h"

CoordinateCalculator::CoordinateCalculator(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}

CoordinateCalculator::~CoordinateCalculator(){

}


CPoint CoordinateCalculator::CalculateCoordinateWithAbsoluteInformation(Long totalLengthToCurrent, Long rowCount) {
	TextMetric textMetric(this->notePadForm);
	Long processedRowLength = 0;
	Long i = 0;
	if (totalLengthToCurrent == 0) {//제일첫줄,첫칸은 입력길이 자체가 0이기때문에 위치계산할필요가 없으므로, 
		rowCount--;                 //위치에 영향을 주는 줄갯수도 0으로 맞춰준다.
	}
	while (totalLengthToCurrent > 0) {
		if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(i)) == 0) {
			rowCount--;
		}
		processedRowLength = textMetric.GetX(this->notePadForm->notePad->GetAt(i), this->notePadForm->notePad->GetAt(i)->GetLength());
		if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(i)) && ((DummyRow*)(this->notePadForm->notePad->GetAt(i)))->GetIsTabErased() == true) {
			processedRowLength += textMetric.GetTextWidth(32) * 8;
		}
		i++;
		totalLengthToCurrent -= processedRowLength;
	}
	if (i > 0) {//첫번째줄 첫번째 칸일경우 위치를 구할필요가 없으므로, 위치를 나타내는 변수에 영향을 주면 안된다.
		i--;
	}
	processedRowLength += totalLengthToCurrent;
	Long lengthToColumnIndex = processedRowLength;
	Long columnIndex = 0;
	Long charLength = 0;
	Long currentGetX = 0;
	Long beforeGetX = 0;
	if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(i)) &&
		((DummyRow*)(this->notePadForm->notePad->GetAt(i)))->GetIsTabErased() == true) {
		lengthToColumnIndex -= textMetric.GetTextWidth(32) * 8;
	}
	while (lengthToColumnIndex > 0) {
		columnIndex++;
		currentGetX = textMetric.GetX(this->notePadForm->notePad->GetAt(i), columnIndex);
		charLength = currentGetX - beforeGetX;
		lengthToColumnIndex -= charLength;
		beforeGetX = currentGetX;
	}
	while (rowCount > 0) {
		i++;
		columnIndex = 0;
		rowCount--;
	}
	CPoint coordinate(columnIndex, i);
	return coordinate;
}
