//String=Maker.cpp

#include"StringMaker.h"
#include"Selector.h"
#include"Glyph.h"
#include"SingleByteCharacter.h"
#include"DummyRow.h"
#include"NotePadForm.h"

StringMaker::StringMaker(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}


StringMaker::~StringMaker() {

}


string StringMaker::MakeStringInSelectedArea() {
	Selector* selector = this->notePadForm->GetSelector();
	
	string contents = "";
	Long startCopyRowIndex = 0;
	Long startCopyColumnIndex = 0;
	Long endCopyRowIndex = 0;
	Long endCopyColumnIndex = 0;

	bool isRightDownwardSelectedArea = selector->IsRightDownWardSelectedArea();
	if (isRightDownwardSelectedArea == true) {
		startCopyRowIndex = selector->GetOriginRowIndex();
		startCopyColumnIndex = selector->GetOriginColumnIndex();
		endCopyRowIndex = selector->GetEndRowIndex();
		endCopyColumnIndex = selector->GetEndColumnIndex();
	}
	else {
		startCopyRowIndex = selector->GetEndRowIndex();
		startCopyColumnIndex = selector->GetEndColumnIndex();
		endCopyRowIndex = selector->GetOriginRowIndex();
		endCopyColumnIndex = selector->GetOriginColumnIndex();
	}
	Long i = startCopyRowIndex;
	Long j = startCopyColumnIndex;

	while (i <= endCopyRowIndex) {
		
		if (i == endCopyRowIndex) {
			if (endCopyRowIndex-startCopyRowIndex>0) {
				if (endCopyColumnIndex == 0) {
					if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(i))) {
						if (((DummyRow*)(this->notePadForm->notePad->GetAt(i)))->GetIsTabErased() == true) {
							contents += '\t';
						}
					}
					else {
						string lineBreak("\r\n");
						contents += lineBreak;
					}
				}
				else {
					if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(i))) {
						if (((DummyRow*)(this->notePadForm->notePad->GetAt(i)))->GetIsTabErased() == true) {
							contents += '\t';
						}
					}
					else {
						string lineBreak("\r\n");
						contents += lineBreak;
					}
				}
			}
			while (j < endCopyColumnIndex) {
				Glyph* glyph = this->notePadForm->notePad->GetAt(i);
				if (dynamic_cast<SingleByteCharacter*>(glyph->GetAt(j))) {
					if (((SingleByteCharacter*)(glyph->GetAt(j)))->GetSingleByteContent() == '\t') {
						string tab("\t");
						contents += tab;
						j += 8;
					}
					else {
						contents += glyph->GetAt(j)->GetContents();
						j++;
					}
				}
				else {
					contents += glyph->GetAt(j)->GetContents();
					j++;
				}
			}
		}
		else {
			if (i < endCopyRowIndex && i >= startCopyRowIndex) {
				while (j < this->notePadForm->notePad->GetAt(i)->GetLength()) {
					Glyph* glyph = this->notePadForm->notePad->GetAt(i);
					if (dynamic_cast<SingleByteCharacter*>(glyph->GetAt(j))) {
						if (((SingleByteCharacter*)(glyph->GetAt(j)))->GetSingleByteContent() == '\t') {
							string tab("\t");
							contents += tab;
							j += 8;
						}
						else {
							contents += glyph->GetAt(j)->GetContents();
							j++;
						}
					}
					else {
						contents += glyph->GetAt(j)->GetContents();
						j++;
					}
				}
				if (i + 1 < endCopyRowIndex) {
					if (dynamic_cast<DummyRow*>(this->notePadForm->notePad->GetAt(i + 1))) {
						if (((DummyRow*)(this->notePadForm->notePad->GetAt(i)))->GetIsTabErased() == true) {
							contents += '\t';
						}
					}
					else {
						string lineBreak("\r\n");
						contents += lineBreak;
					}
				}
			}
		}
		j = 0;
		i++;
	}
	return contents;
}

string StringMaker::MakeNoCapitalStringForFindNoMatchCase(string contents) {
	Long alphaBetIndex = 65; //capital 'A'
	while (alphaBetIndex < 91) {
		char alphaBet = alphaBetIndex;
		char replaceAlphaBet = alphaBetIndex + 32;
		char replaceBuffer[2];
		replaceBuffer[0] = replaceAlphaBet;
		replaceBuffer[1] = '\0';
		string replaceAlphaBetString(replaceBuffer);
		while (contents.find(alphaBet,0)!=-1) {
			contents.replace(contents.find(alphaBet, 0), 1, replaceAlphaBetString);
		}
		alphaBetIndex++;
	}

	return contents;
}

string StringMaker::MakeTimeString() {
	CTime time = CTime::GetCurrentTime();
	CString cstringTime = "";
	if (time.GetHour() >= 12) {
		Long hour = time.GetHour() - 12;
		if (hour == 0) {
			hour = 12;
		}
		if (time.GetDayOfWeek() == 1) {
			if (hour>=10 && time.GetMinute()>=10) {
				cstringTime.Format(_T("PM %d:%d Sun %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour>=10 && time.GetMinute()<10) {
				cstringTime.Format(_T("PM %d:0%d Sun %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM 0%d:%d Sun %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour<10 && time.GetMinute()<10) {
				cstringTime.Format(_T("PM 0%d:0%d Sun %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 2) {
			if (hour >=10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM %d:%d Mon %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM %d:0%d Mon %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM 0%d:%d Mon %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM 0%d:0%d Mon %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 3) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM %d:%d Tue %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM %d:0%d Tue %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM 0%d:%d Tue %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM 0%d:0%d Tue %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 4) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM %d:%d Wed %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM %d:0%d Wed  %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM 0%d:%d Wed %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM 0%d:0%d Wed %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 5) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM %d:%d Tur %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM %d:0%d Tur %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM 0%d:%d Tur %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM 0%d:0%d Tur %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 6) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM %d:%d Fri %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM %d:0%d Fri %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM 0%d:%d Fri %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM 0%d:0%d Fri %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 7) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM %d:%d Sat %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM %d:0%d Sat %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("PM 0%d:%d Sat %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("PM 0%d:0%d Sat %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
	}
	else {
		Long hour = 12-(12 - time.GetHour());
		if (hour == 12) {
			hour = 0;
		}
		if (time.GetDayOfWeek() == 1) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM %d:%d Sun %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM %d:0%d Sun %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM 0%d:%d Sun %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM 0%d:0%d Sun %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 2) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM %d:%d Mon %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM %d:0%d Mon %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM 0%d:%d Mon %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM 0%d:0%d Mon %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 3) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM %d:%d Tue %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM %d:0%d Tue %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM 0%d:%d Tue %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM 0%d:0%d Tue %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 4) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM %d:%d Wed %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM %d:0%d Wed  %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM 0%d:%d Wed %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM 0%d:0%d Wed %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 5) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM %d:%d Tur %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM %d:0%d Tur %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM 0%d:%d Tur %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM 0%d:0%d Tur %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 6) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM %d:%d Fri %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM %d:0%d Fri %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM 0%d:%d Fri %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM 0%d:0%d Fri %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
		else if (time.GetDayOfWeek() == 7) {
			if (hour >= 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM %d:%d Sat %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour >= 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM %d:0%d Sat %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() >= 10) {
				cstringTime.Format(_T("AM 0%d:%d Sat %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
			else if (hour < 10 && time.GetMinute() < 10) {
				cstringTime.Format(_T("AM 0%d:0%d Sat %d-%d-%d"), hour, time.GetMinute(), time.GetYear(), time.GetMonth(), time.GetDay());
			}
		}
	}
	string timeString((LPSTR)(LPCTSTR)(cstringTime));
	return timeString;
}