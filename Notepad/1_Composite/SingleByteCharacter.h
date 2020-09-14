//SingleByteCharacter.h
#ifndef _SINGLEBYTECHARACTER_H
#define _SINGLEBYTECHARACTER_H
#include "Character.h"



class SingleByteCharacter : public Character {
public:
	//생성자, 소멸자
	SingleByteCharacter();
	SingleByteCharacter(char singleByteContent);
	SingleByteCharacter(const SingleByteCharacter& source);
	virtual ~SingleByteCharacter();
	//메소드
	bool IsEqual(const SingleByteCharacter& other);
	bool IsNotEqual(const SingleByteCharacter& other);
	virtual string GetContents();
	virtual Glyph* Clone();//오버라이딩 할거면 슈퍼클래스의 함수선언문이랑 동일하게 만들어야함
	
	//연산자함수
	SingleByteCharacter& operator=(const SingleByteCharacter& source);
	bool operator==(const SingleByteCharacter& other);
	bool operator!=(const SingleByteCharacter& other);
	//인라인함수
	char GetSingleByteContent() const;
	
	
private:
	char singleByteContent;
	
};

inline char SingleByteCharacter::GetSingleByteContent() const {
	return this->singleByteContent;
}



#endif//_SINGLEBYTECHARACTER_H