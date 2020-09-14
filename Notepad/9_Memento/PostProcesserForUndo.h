//PostProcesserForUndo.h

#ifndef _POSTPROCESSERFORUNDO_H
#define _POSTPROCESSERFORUNDO_H

#include"NotePadHistory.h"
#include"NotePadForm.h"

class PostProcesserForUndo {
public:
	//������,�Ҹ���
	PostProcesserForUndo(NotePadForm* notePadForm,NotePadHistory* notePadHistory);
	~PostProcesserForUndo();
	
	//�޼ҵ�
	void DoPostProcessForUndo();
private:
	NotePadForm* notePadForm;
	NotePadHistory* notePadHistory;
};
#endif // !_POSTPROCESSERFORUNDO_H

