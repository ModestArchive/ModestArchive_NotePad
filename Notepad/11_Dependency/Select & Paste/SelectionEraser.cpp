//SelectionEraser.cpp

#include"SelectionEraser.h"
#include"NotePadModifier.h"
#include"SelectModifier.h"
#include"SelectedAreaMetric.h"
#include"NotePadMaker.h"
#include"Selector.h"
#include"Glyph.h"
#include"NotePadIndicator.h"



SelectionEraser::SelectionEraser(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}


SelectionEraser::~SelectionEraser() {

}


void SelectionEraser::EraseSelectionContents() {

	Selector* selector = this->notePadForm->GetSelector();
	bool isRightDownwardSelectedArea = this->notePadForm->GetSelector()->IsRightDownWardSelectedArea();
	Long i = 0;//��ü ó���ؾ��� �ٰ����� ���� ����
	Long j = 0;//������� ó���� �ٰ����� ���� ����
	Long k = 0;//�����ϳ��� �������ٶ� �ݺ������
	Long l = 0;//�ٻ����� ������ �ݺ������!
	bool isFirstRowRemoved = false;
	Long erasedRowCount = 0;      
	Glyph* row = 0;
	Long rowLength = 0;
	
	if (isRightDownwardSelectedArea==true) {
		
		i = selector->GetEndRowIndex() - selector->GetOriginRowIndex() + 1;
		while (j<i) {
			if (i-1==0) {//�������� 1���̶���
				row = this->notePadForm->notePad->GetAt(selector->GetOriginRowIndex());
				while (k < selector->GetEndColumnIndex()-selector->GetOriginColumnIndex()) {
					row->Remove(selector->GetOriginColumnIndex());
					k++;
				}
			}
			else {
				k = 0;
				
				if (j==0) {
					l = this->notePadForm->GetSelector()->GetOriginRowIndex();
					row = this->notePadForm->notePad->GetAt(l);
					rowLength = row->GetLength();
					while (k < rowLength-selector->GetOriginColumnIndex()) {
						row->Remove(selector->GetOriginColumnIndex());
						k++;
					}
					if (row->GetLength() == 0) {
						this->notePadForm->notePad->Remove(l);
						isFirstRowRemoved = true;
						erasedRowCount++;
					}
					else {
						l++;
					}
				}
				else if (j==i-1) {
					
					row = this->notePadForm->notePad->GetAt(l);
					while (k < selector->GetEndColumnIndex()) {
						row->Remove(0);
						k++;
					}
					if (erasedRowCount<i-1 && row->GetLength() == 0) {
						this->notePadForm->notePad->Remove(l);
					
					}
					else {
						if (isFirstRowRemoved==false && selector->GetEndColumnIndex()>=0) {
							Glyph* previousRow = this->notePadForm->notePad->GetAt(selector->GetOriginRowIndex());
							Long c = 0;
							while (row->GetLength()>0) {
								previousRow->Add(row->GetAt(0)->Clone());
								row->Remove(0);
								c++;
							}
							this->notePadForm->notePad->Remove(l);
						}
					}
				}
				else {
					this->notePadForm->notePad->Remove(l);
					erasedRowCount++;
				}
			}
			j++;
		}
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(selector->GetOriginRowIndex(),selector->GetOriginColumnIndex());
	}
	else {
		i = selector->GetOriginRowIndex() - selector->GetEndRowIndex() + 1;
		while (j < i) {
			if (i - 1 == 0) {//�������� 1���̶���
				Glyph* row = this->notePadForm->notePad->GetAt(selector->GetOriginRowIndex());
				while (k < selector->GetOriginColumnIndex() - selector->GetEndColumnIndex()) {
					row->Remove(selector->GetEndColumnIndex());
					k++;
				}
			}
			else {
				k = 0;
				if (j == 0) {
					l = this->notePadForm->GetSelector()->GetEndRowIndex();
					row = this->notePadForm->notePad->GetAt(l);
					rowLength = row->GetLength();
					while (k <rowLength - selector->GetEndColumnIndex()) {
						row->Remove(selector->GetEndColumnIndex());
						k++;
					}
					if (row->GetLength() == 0) {
						this->notePadForm->notePad->Remove(l);
						isFirstRowRemoved = true;
						erasedRowCount++;
					}
					else {
						l++;
					}
				}
				else if (j == i - 1) {
					row = this->notePadForm->notePad->GetAt(l);
					while (k < selector->GetOriginColumnIndex()) {
						row->Remove(0);
						k++;
					}
					if (erasedRowCount < i-1 && row->GetLength() == 0) {
						this->notePadForm->notePad->Remove(l);
					}
					else {
						if (isFirstRowRemoved == false && selector->GetOriginColumnIndex() >= 0) {
							Glyph* previousRow = this->notePadForm->notePad->GetAt(selector->GetEndRowIndex());
							Long c = 0;
							while (row->GetLength() > 0) {
								previousRow->Add(row->GetAt(0)->Clone());
								row->Remove(0);
								c++;
							}
							this->notePadForm->notePad->Remove(l);
						}
					}
				}
				else {
					this->notePadForm->notePad->Remove(l);
					erasedRowCount++;
				}
			}
			j++;
		}
		NotePadIndicator notePadIndicator(this->notePadForm);
		notePadIndicator.GoToCoordinate(selector->GetEndRowIndex(),selector->GetEndColumnIndex());
	}
}