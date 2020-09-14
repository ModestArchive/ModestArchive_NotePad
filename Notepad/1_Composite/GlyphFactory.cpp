//GlyphFactory.cpp

#include"GlyphFactory.h"
#include"Glyph.h"
#include"Row.h"
#include"NotePad.h"
#include"SingleByteCharacter.h"
#include"DoubleByteCharacter.h"


GlyphFactory::GlyphFactory() {
	this->contents[0] = ' ';
	this->contents[1] = ' ';
}

GlyphFactory::~GlyphFactory() {

}

Glyph* GlyphFactory::MakeGlyph(char(*contents)) {
	
	Glyph* glyph=0;

		if (contents[0] == '\0') {//그냥 ""하면 안돼지 문자배열을 입력받는데 아무것도 없으면 널표시로 해야지
		glyph = new NotePad;
		}

		else if(contents[0] == '\r' && contents[1] == '\n') {
		glyph = new Row;
		}

		else if (!(contents[0] & 0x80 )) {//들어있는데이터와 아스키코드랑 비교할때 이런 표현을 쓴다!
		glyph = new SingleByteCharacter(contents[0]);//복사생성자해야지 왜 디폴트로 하냐
		}
		
		else if (contents[0] & 0x80){//들어있는데이터와 아스키코드랑 비교할때 이런 표현을 쓴다!
		glyph = new DoubleByteCharacter(contents);////복사생성자해야지 왜 디폴트로 하냐
		}
		
		return glyph;

}