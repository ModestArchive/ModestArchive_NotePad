//StringMaker.h

#ifndef _STRINGMAKER_H
#define _STRINGMAKER_H

#include<string>;
class NotePadForm;
using namespace std;

class StringMaker {
public:
	StringMaker(NotePadForm* notePadForm);
	~StringMaker();
	string MakeStringInSelectedArea();
	string MakeNoCapitalStringForFindNoMatchCase(string contents);
	string MakeTimeString();
	
 private:
	 NotePadForm* notePadForm;
};
#endif // !_STRINGMAKER_H
