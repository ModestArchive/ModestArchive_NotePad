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
	//������,�Ҹ���

	File();
	File(NotePadForm* notePadForm);
	~File();

	//�޼ҵ�

	string Load(char(*fileName));
	void  Save(char(*fileName), string contents);

	//�������Լ�

	//�ζ����Լ�
	NotePadForm* GetNotePadForm() const;
private:
	NotePadForm* notePadForm;
};

inline NotePadForm* File::GetNotePadForm() const {
	return const_cast<NotePadForm*>(this->notePadForm);
}


#endif // _FILE_H

