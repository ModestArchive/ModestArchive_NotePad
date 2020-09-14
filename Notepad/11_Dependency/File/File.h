//File.h
#ifndef _FILE_H
#define _FILE_H
#include<fstream>
#include<iostream>
#include"NotePadForm.h"
#include"Glyph.h"
#include <string>
using namespace std;


class File {
public:
	//생성자,소멸자

	File();
	File(NotePadForm* notePadForm);
	~File();

	//메소드

	string Load(char(*fileName));
	void  Save(char(*fileName), string contents);

	//연산자함수

	//인라인함수
	NotePadForm* GetNotePadForm() const;
private:
	NotePadForm* notePadForm;
};

inline NotePadForm* File::GetNotePadForm() const {
	return const_cast<NotePadForm*>(this->notePadForm);
}


#endif // _FILE_H

