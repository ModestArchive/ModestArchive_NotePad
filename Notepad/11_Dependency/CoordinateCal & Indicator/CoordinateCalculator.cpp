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
	if (totalLengthToCurrent == 0) {//����ù��,ùĭ�� �Է±��� ��ü�� 0�̱⶧���� ��ġ������ʿ䰡 �����Ƿ�, 
		rowCount--;                 //��ġ�� ������ �ִ� �ٰ����� 0���� �����ش�.
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
	if (i > 0) {//ù��°�� ù��° ĭ�ϰ�� ��ġ�� �����ʿ䰡 �����Ƿ�, ��ġ�� ��Ÿ���� ������ ������ �ָ� �ȵȴ�.
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
