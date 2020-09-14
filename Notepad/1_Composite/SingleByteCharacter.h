//SingleByteCharacter.h
#ifndef _SINGLEBYTECHARACTER_H
#define _SINGLEBYTECHARACTER_H
#include "Character.h"



class SingleByteCharacter : public Character {
public:
	//������, �Ҹ���
	SingleByteCharacter();
	SingleByteCharacter(char singleByteContent);
	SingleByteCharacter(const SingleByteCharacter& source);
	virtual ~SingleByteCharacter();
	//�޼ҵ�
	bool IsEqual(const SingleByteCharacter& other);
	bool IsNotEqual(const SingleByteCharacter& other);
	virtual string GetContents();
	virtual Glyph* Clone();//�������̵� �ҰŸ� ����Ŭ������ �Լ������̶� �����ϰ� ��������
	
	//�������Լ�
	SingleByteCharacter& operator=(const SingleByteCharacter& source);
	bool operator==(const SingleByteCharacter& other);
	bool operator!=(const SingleByteCharacter& other);
	//�ζ����Լ�
	char GetSingleByteContent() const;
	
	
private:
	char singleByteContent;
	
};

inline char SingleByteCharacter::GetSingleByteContent() const {
	return this->singleByteContent;
}



#endif//_SINGLEBYTECHARACTER_H