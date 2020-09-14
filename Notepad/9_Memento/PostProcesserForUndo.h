//PostProcesserForUndo.h

#ifndef _POSTPROCESSERFORUNDO_H
#define _POSTPROCESSERFORUNDO_H

#include"NotePadHistory.h"
#include"NotePadForm.h"

class PostProcesserForUndo {
public:
	//持失切,社瑚切
	PostProcesserForUndo(NotePadForm* notePadForm,NotePadHistory* notePadHistory);
	~PostProcesserForUndo();
	
	//五社球
	void DoPostProcessForUndo();
private:
	NotePadForm* notePadForm;
	NotePadHistory* notePadHistory;
};
#endif // !_POSTPROCESSERFORUNDO_H

