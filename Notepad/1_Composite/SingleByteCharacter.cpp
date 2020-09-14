#include "SingleByteCharacter.h"
#include <afxwin.h>
#include <string>

SingleByteCharacter::SingleByteCharacter() {
	this->singleByteContent = ' ';
	
	
}


SingleByteCharacter::SingleByteCharacter(char singleByteContent) {

	this->singleByteContent = singleByteContent;
	
}


SingleByteCharacter::SingleByteCharacter(const SingleByteCharacter& source) {

	this->singleByteContent = source.singleByteContent;
	
	
}

SingleByteCharacter::~SingleByteCharacter() {

}

bool SingleByteCharacter::IsEqual(const SingleByteCharacter& other) {
	bool ret = false;
	if (this->singleByteContent == other.singleByteContent) {
		ret = true;
	}
	return ret;
}

bool SingleByteCharacter::IsNotEqual(const SingleByteCharacter& other) {
	bool ret = false;
	if (this->singleByteContent != other.singleByteContent ) {
		ret = true;
	}
	return ret;
}

SingleByteCharacter& SingleByteCharacter::operator=(const SingleByteCharacter& source) {
	this->singleByteContent = source.singleByteContent;
	
	return *this;
}


bool SingleByteCharacter ::operator==(const SingleByteCharacter& other) {
	bool ret = false;
	if (this->singleByteContent == other.singleByteContent ) {
		ret = true;
	}
	return ret;
}


bool SingleByteCharacter::operator!=(const SingleByteCharacter& other) {
	bool ret = false;
	if (this->singleByteContent != other.singleByteContent ) {
		ret = true;
	}
	return ret;
}


Glyph* SingleByteCharacter::Clone() {
	return new SingleByteCharacter(*this);

}

string SingleByteCharacter::GetContents() {

	char buffer[2];

	if (this->singleByteContent == VK_TAB) {
		buffer[0] =	' ';
		buffer[1] = '\0';
	}
	else {
	buffer[0] = this->singleByteContent;
	buffer[1] = '\0';
	}
	string contents(buffer);
	return contents;
}

