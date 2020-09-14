#ifndef _DOUBLEBYTECHARACTER_H
#define _DOUBLEBYTECHARACTER_H
#include "Character.h"


class DoubleByteCharacter : public Character {
public:
	//������,�Ҹ���
	DoubleByteCharacter();
	DoubleByteCharacter(char (*doubleByteContent));
	DoubleByteCharacter(const DoubleByteCharacter& source);
	virtual ~DoubleByteCharacter();
	//�޼ҵ�
	bool IsEqual(const DoubleByteCharacter& other);
	bool IsNotEqual(const DoubleByteCharacter& other);
	virtual string GetContents();
	virtual Glyph* Clone();
	char* GetFirstContents();
	char* GetLastContents();
	//�������Լ�
	DoubleByteCharacter& operator=(const DoubleByteCharacter& source);
	bool operator==(const DoubleByteCharacter& other);
	bool operator!=(const DoubleByteCharacter& other);
	//�ζ����Լ�
	char* GetDoubleByteContent() const;
private:
	char doubleByteContent[2];//���ڹ迭�� ũ��
	};

inline char* DoubleByteCharacter::GetDoubleByteContent() const {
	return const_cast<char*>(this->doubleByteContent);
}
#endif   //_DOUBLEBYTECHARACTER_H