//KeyActionFactory.cpp

#include"KeyAction.h"
#include"ShiftCtrlEndKey.h"
#include"ShiftCtrlHomeKey.h"
#include"ShiftCtrlLeftArrowKey.h"
#include"ShiftCtrlRightArrowKey.h"
#include"ShiftDownArrowKey.h"
#include"ShiftEndKey.h"
#include"ShiftHomeKey.h"
#include"ShiftLeftArrowKey.h"
#include"ShiftRightArrowKey.h"
#include"ShiftUpArrowKey.h"
#include"CtrlLeftArrowKey.h"
#include"CtrlEndKey.h"
#include"CtrlHomeKey.h"
#include"CtrlRightArrowKey.h"
#include"LeftArrowKey.h"
#include"RightArrowKey.h"
#include"UpArrowKey.h"
#include"DownArrowKey.h"
#include"EndKey.h"
#include"HomeKey.h"
#include"BackspaceKey.h"
#include"DeleteKey.h"
#include"PageUpKey.h"
#include"PageDownKey.h"
#include"KeyActionFactory.h"
#include"CtrlZKey.h"
#include"CtrlYKey.h"
#include"CtrlCKey.h"
#include"CtrlVKey.h"
#include"CtrlXKey.h"
#include"Selector.h"
#include"NotePadFormControlWnd.h"
#include"FindReplaceSupervisor.h"
#include"ShiftF3.h"
#include"F3.h"
#include"F5.h"
#include"CtrlShiftS.h"
#include"CtrlShiftN.h"
#include"CtrlS.h"
#include"CtrlP.h"
#include"CtrlO.h"
#include"CtrlN.h"
#include"CtrlH.h"
#include"CtrlF.h"
#include"CtrlE.h"
#include"CtrlA.h"
#include"NotePadMetric.h"


KeyActionFactory::KeyActionFactory() {
	this->notePadForm = 0;
}

KeyActionFactory::KeyActionFactory(NotePadForm* notePadForm) {
	this->notePadForm = notePadForm;
}

KeyActionFactory::~KeyActionFactory() {

}

KeyAction* KeyActionFactory::MakeKey(UINT nChar) {
	KeyAction* keyAction = 0;
	
		if (nChar == VK_LEFT) {
			if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new ShiftCtrlLeftArrowKey(this->notePadForm);
				this->notePadForm->SetIsWithShiftKey(true);
			}
			else if (GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new ShiftLeftArrowKey(this->notePadForm);
				this->notePadForm->SetIsWithShiftKey(true);
			}
			else if (GetKeyState(VK_CONTROL) & 0x8000) {
				keyAction = new CtrlLeftArrowKey(this->notePadForm);
			}
			else {
				keyAction = new LeftArrowKey(this->notePadForm);
			}
		}	

		else if (nChar == VK_RIGHT) {
			if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new ShiftCtrlRightArrowKey(this->notePadForm);
				this->notePadForm->SetIsWithShiftKey(true);
			}
			else if (GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new ShiftRightArrowKey(this->notePadForm);
				this->notePadForm->SetIsWithShiftKey(true);
			}
			else if (GetKeyState(VK_CONTROL)&0x8000) {
				keyAction = new CtrlRightArrowKey(this->notePadForm);
			}
			else {
				keyAction = new RightArrowKey(this->notePadForm);
			}
		}

		else if (nChar == VK_HOME) {
		    if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new ShiftCtrlHomeKey(this->notePadForm);
				this->notePadForm->SetIsWithShiftKey(true);
			}
			else if (GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new ShiftHomeKey(this->notePadForm);
				this->notePadForm->SetIsWithShiftKey(true);
			}
			else if (GetKeyState(VK_CONTROL) & 0x8000) {
				keyAction = new CtrlHomeKey(this->notePadForm);
			}
			else {
				keyAction = new HomeKey(this->notePadForm);
			}
		}

		else if (nChar == VK_END) {
			if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new ShiftCtrlEndKey(this->notePadForm);
				this->notePadForm->SetIsWithShiftKey(true);
			}
			else if (GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new ShiftEndKey(this->notePadForm);
				this->notePadForm->SetIsWithShiftKey(true);
			}
			else if (GetKeyState(VK_CONTROL) & 0x8000) {
				keyAction = new CtrlEndKey(this->notePadForm);
			}
			else {
				keyAction = new EndKey(this->notePadForm);
			}
		}
		else if (nChar == 0x43 && GetKeyState(VK_CONTROL)&0x8000) {
			if (this->notePadForm->GetIsSelected() == true) {
				keyAction = new CtrlCKey(this->notePadForm);
			}
		}
		else if (nChar == 0x56 && GetKeyState(VK_CONTROL) & 0x8000) {
			
			keyAction = new CtrlVKey(this->notePadForm);
		}
		else if (nChar == 0x58 && GetKeyState(VK_CONTROL) & 0x8000) {

			keyAction = new CtrlXKey(this->notePadForm);
		}
		else if (nChar == 0x5A && GetKeyState(VK_CONTROL) & 0x8000) {
			keyAction = new CtrlZKey(this->notePadForm);
		}
		else if (nChar==0x59 && GetKeyState(VK_CONTROL) & 0x8000) {
			keyAction = new CtrlYKey(this->notePadForm);
		}
		else if (nChar == VK_UP) {
			if (GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new ShiftUpArrowKey(this->notePadForm);
				this->notePadForm->SetIsWithShiftKey(true);
			}
			else {
				keyAction = new UpArrowKey(this->notePadForm);
			}
		}

		else if (nChar == VK_DOWN) {
			if (GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new ShiftDownArrowKey(this->notePadForm);
				this->notePadForm->SetIsWithShiftKey(true);
			}
			else {
				keyAction = new DownArrowKey(this->notePadForm);
			}
		}

		else if (nChar == VK_BACK) {
			keyAction = new BackspaceKey(this->notePadForm);
			
		}

		else if (nChar == VK_DELETE) {
			keyAction = new DeleteKey(this->notePadForm);
		}

		else if (nChar == VK_PRIOR) {
			keyAction = new PageUpKey(this->notePadForm);
		}

		else if (nChar == VK_NEXT) {
			keyAction = new PageDownKey(this->notePadForm);
		}
		else if (nChar == VK_F3) {
			NotePadMetric notePadMetric(this->notePadForm);
			bool thereIsContents = notePadMetric.GetThereIsContents();
			if (thereIsContents == true) {
				if (GetKeyState(VK_SHIFT) & 0x8000) {
					keyAction = new ShiftF3(this->notePadForm);
				}
				else {
					keyAction = new F3(this->notePadForm);
				}
			}
		}
		else if (nChar == VK_F5) {
		    keyAction = new F5(this->notePadForm);
		}
		else if (nChar ==0x53) {//SŰ
			if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new CtrlShiftS (this->notePadForm);
			}
			else if (GetKeyState(VK_CONTROL) & 0x8000) {
				keyAction = new CtrlS(this->notePadForm);
			}
		}
		else if (nChar == 0x4E) {//NŰ
			if (GetKeyState(VK_CONTROL) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000) {
				keyAction = new CtrlSHiftN(this->notePadForm);
			}
			else if (GetKeyState(VK_CONTROL) & 0x8000) {
				keyAction = new CtrlN(this->notePadForm);
			}
		}
		else if (nChar == 0x50) {//PŰ
			if (GetKeyState(VK_CONTROL) & 0x8000) {
				keyAction = new CtrlP(this->notePadForm);
			}
		}
		else if (nChar == 0x4F) {//OŰ
			if (GetKeyState(VK_CONTROL) & 0x8000) {
				keyAction = new CtrlO(this->notePadForm);
			}
		}
		else if (nChar == 0x48) {//HŰ
			if (GetKeyState(VK_CONTROL) & 0x8000) {
				NotePadMetric notePadMetric(this->notePadForm);
				bool thereIsContents = notePadMetric.GetThereIsContents();
				if (thereIsContents == true) {
					keyAction = new CtrlH(this->notePadForm);
				}
			}
		}
		else if (nChar == 0x46) {//FŰ
			if (GetKeyState(VK_CONTROL) & 0x8000) {
				NotePadMetric notePadMetric(this->notePadForm);
				bool thereIsContents = notePadMetric.GetThereIsContents();
				if (thereIsContents==true) {
					keyAction = new CtrlF(this->notePadForm);
				}
			} 
		}
		else if (nChar == 0x45) {//EŰ
			if (GetKeyState(VK_CONTROL) & 0x8000) {
				keyAction = new CtrlE(this->notePadForm);
			}
		}
		else if (nChar==0x41) {//A키
			if (GetKeyState(VK_CONTROL) & 0x8000) {
				keyAction = new CtrlA(this->notePadForm);
			}
		}
		if (dynamic_cast<CtrlLeftArrowKey*>(keyAction) || dynamic_cast<LeftArrowKey*>(keyAction) || 
			dynamic_cast<CtrlRightArrowKey * >(keyAction) || dynamic_cast<RightArrowKey*>(keyAction) ||
			dynamic_cast<CtrlHomeKey*>(keyAction) || dynamic_cast<HomeKey*>(keyAction) ||
			dynamic_cast<CtrlEndKey*>(keyAction) || dynamic_cast<EndKey*>(keyAction) ||
			dynamic_cast<CtrlZKey*>(keyAction) || dynamic_cast<CtrlYKey*>(keyAction) || 
			dynamic_cast<CtrlA*>(keyAction)|| dynamic_cast<UpArrowKey*>(keyAction) ||
			dynamic_cast<DownArrowKey*>(keyAction) || dynamic_cast<PageUpKey*>(keyAction) || 
			dynamic_cast<PageDownKey*>(keyAction)) {

			if (this->notePadForm->GetIsSelected() == true) {
				this->notePadForm->SetIsSelected(false);
				if (this->notePadForm->GetSelector() != 0) {
					delete this->notePadForm->GetSelector();
				}
				Selector* selector = new Selector(this->notePadForm);
				this->notePadForm->SetSelector(selector);
				if (((NotePadFormControlWnd*)(this->notePadForm->GetParent()))->GetContentsFinder() != 0) {
					FindReplaceSupervisor findReplaceSupervisor(((NotePadFormControlWnd*)(this->notePadForm->GetParent())), this->notePadForm,
																((NotePadFormControlWnd*)(this->notePadForm->GetParent()))->GetContentsFinder(), 0, 0);
					findReplaceSupervisor.DeleteMatchIndexCollector();
				}
			}
		}
	return keyAction;
}
