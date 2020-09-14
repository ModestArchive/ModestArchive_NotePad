#ifndef _DOUBLEBYTECHARACTER_H
#define _DOUBLEBYTECHARACTER_H
#include "Character.h"


class DoubleByteCharacter : public Character {
public:
	//생성자,소멸자
	DoubleByteCharacter();
	DoubleByteCharacter(char (*doubleByteContent));
	DoubleByteCharacter(const DoubleByteCharacter& source);
	virtual ~DoubleByteCharacter();
	//메소드
	bool IsEqual(const DoubleByteCharacter& other);
	bool IsNotEqual(const DoubleByteCharacter& other);
	virtual string GetContents();
	virtual Glyph* Clone();
	char* GetFirstContents();
	char* GetLastContents();
	//연산자함수
	DoubleByteCharacter& operator=(const DoubleByteCharacter& source);
	bool operator==(const DoubleByteCharacter& other);
	bool operator!=(const DoubleByteCharacter& other);
	//인라인함수
	char* GetDoubleByteContent() const;
private:
	char doubleByteContent[2];//문자배열의 크기
	};

inline char* DoubleByteCharacter::GetDoubleByteContent() const {
	return const_cast<char*>(this->doubleByteContent);
}
#endif   //_DOUBLEBYTECHARACTER_H