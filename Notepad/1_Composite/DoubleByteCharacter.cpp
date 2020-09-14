//DoubleByteCharacter.cpp

#include "DoubleByteCharacter.h"

DoubleByteCharacter::DoubleByteCharacter() {
	this->doubleByteContent[0] = ' ';//2는 크기고 0,1은 첨자이다. 이건 문자배열이고 끝에 널문자들어간건 문자열이자나
	this->doubleByteContent[1] = ' '; 
	
}


DoubleByteCharacter::DoubleByteCharacter(char(*doubleByteContent)) {
	this->doubleByteContent[0] = doubleByteContent[0];
	this->doubleByteContent[1] = doubleByteContent[1];
}
DoubleByteCharacter::DoubleByteCharacter(const DoubleByteCharacter& source) {
	this->doubleByteContent[0] = source.doubleByteContent[0];
	this->doubleByteContent[1] = source.doubleByteContent[1];
}

DoubleByteCharacter::~DoubleByteCharacter() {

}

bool DoubleByteCharacter::IsEqual(const DoubleByteCharacter& other) {

	bool ret = false;
	if (this->doubleByteContent[0] == other.doubleByteContent[0] && 
		this->doubleByteContent[1] == other.doubleByteContent[1]) {
		ret = true;
	}

	return ret;

}

bool DoubleByteCharacter::IsNotEqual(const DoubleByteCharacter& other) {

	bool ret = false;
	if (this->doubleByteContent[0] != other.doubleByteContent[0] || 
		this->doubleByteContent[1] != other.doubleByteContent[1]) {
		ret = true;
	}
	return ret;
}


DoubleByteCharacter& DoubleByteCharacter::operator=(const DoubleByteCharacter& source) {
	this->doubleByteContent[0] = source.doubleByteContent[0];
	this->doubleByteContent[1] = source.doubleByteContent[1];
	return *this;
}


bool DoubleByteCharacter::operator==(const DoubleByteCharacter& other) {
	bool ret = false;
	if (this->doubleByteContent[0] == other.doubleByteContent[0] && 
		this->doubleByteContent[1] == other.doubleByteContent[1]) {
		ret = true;
	}
	return ret;
}

bool DoubleByteCharacter::operator!=(const DoubleByteCharacter& other) {

	bool ret = false;

	if (this->doubleByteContent[0] != other.doubleByteContent[0] || 
		this->doubleByteContent[1] != other.doubleByteContent[1]) {
		ret = true;
	}
	return ret;
}

Glyph* DoubleByteCharacter::Clone() {

	return new DoubleByteCharacter(*this);
}


char* DoubleByteCharacter::GetFirstContents() {
	char buffer[2];
	buffer[0] = this->doubleByteContent[0];
	buffer[1] = '\0';

	return buffer;
}

char* DoubleByteCharacter::GetLastContents() {
	char buffer[2];
	buffer[0] = this->doubleByteContent[1];
	buffer[1] = '\0';

	return buffer;
}


string DoubleByteCharacter::GetContents() {
	char buffer[3];
	buffer[0] = this->doubleByteContent[0];
	buffer[1] = this->doubleByteContent[1];
	buffer[2] = '\0';
	string contents(buffer);
	
	return contents;

}


